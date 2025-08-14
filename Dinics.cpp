// Lecture code, Raveen de Silva
#include <bits/stdc++.h>
using namespace std;

struct FlowEdge {
    long v, u;
    long cap, flow = 0;
    FlowEdge(long v, long u, long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<long>> adj;
    long n, m = 0;
    long s, t;
    vector<long> level, ptr;
    queue<long> q;

    /**
     * n: number of nodes
     * s: source node
     * t: sink node
     */
    Dinic(long n, long s, long t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(long v, long u, long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            long v = q.front();
            q.pop();
            for (long id : adj[v]) {
                if (edges[id].cap == edges[id].flow)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long dfs(long v, long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (long& cid = ptr[v]; cid < (long)adj[v].size(); cid++) {
            long id = adj[v][cid];
            long u = edges[id].u;
            if (level[v] + 1 != level[u])
                continue;
            long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long flow() {
        long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};
