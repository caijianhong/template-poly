#pragma once
#include "base.hpp"
#include "getdevint.hpp"
#include "getln.hpp"
#include "header.h"
#include "ntt.hpp"
template <class mint, int g = 3>
vector<mint> getExp(const vector<mint>& a, int lim) {
  assert(a[0] == 0);
  vector<mint> b{1};
  for (int len = 2; len <= glim(lim); len <<= 1) {
    vector<mint> c =
        vector<mint>(a.begin(), a.begin() + min(len, (int)a.size()));
    auto func = [](auto&& vec) { return vec[0] * (1 - vec[1] + vec[2]); };
    b = cut(concalc<mint, g>(len << 1, {b, getLn(b, len), c}, func), len);
  }
  return cut(b, lim);
}
