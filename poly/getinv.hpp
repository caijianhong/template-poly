#pragma once
#include "header.h"
#include "ntt.hpp"
template <class mint, int g = 3>
vector<mint> getInv(const vector<mint>& a, int lim) {
  vector<mint> b{1 / a[0]};
  for (int len = 2; len <= glim(lim); len <<= 1) {
    vector<mint> c(a.begin(), a.begin() + min(len, (int)a.size()));
    auto func = [](vector<mint> vec) { return vec[0] * (2 - vec[0] * vec[1]); };
    b = cut(concalc<mint, g>(len << 1, {b, c}, func), len);
  }
  return cut(b, lim);
}
