#pragma once
#include "header.h"
int glim(const int& x) { return 1 << (32 - __builtin_clz(x - 1)); }
int bitctz(const int& x) { return __builtin_ctz(x); }
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
  a.resize(lim);
  return a;
}
