#pragma once
#include "poly/base.hpp"
#include "poly/getdevint.hpp"
#include "poly/getinv.hpp"
#include "poly/header.h"
#include "poly/multiple.hpp"
template <class mint, int g = 3>
vector<mint> getLn(const vector<mint>& a, int lim) {
  assert(a[0] == 1);
  return cut(getInt(getDev(a) * getInv(a, lim)), lim);
}
