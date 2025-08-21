#include <bits/stdc++.h>
#include <deque>
#define long long long
using namespace std;

class MonotonicWindowQueue {
public:
    MonotonicWindowQueue(long size) {
        _size = size;
    }

    void insert(long x) {
        // remove old
        while (!dq.empty() && dq.front().second + _size < cur) dq.pop_front();

        while (!dq.empty() && x < dq.back()) {
            dq.pop_back();
        }
        

        ++cur;
    }
    
    long top() {
        return dq.front();
    }

    //long pop() {

    //}
private:
    deque<pair<long, long>> dq; // num first, id second.
    size_t _size;
    long cur;
}
