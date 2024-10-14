#pragma once
#include "poly/base.hpp"
#include "poly/getinv.hpp"
#include "poly/internal_math.hpp"
#include "poly/multiple.hpp"
#include "poly/ntt.hpp"
#include "poly/plusminus.hpp"
namespace poly {
template <class mint>
vector<mint> getSqrt(const vector<mint>& a, int lim) {
  vector<mint> b{internal::sqrt(a[0])};
  for (int len = 2; len <= glim(lim); len <<= 1) {
    vector<mint> c(a.begin(), a.begin() + std::min(len, (int)a.size()));
    b = cut(c * getInv(b * 2, len) + b / 2, len);
  }
  return cut(b, lim);
}
}  // namespace poly
