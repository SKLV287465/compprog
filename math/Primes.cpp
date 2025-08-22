#include <bits/stdc++.h>
using namespace std;
#define long long long

/*
 * primes
 */

#include <vector>
using namespace std;

bool isprime(long x) {
  if (x < 2) return false;

  for (long f = 2; f*f <= x; f++) {
    if (x % f == 0) { return false; }
  }
  
  return true;
}

// Returns prime factors in increasing order with right multiplicity.
vector<long> primefactorize(long x) {
  vector<long> factors;
  for (long f = 2; f*f <= x; f++)
    while (x % f == 0) {
      factors.push_back(f);
      x /= f;
    }

  if (x != 1) { factors.push_back(x); }
  return factors;
}
