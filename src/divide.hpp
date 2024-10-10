#pragma once
#include "getinv.hpp"
#include "header.h"
#include "multiple.hpp"
#include "ntt.hpp"
#include "plusminus.hpp"
template <class mint, int g = 3>
auto divide(vector<mint> a, vector<mint> b) {
  if (a.size() < b.size()) return pair<vector<mint>, vector<mint>>{};
  int rlen = a.size() - b.size() + 1;
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  auto d = cut(multiple<mint, g>(a, getInv<mint, g>(b, rlen)), rlen);
  reverse(d.begin(), d.end());
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  auto r = cut(a - multiple<mint, g>(d, b), b.size() - 1);
  return make_pair(d, r);
}
