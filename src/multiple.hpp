#pragma once
#include "header.h"
#include "ntt.hpp"
template <class mint, int g = 3>
vector<mint> multiple(const vector<mint>& a, const vector<mint>& b) {
  int rlen = a.size() + b.size() - 1;
  auto func = [](auto&& vec) -> mint { return vec[0] * vec[1]; };
  auto ret = concalc<mint, g>(rlen, {a, b}, func);
  return cut(ret, rlen);
}
