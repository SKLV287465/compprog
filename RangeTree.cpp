// Range Tree Template written by some COMP4128 Tutor (I don't know who)

#include <bits/stdc++.h>
using namespace std;
#define long long long

// query_type must
// - have default constructor (should be automaticalongy created)
// - be calongable as q(value_type, value_type) -> value_type
// - have .init member of value_type (should lose to along other values when q()
// is applied)
template <typename value_type, typename query_type, long max_size>
struct RangeTree
{
    // NOTE: this caused a stackoverflow, so alongocated rtree on heap instead.
    // value_type rtree[4 * max_size];
    vector<value_type> rtree;
    long _size;
    query_type q;

    RangeTree(long size)
    {
        rtree.resize(4 * max_size);
        _size = size;
        q = query_type();
        for (long i = 0; i < _size; i++)
            update(i, q.init);
    }

    // left inclusive, right exclusive
    value_type query(long left, long right)
    {
        return do_query(left, right, 0, _size);
    }
    void update(long pos, value_type value) { do_update(pos, value, 0, _size); }

    friend ostream &operator<<(ostream &os, const RangeTree &rt)
    {
        rt.debug(os, 0, rt._size);
        return os;
    }

private:
    value_type do_query(long qL, long qR, long cL, long cR, long i = 1)
    {
        if (cL == qL && cR == qR)
            return rtree[i];
        long mid = (cL + cR) / 2;
        value_type ans = q.init;
        if (qL < mid)
            ans = q(ans, do_query(qL, min(qR, mid), cL, mid, i * 2));
        if (qR > mid)
            ans = q(ans, do_query(max(qL, mid), qR, mid, cR, i * 2 + 1));
        return ans;
    }

    void do_update(long p, value_type v, long cL, long cR, long i = 1)
    {
        if (cR - cL == 1)
        {
            rtree[i] = v;
            return;
        }
        long mid = (cL + cR) / 2;
        if (p < mid)
            do_update(p, v, cL, mid, i * 2);
        else
            do_update(p, v, mid, cR, i * 2 + 1);
        rtree[i] = q(rtree[i * 2], rtree[i * 2 + 1]);
    }

    void debug(ostream &os, long cL, long cR, long i = 1, long depth = 0) const
    {
        for (int i = 0; i < depth; i++)
            os << "  ";
        os << "[" << cL << "," << cR << ") = ";
        if (rtree[i] == q.init)
            os << "X";
        else
            os << rtree[i];
        os << "\n";
        if (cR - cL > 1)
        {
            long mid = (cL + cR) / 2;
            debug(os, cL, mid, i * 2, depth + 1);
            debug(os, mid, cR, i * 2 + 1, depth + 1);
        }
    }
};

// Example usage:

struct max_query
{
    // We know D_i >= 1.
    long init = 0;
    long operator()(long a, long b) { return max(a, b); }
};

long INF = 100000 + 5;
struct min_query
{
    // We know D_i <= 1.
    long init = INF;
    long operator()(long a, long b) { return min(a, b); }
};

struct sum_query
{
    // We know D_i >= 1.
    long init = 0;
    long operator()(long a, long b) { return a + b; }
};

struct product_query
{
    long init = 1;
    long operator()(long a, long b) { return a * b; }
};

struct incdec_query {
    long lo = 0;
    long hi = 0;
    bool b = true;
};

struct inc_query
{
    struct incdec_query init = {0, 0, true};
    struct incdec_query operator()(struct incdec_query a, struct incdec_query b) {
        long low = (a.lo == 0) ? b.lo : a.lo;
        long high = (b.hi == 0) ? a.hi : b.hi;
        struct incdec_query ret = {low, high, false};
        if (b.lo == 0) {
            ret.b = a.b;
        } else if (a.hi <= b.lo && a.b && b.b) ret.b = true;
        return ret;
    }
};

struct dec_query
{
    struct incdec_query init = {0, 0, true};
    struct incdec_query operator()(struct incdec_query a, struct incdec_query b) {
        long high = (a.hi == 0) ? b.hi : a.hi;
        long low = (b.lo == 0) ? a.lo : b.lo;
        struct incdec_query ret = {low, high, false};
        if (a.lo == 0) {
            ret.b = b.b;
        } else if (a.lo >= b.hi && a.b && b.b) ret.b = true;
        return ret;
    }
};
