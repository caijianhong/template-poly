#pragma once
#include "poly/base.hpp"
#include "poly/multiple.hpp"
namespace poly {
template <class mint>
mint divide_at(vector<mint> f, vector<mint> g, LL n) {
  for (; n; n >>= 1) {
    auto r = g;
    for (int i = 1; i < (int)r.size(); i += 2) r[i] *= -1;
    f *= r, g *= r;
    for (int i = n & 1; i < (int)f.size(); i += 2) f[i >> 1] = f[i];
    f.resize((f.size() + 1) >> 1);
    for (int i = 0; i < (int)g.size(); i += 2) g[i >> 1] = g[i];
    g.resize((g.size() + 1) >> 1);
  }
  return f.empty() ? 0 : f[0] / g[0];
}
}  // namespace poly
