#pragma once
#include "poly/base.hpp"
#include "poly/divide_at.hpp"
#include "poly/plusminus.hpp"
namespace poly {
template <class mint>
mint linear_rec(vector<mint> a, vector<mint> f, LL n) {
  // a[n] = sum_i f[i] * a[n - i]
  a.resize(f.size() - 1);
  f = 1 - f;
  return divide_at(cut(a * f, (int)a.size()), f, n);
}
}  // namespace poly
