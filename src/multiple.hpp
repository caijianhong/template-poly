#pragma once
#include "header.h"
#include "ntt.hpp"
template <class mint>
vector<mint> operator*(const vector<mint>& a, const vector<mint>& b) {
  int rlen = a.size() + b.size() - 1, len = glim(rlen);
  return dit(dif(a, len) * dif(b, len), rlen);
}
