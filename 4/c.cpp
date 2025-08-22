#include <algorithm>
#include <bits/stdc++.h>
#include <limits>
#include <queue>
#define long long long
using namespace std;

struct considerations {
    long prev_colour;
    long pos;
    long diff_colours;
    long cost;
};

int main() {
    long n, m, k;
    cin >> n >> m >> k;
    long start_colours = 0;
    long prev = 0;
    vector<long> initial_colours(n);
    for (long i = 0; i < n; ++i) {
        cin >> initial_colours[i];
        if (!prev && prev != initial_colours[i]) {
            ++start_colours;
        }
    }
    ++start_colours;
    vector<priority_queue<long, vector<long>, greater<long>>> sorted_costs(n);
    vector<vector<long>> costs(n);
    for (long i = 0; i < n; ++i) {
        for (long j = 0; j < m; ++j) {
            long c;
            cin >> c;
            costs[i].push_back(c);
            sorted_costs[i].push(c);
        }
    }
    
    // set next colour;
    long prev_colour = initial_colours[n - 1];
    vector<long> next_colours(n);
    for (long i = n - 1; i >= 0; --i) {
        next_colours[i] = prev_colour;
        if (initial_colours[i] != 0) prev_colour = initial_colours[i];
    }
    long min_cost = numeric_limits<long>::max();

    // index, num colours, min cost
    vector<vector<long>> dp(n);
    for (long i = 0; i < n; ++i) {
        dp.emplace_back(n, numeric_limits<long>::max());
    }
    // push the starting case:

    struct considerations starting = {0, 0, start_colours, 0};
    queue<struct considerations> q;
    // create the start case
    q.push(std::move(starting));
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();

        if (initial_colours[cur.pos]) {
            // do next one
            q.emplace(initial_colours[cur.pos], cur.pos + 1, cur.diff_colours, cur.cost);
        } else {
            // is zero so i need to consider all possibilities.
            // staying same:
            // next
            struct considerations same_next = {next_colours[cur.pos], cur.pos + 1, cur.diff_colours, cur.cost + costs[cur.pos][next_colours[cur.pos]]};
            dp[cur.pos, cur.diff_colours] = min(dp[cur.pos + 1, cur.diff_colours], same_next.cost);
            q.push(move(same_next));
            // prev
            struct considerations same_prev = {cur.prev_colour, cur.pos + 1, cur.diff_colours, cur.cost + costs[cur.pos][cur.prev_colour]};
            dp[cur.pos, cur.diff_colours] = min(dp[cur.pos + 1, cur.diff_colours], same_prev.cost);
            q.push(move(same_next));

            // cheapest
            // second cheapest
            // third cheapest
        }
    }
}
