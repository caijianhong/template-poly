#pragma once
#include "header.h"
template <class mint>
vector<mint> getDev(vector<mint> a) {
  a.erase(a.begin());
  for (int i = 1; i < (int)a.size(); i++) a[i] *= i + 1;
  return a;
}
template <class mint>
vector<mint> getInt(vector<mint> a) {
  a.insert(a.begin(), 0);
  for (int i = 1; i < (int)a.size(); i++) a[i] /= i;
  return a;
}
