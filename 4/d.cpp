#include <bits/stdc++.h>
#define long long long
using namespace std;

// I probably want to have some kind of dp
// dp[current_index]
// the problem looks kind of greedy though
//
// Brute force:
// - try every combination of routers, but the question becomes, which routers do i pick?
// let dp[i] be the cheapest{not necessarily best way} to connect the first i rooms (0 indexed).
long dp[2 * 100007];
int main() {
    long n, k;
    cin >> n >> k;
    queue<long> routers; // genius idea: what if i have routers based on position
    for (long i = 1; i < n; ++i) {
        long cur;
        cin >> cur;
        if (cur) routers.push(i);
    }
    
    // at the zero point.
    dp[0] = 0;
    for (long i = 1; i < n + 1; ++i) {
        // if there is no router in range, then i just need to tank the cost
        if (routers.front() != i) {
            dp[i] = dp[i - 1] + i;
        } else { // if a router is in range
            routers.pop();
            dp[i] = dp[i - k] + i;
        }
    }
}
