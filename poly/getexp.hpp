#pragma once
#include "base.hpp"
#include "getdevint.hpp"
#include "getln.hpp"
#include "header.h"
#include "ntt.hpp"
template <class mint>
vector<mint> getExp(const vector<mint>& a, int lim) {
  assert(a[0] == 0);
  vector<mint> b{1};
  for (int len = 2; len <= glim(lim); len <<= 1) {
    vector<mint> c(a.begin(), a.begin() + min(len, (int)a.size()));
    auto func = [](auto&& v0, auto&& v1, auto&& v2) { return v0 * (1 - v1 + v2); };
    b = cut(concalc(len << 1, func, b, getLn(b, len), c), len);
  }
  return cut(b, lim);
}