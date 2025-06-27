#include <bits/stdc++.h>
#define long long long
using namespace std;

long find(long a, vector<long>& parent) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = find(parent[a], parent);
}

// find(a) is always the new root.
void unite(long a, long b, vector<long>& parent) {
    if (a == b) {
        return;
    }
    a = find(a, parent);
    b = find(b, parent);
    parent[b] = a;
}