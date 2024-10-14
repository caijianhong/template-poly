#pragma once
#include "base.hpp"
#include "getdevint.hpp"
#include "getinv.hpp"
#include "header.h"
#include "multiple.hpp"
template <class mint, int g = 3>
vector<mint> getLn(const vector<mint>& a, int lim) {
  assert(a[0] == 1);
  return cut(getInt(getDev(a) * getInv(a, lim)), lim);
}
