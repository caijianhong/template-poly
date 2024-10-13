#pragma once
#include "base.hpp"
#include "header.h"
template <class mint, int g = 3>
void ntt(vector<mint>& a, int op) {
  static vector<mint> wns;
  if (wns.empty()) {
    for (int j = 1; j <= 23; j++) {
      wns.push_back(qpow(mint(g), (mint::mod - 1) >> j));
    }
  }
  int n = a.size();
  for (int i = 1, r = 0; i < n; i++) {
    r ^= n - (1 << (bitctz(n) - bitctz(i) - 1));
    if (i < r) swap(a[i], a[r]);
  }
  vector<mint> w(n);
  for (int k = 1, len = 2; len <= n; k <<= 1, len <<= 1) {
    mint wn = wns[bitctz(k)];
    w[0] = 1;
    for (int i = 1; i < k; i++) w[i] = w[i - 1] * wn;
    for (int i = 0; i < n; i += len) {
      for (int j = 0; j < k; j++) {
        mint x = a[i + j], y = a[i + j + k] * w[j];
        a[i + j] = x + y, a[i + j + k] = x - y;
      }
    }
  }
  if (op == -1) {
    reverse(a.begin() + 1, a.end());
    for (int i = 0; i < n; i++) a[i] /= n;
  }
}
template <class mint, int g = 3, class Func>
vector<mint> concalc(int n, vector<vector<mint>> vec, Func&& func) {
  int lim = glim(n);
  int m = vec.size();
  for (int j = 0; j < m; j++) vec[j].resize(lim), ntt(vec[j], 1);
  vector<mint> tmp(m), ret(lim);
  for (int i = 0; i < lim; i++) {
    for (int j = 0; j < m; j++) tmp[j] = move(vec[j][i]);
    ret[i] = func(tmp);
  }
  ntt(ret, -1);
  return ret;
}
