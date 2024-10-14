#pragma once
#include "poly/getinv.hpp"
#include "poly/multiple.hpp"
#include "poly/ntt.hpp"
#include "poly/plusminus.hpp"
namespace poly {
template <class mint>
vector<mint> operator/(vector<mint> a, vector<mint> b) {
  if (a.size() < b.size()) return {};
  int rlen = a.size() - b.size() + 1;
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  auto d = cut(a * getInv(b, rlen), rlen);
  reverse(d.begin(), d.end());
  return d;
}
template <class mint>
vector<mint> operator%(const vector<mint>& a, const vector<mint>& b) {
  return cut(a - (a / b) * b, b.size() - 1);
}
template <class mint>
vector<mint> operator/=(vector<mint> a, const vector<mint>& b) {
  return a = a / b;
}
template <class mint>
vector<mint> operator%=(vector<mint> a, const vector<mint>& b) {
  return a = a % b;
}
}  // namespace poly
