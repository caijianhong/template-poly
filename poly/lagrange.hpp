#pragma once
#include "poly/base.hpp"
namespace poly {
namespace internal {
template <class mint>
vector<mint> divide2(vector<mint> a, mint b) {
  vector<mint> res(a.size() - 1);
  for (size_t i = (int)a.size() - 1; i >= 1; i--) {
    res[i - 1] = a[i];
    a[i - 1] -= a[i] * b;
  }
  return res;
}
}  // namespace internal
template <class mint>
vector<mint> lagrange(const vector<std::pair<mint, mint>>& a) {
  vector<mint> ans(a.size()), product{1};
  for (size_t i = 0; i < a.size(); i++) {
    product *= vector<mint>{-a[i].first, 1};
  }
  for (size_t i = 0; i < a.size(); i++) {
    mint denos = 1;
    for (size_t j = 0; j < a.size(); j++) {
      if (i != j) denos *= a[i].first - a[j].first;
    }
    vector<mint> numes = internal::divide2(product, -a[i].first);
    ans += a[i].second / denos * numes;
  }
  return ans;
}
}  // namespace poly
