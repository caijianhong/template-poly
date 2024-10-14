#pragma once
#include "poly/ntt.hpp"
namespace poly {
template <class mint>
vector<mint>& operator*=(vector<mint>& a, const vector<mint>& b) {
  if (a.empty() || b.empty()) return a.clear(), a;
  int rlen = (int)(a.size() + b.size() - 1), len = glim(rlen);
  if (std::min(a.size(), b.size()) <= 20) {
    vector<mint> ret(rlen, 0);
    for (int i = 0; i < (int)a.size(); i++) {
      for (int j = 0; j < (int)b.size(); j++) ret[i + j] += a[i] * b[j];
    }
    a = move(ret);
  } else {
    a = dit(dif(a, len) * dif(b, len));
    a.resize(rlen);
  }
  return a;
}
template <class mint>
vector<mint> operator*(vector<mint> a, const vector<mint>& b) {
  return a *= b;
}
}  // namespace poly
