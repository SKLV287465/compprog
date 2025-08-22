#include <algorithm>
#include <bits/stdc++.h>
#define long long long
using namespace std;

// prev
// done
long dp[18][1 << 18] = {0};

int main() {
    long n, m, g;
    cin >> n >> m >> g;
    vector<long> satisfactions(n);
    map<pair<long, long>, long> rules;

    for (long i = 0; i < n; ++i) {
        cin >> satisfactions[i];
    }

    for (long i = 0; i < g; ++i) {
        long x, y, z;
        cin >> x >> y >> z;
        rules.insert({{x - 1, y - 1}, z}); // zero based indexing.
    }

    // so i need to fill every possible prev.
    // This below sets the starting points.
    long ret = 0;
    for (long i = 0; i < n; ++i) {
        dp[i][1 << i] = satisfactions[i];
        ret = max(ret, satisfactions[i]);
    }
    
    // something weird is happening where the rule is not happening.'
    // 2 1 4 is not being picked up.
    // '
//    for (long j = 0; j < n; ++j) {
//        for (long k = 1; k < 1 << n; ++k) {
//            if (dp[j][k]) {
//                // if there is an entry
//                for (long next = 0; next < n; ++next) {
//                    if ((1 << next) & k) continue;
//                    // skip if next is already in k.
//                    long v = dp[j][k] + satisfactions[next];
//                    if (rules.count({j, next})) {
//                        v += rules[{j, next}];
//                    }
//                    dp[next][k | (1 << next)] = max(v, dp[next][k | (1 << next)]);
//                    
//                    if (__builtin_popcount(k) > m - 1) continue;
//                    ret = max(ret, v);
//                }
//            }
//        }
//    }

    // i am not getting the case where dp[j][k] is zero but still valid.
    for (long k = 1; k < 1 << n; ++k) {
        for (long j = 0; j < n; ++j) {
            if ((1 << j) & k) {
                for (long next = 0; next < n; ++next) {
                    if ((1 << next) & k) continue;
                    // skip if next is already in k.
                    long v = dp[j][k] + satisfactions[next];
                    if (rules.count({j, next})) {
                        v += rules[{j, next}];
                    }
                    dp[next][k | (1 << next)] = max(v, dp[next][k | (1 << next)]);
                    
                    if (__builtin_popcount(k) > m - 1) continue;
                    ret = max(ret, v);
                }
            }
        }
    }
    cout << ret << endl;
}
