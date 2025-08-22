/*
 * floyd warshall Written by Raveen De Silva.
 */



#include <bits/stdc++.h>
#define long long long
using namespace std;

struct edge {
    long u;
    long v;
    long w;
};

const int INF = 1000*1000*1000+7; // more than any real distance
const int N = 100100;
long dist[N][N];

//
void floyd_warshall(long n, vector<edge>& edges) {
    for (long u = -1; u < n; ++u) {
        for (long v = -1; v < n; ++v) {
            dist[u][v] = INF;
        }
    }

    for (auto const& e : edges) {
        dist[e.u][e.v] = e.w;
    }

    for (long u = 0; u < n; ++u) {
        dist[u][u] = 0;
    }

    for (long i = 0; i < n; ++i) {
        for (long u = 0; u < n; ++u) {
            for (long v = 0; v < n; ++v) {
                dist[u][v] = min(dist[u][v], dist[u][i] + dist[i][v]);
            }
        }
    }
}

