#pragma once
#include "poly/base.hpp"
#include "poly/header.h"
#include "poly/ntt.hpp"
#include "poly/getinv.hpp"
#include "poly/multiple.hpp"
#include "poly/plusminus.hpp"
#include "poly/internal_math.hpp"
template <class mint>
vector<mint> getSqrt(const vector<mint>& a, int lim) {
  vector<mint> b{poly_internal::sqrt(a[0])};
  for (int len = 2; len <= glim(lim); len <<= 1) {
    vector<mint> c(a.begin(), a.begin() + min(len, (int)a.size()));
    b = cut(c * getInv(b * 2, len) + b / 2, len);
  }
  return cut(b, lim);
}
