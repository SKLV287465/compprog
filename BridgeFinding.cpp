#include <bits/stdc++.h>
#define long long long
using namespace std;
#define N 1001001 // number of vertices in graph


/*
 * bridges written by Raveen Da Silva
 */

long preorder[N]; // order of pushing to the DFS stack
                 // initialise to -1
long T = 0; // counter for preorder sequence
long reach[N]; // reach[u] is the smallest preorder index
            // of any vertex reachable from u
vector<pair<long,long>> bridges;

// u is the starting point (source) and v is prev
void dfs(vector<vector<long>>& edges, long u, long from = -1) {
  preorder[u] = T++;
  reach[u] = preorder[u];

  for (long v : edges[u]) if (v != from) {
    if (preorder[v] == -1) { // u--v is a tree edge
      // v hasn't been seen before, so recurse
      dfs(edges, v, u);
      // if v can't reach anything earlier than itself
      // then u--v is a bridge
      if (reach[v] == preorder[v]) { bridges.emplace_back(u,v); }
    }
    // anything reachable from v is reachable from u
    reach[u] = min(reach[u], reach[v]);
  }
}

// MUST DO THIS FOR ALGO TO WORK.
void init() {
    fill(preorder, preorder + N, -1);
}
