#pragma once
#include "header.h"
#ifndef NTT_VERSION
#define NTT_VERSION 1
#endif
#if NTT_VERSION == 0
#include "ntt0.hpp"
#elif NTT_VERSION == 1
#include "ntt1.hpp"
#elif
#error "invaild argument: NTT_VERSION"
#endif
template <class mint>
vector<mint> operator+(vector<mint> a, const vector<mint>& b) {
  if (a.size() < b.size()) a.resize(b.size());
  for (int i = 0; i < (int)b.size(); i++) a[i] += b[i];
  return a;
}
template <class mint>
vector<mint> operator-(vector<mint> a, const vector<mint>& b) {
  if (a.size() < b.size()) a.resize(b.size());
  for (int i = 0; i < (int)b.size(); i++) a[i] -= b[i];
  return a;
}
template <class mint, int g = 3>
vector<mint> multiple(const vector<mint>& a, const vector<mint>& b) {
  int rlen = a.size() + b.size() - 1;
  auto func = [](vector<mint> vec) -> mint { return vec[0] * vec[1]; };
  auto ret = concalc<mint, 3>(rlen, {a, b}, func);
  return cut(ret, rlen);
}
template <class mint>
vector<mint> operator+=(vector<mint>& a, const vector<mint>& b) { return a = move(a + b); }
template <class mint>
vector<mint> operator-=(vector<mint>& a, const vector<mint>& b) { return a = move(a - b); }
