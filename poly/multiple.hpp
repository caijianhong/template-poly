#pragma once
#include "poly/ntt.hpp"
namespace poly {
template <class mint>
vector<mint> operator*(const vector<mint>& a, const vector<mint>& b) {
  int rlen = (int)(a.size() + b.size() - 1), len = glim(rlen);
  return cut(dit(dif(a, len) * dif(b, len)), rlen);
}
}  // namespace poly
