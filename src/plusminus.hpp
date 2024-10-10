#pragma once
#include "header.h"
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
template <class mint>
vector<mint> operator+=(vector<mint>& a, const vector<mint>& b) {
  return a = move(a + b);
}
template <class mint>
vector<mint> operator-=(vector<mint>& a, const vector<mint>& b) {
  return a = move(a - b);
}
