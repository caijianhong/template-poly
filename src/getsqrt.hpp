#pragma once
#include "base.hpp"
#include "header.h"
#include "ntt.hpp"
#include "getinv.hpp"
#include "multiple.hpp"
#include "plusminus.hpp"
template <class mint>
mint sqrt(const mint& c) {
  static const auto check = [](mint c) {
    return qpow(c, (mint::mod - 1) >> 1) == 1;
  };
  if (raw(c) <= 1) return 1;
  if (!check(c)) throw "No solution!";
  static mt19937 rng{random_device{}()};
  mint a = rng();
  while (check(a * a - c)) a = rng();
  typedef pair<mint, mint> number;
  const auto mul = [=](number x, number y) {
    return make_pair(x.first * y.first + x.second * y.second * (a * a - c),
                     x.first * y.second + x.second * y.first);
  };
  const auto qpow = [=](number a, int b) {
    number r = {1, 0};
    for (; b; b >>= 1, a = mul(a, a))
      if (b & 1) r = mul(r, a);
    return r;
  };
  mint ret = qpow({a, 1}, (mint::mod + 1) >> 1).first;
  return min(raw(ret), raw(-ret));
}
template <class mint, int g = 3>
vector<mint> getSqrt(const vector<mint>& a, int lim) {
  vector<mint> b{sqrt(a[0])};
  for (int len = 2; len <= glim(lim); len <<= 1) {
    vector<mint> c(a.begin(), a.begin() + min(len, (int)a.size()));
    b = cut(multiple<mint, g>(c, getInv<mint, g>(b * 2, len)) + b / 2, len);
  }
  return cut(b, lim);
}
