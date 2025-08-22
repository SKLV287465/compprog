#include <bits/stdc++.h>
#include <limits>
#define long long long
using namespace std;

long dp[101][101][101]; // a trees, b beauty, c last colour. maps to cost.

int main() {
    long n, m, k;
    cin >> n >> m >> k;
    memset(dp, -1, sizeof(dp)); 
    vector<long> initial_colours(n);
    for (long i = 0; i < n; ++i) {
        long col;
        cin >> col;
        initial_colours[i] = col - 1; // zero based indexing.
    }

    vector<vector<long>> costs(n, vector<long>(m));
    for (long i = 0; i < n; ++i) {
        for (long j = 0; j < m; ++j) {
            cin >> costs[i][j];
        }
    }

    // definitely not a bitset question
    //
    // Set the base case. also need to check if already coloured.
    // if k == 1 and n == 1.
    long mincost = numeric_limits<long>::max(); 
    if (initial_colours[0] != -1) {
        dp[0][1][initial_colours[0]] = 0;
        if (n == 1) {
            mincost = min(mincost, dp[0][1][initial_colours[0]]);
        }
    } else {
        for (long i = 0; i < m; ++i) {
            dp[0][1][i] = costs[0][i];
            if (n == 1) {
                mincost = min(mincost, dp[0][1][i]);
            }
        }
    }
    

    // do the things.
    // j and a might need to start from 1.
    
    for (long i = 1; i < n; ++i) { // tree loop
        for (long b = 1; b < n; ++b) {
            for (long j = 0; j < m; ++j) { // colour loop prev
                if (dp[i - 1][b][j] == -1) continue;// skip invalid
                if (initial_colours[i] != -1) { // zero based indexing.
                    long new_b = b;
                    if (initial_colours[i] != j) ++new_b;
                    if (dp[i][new_b][initial_colours[i]] > dp[i - 1][b][j] || dp[i][new_b][initial_colours[i]] == -1) dp[i][new_b][initial_colours[i]] = dp[i - 1][b][j];
                    if (new_b == k && i == n - 1) {
                        mincost = min(mincost, dp[i][new_b][initial_colours[i]]);
                    }
                } else {
                    for (long a = 0; a < m; ++a) {
                        long new_b = b;
                        if (j != a) ++new_b;
                        if (dp[i][new_b][a] == -1 || dp[i][new_b][a] > dp[i - 1][b][j] + costs[i][a])
                        dp[i][new_b][a] = dp[i - 1][b][j] + costs[i][a];
                        if (new_b == k && i == n - 1) {
                            mincost = min(mincost, dp[i][new_b][a]);
                        }
                    }
                }
            }
        }
        
        
    }

    if (mincost == numeric_limits<long>::max()) {
        cout << -1 << endl;
    } else {
        cout << mincost << endl;
    }

}
