#pragma once
#include "poly/base.hpp"
#include "poly/getinv.hpp"
#include "poly/multiple.hpp"
#include "poly/plusminus.hpp"
namespace poly {
std::mt19937 rng{std::random_device{}()};
template <class mint>
mint sqrt(const mint &c) {
  auto euler = [&](const mint &x) -> mint {
    return qpow(x, (mint::mod - 1) >> 1);
  };
  if (raw(c) <= 1) return c;
  if (euler(c) != 1) throw "No solution!";
  mint w = rng();
  while (euler(w * w - c) == 1) w = rng();
  struct number {
    mint x, y;
  };
  auto mul = [&](const number &lhs, const number &rhs) -> number {
    return {lhs.x * rhs.x + lhs.y * rhs.y * (w * w - c),
            lhs.x * rhs.y + lhs.y * rhs.x};
  };
  auto qpow = [&](number a, int b) -> number {
    number r = {1, 0};
    for (; b; b >>= 1, a = mul(a, a))
      if (b & 1) r = mul(r, a);
    return r;
  };
  mint ret = qpow({w, 1}, (mint::mod + 1) >> 1).x;
  return std::min(raw(ret), raw(-ret));
}
template <class mint>
vector<mint> getSqrt(const vector<mint> &a, int lim) {
  vector<mint> b{sqrt(a[0])};
  for (int len = 2; len <= glim(lim); len <<= 1) {
    vector<mint> c(a.begin(), a.begin() + std::min(len, (int)a.size()));
    b = cut(c * getInv(b * 2, len) + b / 2, len);
  }
  return cut(b, lim);
}
}  // namespace poly
