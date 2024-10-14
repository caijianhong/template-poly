#pragma once
#include "poly/ntt.hpp"
namespace poly {
template <class mint>
vector<mint> getInv(const vector<mint>& a, int lim) {
  vector<mint> b{1 / a[0]};
  for (int len = 2; len <= glim(lim); len <<= 1) {
    vector<mint> c(a.begin(), a.begin() + std::min(len, (int)a.size()));
    auto difb = dif(b, len);
    c = dit(dif(c, len) * difb);
    for (int i = 0; i < len >> 1; i++) c[i] = 0;
    c = dit(dif(c, len) * difb);
    b.resize(len);
    for (int i = len >> 1; i < len; i++) b[i] = -c[i];
  }
  return cut(b, lim);
}
}  // namespace poly
