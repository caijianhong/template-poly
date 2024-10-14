#pragma once
#include "poly/header.h"
int glim(int x) { return x == 1 ? 1 : 1 << (32 - __builtin_clz(x - 1)); }
int bitctz(int x) { return __builtin_ctz(x); }
template <class mint>
mint getValue(const vector<mint>& a, const mint& x) {
  mint res = 0;
  for (int i = (int)a.size() - 1; i >= 0; i--) {
    res = res * x + a[i];
  }
  return res;
}
template <class mint>
vector<mint> cut(vector<mint> a, int lim) {
  a.resize(lim, 0);
  return a;
}
