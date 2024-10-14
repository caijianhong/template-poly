#pragma once
#include "poly/getinv.hpp"
#include "poly/multiple.hpp"
#include "poly/ntt.hpp"
#include "poly/plusminus.hpp"
namespace poly {
template <class mint>
vector<mint>& operator/=(vector<mint>& a, vector<mint> b) {
  if (a.size() < b.size()) return a.clear(), a;
  int rlen = (int)(a.size() - b.size() + 1);
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  a *= getInv(b, rlen);
  a.resize(rlen);
  reverse(a.begin(), a.end());
  return a;
}
template <class mint>
vector<mint>& operator%=(vector<mint>& a, const vector<mint>& b) {
  a -= (a / b) * b;
  a.resize(b.size() - 1);
  return a;
}
template <class mint>
vector<mint> operator/(vector<mint> a, const vector<mint>& b) {
  return a /= b;
}
template <class mint>
vector<mint> operator%(vector<mint> a, const vector<mint>& b) {
  return a %= b;
}
}  // namespace poly
