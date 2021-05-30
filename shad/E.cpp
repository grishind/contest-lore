#include <bits/stdc++.h>

using namespace std;

// Решето Эратосфена
class EratosthenesSieve {
    vector<int> sieve;
public:
    EratosthenesSieve(int n) : sieve(n, 0) {
        for (int i = 1; i < n; i++) {
            for (int j = i + i; j < n; j += i) {
                sieve[j]++;
            }
        }
    }

    bool isPrime(int k) {
        return sieve[k] == 1;
    }
};

// Быстое возведение base в степень power по модулю mod
int fastPowerModulo(int base, int power, int mod) {
    if (power == 1) {
        return base%mod;
    }
    if (power%2 == 0) {
        const int sq = fastPowerModulo(base, power/2, mod);
        return (sq*sq)%mod;
    }
    const int sq = fastPowerModulo(base, (power - 1)/2, mod);
    return (sq*sq*base)%mod;
}

// Критерий делимости числа 1..1 с n единицами на простое p
bool repunitDivisible(int n, int p) {
    return fastPowerModulo(10, n, p) == 1;
}

// Наименьшией отличный от 1 делитель x
int smallestDivisor(int x) {
    for (int d = 2; d*d <= x; d++) {
        if (x%d == 0) {
            return d;
        }
    }
    return x;
}

// Наименьшией отличный от 1 делитель числа 1..1 с n единицами, не превышающий bound
int smallestRepunitDivisor(int n, int bound) {
    if (n % 3 == 0) {
        return 3;
    }
    if (n % 2 == 0) {
        return 11;
    }
    auto sieve = new EratosthenesSieve(bound);
    for (int i = 5; i < bound; i++) {
        if (sieve->isPrime(i) && repunitDivisible(n, i)) {
            return i;
        }
    }
    return bound;
}

int solve(const string &str) {
    const int n = str.size();
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += str[i] - '0';
    }
    const int sum_divisor = smallestDivisor(sum);
    const int repunit_divisor = smallestRepunitDivisor(n, sum_divisor);
    return std::min(sum_divisor, repunit_divisor);
}

int main() {
    string str;
    cin >> str;
    cout << solve(str) << '\n';

    return 0;
}
