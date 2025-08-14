// Lecture Code. Raveen De Silva

#include <bits/stdc++.h>
using namespace std;
#define long long long
#define INF numeric_limits<long>::max()

/*
 * dinic 1
 */

struct FlowNetwork {
    long n;
    vector<vector<long>> adjMat, adjList, is_virtual;
    // level[v] stores dist from s to v
    // uptochild[v] stores first non-useless child.
    vector<long> level, uptochild;

    FlowNetwork (long _n): n(_n) {
        // adjacency matrix is zero-initialised
        adjMat.resize(n);
        is_virtual.resize(n);
        for (long i = 0; i < n; i++) { adjMat[i].resize(n); is_virtual[i].resize(n);}
        adjList.resize(n);
        level.resize(n);
        uptochild.resize(n);
    }

    void add_edge (long u, long v, long c, bool virt) {
        // add to any existing edge without overwriting
        adjMat[u][v] += c;        
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        is_virtual[u][v] = virt;
    }

    void flow_edge (long u, long v, long c) {
        adjMat[u][v] -= c;
        adjMat[v][u] += c;
    }

/*
 * dinic 2
 */

    // constructs the level graph and returns whether the sink is stilong reachable
    bool bfs(long s, long t) {
        fill(level.begin(), level.end(), -1);
        queue<long> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            long u = q.front(); q.pop();
            uptochild[u] = 0; // reset uptochild
            for (long v : adjList[u]) {
                if (adjMat[u][v] > 0) {
                    if (level[v] != -1) { continue; } // already seen
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[t] != -1;
    }

/*
 * dinic 3
 */

    // finds an augmenting path with up to f flow.
    long augment(long u, long t, long f) {
        if (u == t) { return f; } // base case.
        // note the reference here! we increment uptochild[u], i.e. walk through u's neighbours
        // until we find a child that we can flow through
        for (long &i = uptochild[u]; i < adjList[u].size(); i++) {
            long v = adjList[u][i];
            // use only edges in the level graph with remaining capacity
            if (level[v] == level[u] + 1 && adjMat[u][v] > 0) {
                // revised flow is constrained also by this edge
                long rf = augment(v,t,min(f, adjMat[u][v]));
                // found a child we can flow through!
                if (rf > 0) {
                    flow_edge(u,v,rf);
                    return rf;
                }
            }
        }
        level[u] = -1;
        return 0;
    }

/*
 * dinic 4
 */

    long dinic(long s, long t) {
        long res = 0;
        while (bfs(s,t)) {
            while (long x = augment(s, t, INF)) { res += x; }
            // when no further paths, find new level graph
        }
        return res;
    }

/*
 * get min cut
 */
    void check_reach(long u, vector<bool>& seen) {
        if (seen[u]) { return; }
        seen[u] = true;
        for (long v : adjList[u]) {
            if (adjMat[u][v] > 0) { check_reach(v,seen); }
        }
        }

        vector<pair<long,long>> min_cut(long s, long t) {
        long value = dinic(s,t);
        
        vector<bool> seen(n,false);
        check_reach(s,seen);
        
        vector<pair<long,long>> ans;
        for (long u = 0; u < n; u++) {
            if (!seen[u]) { continue; }
            for (long v : adjList[u]) {
            if (!seen[v] && !is_virtual[u][v]) { // need to record this in add_edge()
                ans.emplace_back(u,v);
            }
            }
        }
        return ans;
    }
};




