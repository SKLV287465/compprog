#include <bits/stdc++.h>
#define long long long
using namespace std;

class UnionFind {
    vector<long> rank, parent;

public:
  
    // Constructor to initialize sets
    UnionFind(long n) {
        rank.resize(n, 0);
        parent.resize(n);

        // Initially, each element is in its own set
        for (long i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find the representative of the set that x belongs to
    long find(long i) {
        long root = parent[i];
      
        if (parent[root] != root) {
            return parent[i] = find(root);
        }
      
        return root;
    }

    // Union of sets containing x and y, returns new root.
    long unite(long x, long y) {
        long xRoot = find(x);
        long yRoot = find(y);

        // If they are in the same set, no need to union
        if (xRoot == yRoot) return;

        // Union by rank
        if (rank[xRoot] < rank[yRoot]) {
            parent[xRoot] = yRoot;
            return yRoot;
        } else if (rank[yRoot] < rank[xRoot]) {
            parent[yRoot] = xRoot;
            return xRoot;
        } else {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
            return xRoot;
        }
    }
};