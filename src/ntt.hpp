#pragma once
#include "base.hpp"
#include "header.h"
#include "internal_math.hpp"
template <class mint>
void init(vector<mint>& w, int n) {
  static constexpr int g = poly_internal::pmtroot(mint::mod);
  while ((int)w.size() < n) {
    int m = w.size();
    mint wn = qpow(mint(g), (mint::mod - 1) / m >> 2);
    w.resize(m << 1);
    for (int i = m; i < m << 1; i++) w[i] = wn * w[i ^ m];
  }
}
template <class mint>
valarray<mint> dif(const vector<mint>& src, int n) {
  static vector<mint> w{1};
  init(w, n);
  valarray<mint> a(0, n);
  copy(src.begin(), src.end(), begin(a));
  for (int len = n, k = n >> 1; k >= 1; len = k, k >>= 1) {
    for (int i = 0, t = 0; i < n; i += len, t++) {
      for (int j = 0; j < k; j++) {
        mint x = a[i + j], y = a[i + j + k] * w[t];
        a[i + j] = x + y, a[i + j + k] = x - y;
      }
    }
  }
  return a;
}
template <class T>
auto dit(T&& _src, int m) {
  using mint = typename T::value_type;
  valarray<mint> src = _src;
  int n = (int)src.size();
  static vector<mint> w{1};
  init(w, n);
  vector<mint> a(begin(src), end(src));
  for (int k = 1, len = 2; len <= n; k = len, len <<= 1) {
    for (int i = 0, t = 0; i < n; i += len, t++) {
      for (int j = 0; j < k; j++) {
        mint x = a[i + j], y = a[i + j + k];
        a[i + j] = x + y, a[i + j + k] = (x - y) * w[t];
      }
    }
  }
  mint iv = mint(1) / n;
  for (int i = 0; i < n; i++) a[i] *= iv;
  reverse(a.begin() + 1, a.end());
  a.resize(m);
  return a;
}
template <class Func, class... Ts>
auto concalc(int len, Func&& func, Ts... args) {
  return dit(func(dif(args, len)...), len);
}
