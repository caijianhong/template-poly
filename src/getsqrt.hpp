#pragma once
#include "base.hpp"
#include "header.h"
#include "ntt.hpp"
#include "getinv.hpp"
#include "multiple.hpp"
#include "plusminus.hpp"
#include "internal_math.hpp"
template <class mint>
vector<mint> getSqrt(const vector<mint>& a, int lim) {
  vector<mint> b{poly_internal::sqrt(a[0])};
  for (int len = 2; len <= glim(lim); len <<= 1) {
    vector<mint> c(a.begin(), a.begin() + min(len, (int)a.size()));
    b = cut(c * getInv(b * 2, len) + b / 2, len);
  }
  return cut(b, lim);
}
