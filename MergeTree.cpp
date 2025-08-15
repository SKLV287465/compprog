// Made referencing Raveen's range Tree


#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
#define long long long
using namespace std;

class MergeTree {
public:
    MergeTree(const vector<long>& values) {
        _tree.resize(4 * values.size()); // default initialised (might be a problem)
        build(0, values.size(), values);
    }

    long query(long value, long left, long right, long cL, long cR, long i = 1) {
        if (cL == left and cR == right) return lower_bound(_tree[i].begin(), _tree[i].end(), value, greater<long>()) - _tree[i].begin();
        long mid = (cL + cR) / 2;
        long ans = 0;
        if (left < mid) {
            ans = query(value, left, min(right, mid), cL, mid, i * 2); 
        } 
        if (right > mid) {
            ans += query(value, max(left, mid), right, mid, cR, i * 2 + 1);
        }
        return ans;
    }
private:
    void build(long cL, long cR, const vector<long>& values, long i = 1) {
        if (cR - cL == 1) {
            _tree[i] = {values[cL]};
            return;
        }
        long mid = (cR + cL) / 2;
        build(cL, mid, values, i * 2);
        build(mid, cR, values, i* 2 + 1);
        _tree[i] = merge(_tree[i * 2], _tree[i * 2 + 1]);
    }
    vector<long> merge(const vector<long>& a, const vector<long>& b) {
        vector<long> combined;
        combined.reserve(a.size() + b.size());
        long i = 0, j = 0;
        while (i < a.size() && j < b.size()) {
            if (a[i] >= b[j]) {
                combined.push_back(a[i++]);
            } else {
                combined.push_back(b[j++]);
            }
        }
        while (i < a.size()) combined.push_back(a[i++]);
        while (j < b.size()) combined.push_back(b[j++]);
        return combined;
    }
    vector<vector<long>> _tree;
};
