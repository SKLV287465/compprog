#include <bits/stdc++.h>
#define long long long
using namespace std;

// USINTG CODE FROM RAVEEN DE SILVA's lecture slides.

/*
 * combinations
 */


const int N = 1001001;
#define MOD 1000000007
long f[N], invfact[N];
long modpow(long a, long b, int c) // as earlier, but modulo c
{
    long ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % c;
        a = a * a % c;
        b >>= 1;
    }
    return ret;
}

long inv(long x) {
  return modpow(x, MOD-2, MOD); // Fermat's little theorem
}

void init() {
    f[0] = 1;
    for (long i = 1; i < N; ++i) {
        f[i] = (i * f[i - 1]) % MOD;
    }

    // precompute factorials.
    invfact[N-1] = modpow(f[N-1], MOD-2, MOD);
    for (long i = N - 1; i > 0; --i) {
        invfact[i - 1] = invfact[i] * i % MOD;
    }
}

// nCr
long nCr(long n, long r) {
    if (r < 0 || r > n) return 0;
    long res = (f[n] * inv(f[n - r])) % MOD;
    res = (res * inv(f[r])) % MOD;
    return res;
}

// c is prime mod
long lucas_theorem(long n, long r, long c) {
    vector<long> ns;
    vector<long> rs;
    while (n > 0) {
        ns.push_back(n % c);
        n /= c;
    }
    while (r > 0) {
        rs.push_back(r % c);
        r /= c;
    }

    while (rs.size() < ns.size()) {
        rs.push_back(0);
    }

    long ret = 1;
    for (long i = 0; i < rs.size(); ++i) {
        ret *= nCr(ns[i], rs[i]);
    }

    return ret;
}
