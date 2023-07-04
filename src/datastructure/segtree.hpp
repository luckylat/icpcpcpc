#include <bits/stdc++.h>
using namespace std;

template <class S, S (*op)(S, S), S (*e)()>
struct SegmentTree {
  int n_, size, log;
  vector<S> d;

  SegmentTree(): SegmentTree(0) {}
  SegmentTree(int n): SegmentTree(vector<S>(n, e())) {}
  SegmentTree(const vector<S> &v): n_((int)(v.size())) {
    size = bit_ceil(n_);
    log = countr_zero(size);

    d = vector<S>(2 * size, e());
    for (int i = 0; i < n_; i++) {
      d[size + i] = v[i];
    }

    for (int i = size - 1; i >= 1; i--) {
      update(i);
    }
  }

  void set(int p, S x) {
    assert(0 <= p && p < n_);
    p += size;
    d[p] = x;
    for (int i = 1; i <= log; i++) {
      update(p >> i);
    }
  }

  S get(int p) const {
    assert(0 <= p && p < n_);
    return d[p + size];
  }

  S prod(int l, int r) const {
    assert(0 <= l && l <= r && r <= n_);
    S sml = e(), smr = e();
    l += size;
    r += size;

    while (l < r) {
      if (l & 1) {
        sml = op(sml, d[l++]);
      }
      if (r & 1) {
        smr = op(d[--r], smr);
      }
      l >>= 1;
      r >>= 1;
    }
    return op(sml, smr);
  }

  S all_prod() const {
    return d[1];
  }

  template <bool (*f)(S)>
  int max_right(int l) const {
    return max_right(l, [](S x) {
      return f(x);
    });
  }

  template <class F>
  int max_right(int l, F f) const {
    assert(0 <= l && l <= n_);
    assert(f(e()));
    if (l == n_)
      return n_;
    l += size;
    S sm = e();
    do {
      while (l % 2 == 0) {
        l >>= 1;
      }
      if (!f(op(sm, d[l]))) {
        while (l < size) {
          l = (2 * l);
          if (f(op(sm, d[l]))) {
            sm = op(sm, d[l]);
            l++;
          }
        }
        return l - size;
      }
      sm = op(sm, d[l]);
      l++;
    } while ((l & -l) != l);
    return n_;
  }

  template <bool (*f)(S)>
  int min_left(int r) const {
    return min_left(r, [](S x) {
      return f(x);
    });
  }

  template <class F>
  int min_left(int r, F f) const {
    assert(0 <= r && r <= n_);
    assert(f(e()));
    if (r == 0) {
      return 0;
    }
    r += size;
    S sm = e();
    do {
      r--;
      while (r > 1 && (r % 2)) {
        r >>= 1;
      }
      if (!f(op(d[r], sm))) {
        while (r < size) {
          r = (2 * r + 1);
          if (f(op(d[r], sm))) {
            sm = op(d[r], sm);
            r--;
          }
        }
        return r + 1 - size;
      }
      sm = op(d[r], sm);
    } while ((r & -r) != r);
    return 0;
  }

private:
  void update(int k) {
    d[k] = op(d[2 * k], d[2 * k + 1]);
  }

  int countr_zero(unsigned int n) {
    int x = 0;
    while (!(n & (1 << x))) {
      x++;
    }
    return x;
  }

  unsigned int bit_ceil(unsigned int n) {
    unsigned int x = 1;
    while (x < n) {
      x *= 2;
    }
    return x;
  }
};
