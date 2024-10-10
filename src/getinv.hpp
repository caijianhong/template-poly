#pragma once
#include "header.h"
#include "ntt.hpp"
template <class mint, int g = 3>
vector<mint> getInv(const vector<mint>& a, int lim) {
  vector<mint> b{1 / a[0]};
  for (int len = 2; len <= glim(lim); len <<= 1) {
    vector<mint> c(a.begin(), a.begin() + min(len, (int)a.size()));
    auto func = [](auto&& vec) { return vec[0] * vec[1]; };
    c = concalc<mint, g>(len, {b, c}, func);
    for (int i = 0; i < len >> 1; i++) c[i] = 0;
    c = concalc<mint, g>(len, {b, c}, func);
    b.resize(len);
    for (int i = len >> 1; i < len; i++) b[i] = -c[i];
  }
  return cut(b, lim);
}
