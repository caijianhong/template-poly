#pragma once
#include "poly/header.h"
#include "poly/ntt.hpp"
template <class mint>
vector<mint> getInv(const vector<mint>& a, int lim) {
  vector<mint> b{1 / a[0]};
  for (int len = 2; len <= glim(lim); len <<= 1) {
    vector<mint> c(a.begin(), a.begin() + min(len, (int)a.size()));
    auto func = [&](auto&& vb, auto&& vc) { return vb * (2 - vc * vb); };
    b = cut(concalc(len << 1, func, b, c), len);
  }
  return cut(b, lim);
}
