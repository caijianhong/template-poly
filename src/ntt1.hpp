#pragma once
#include "base.hpp"
#include "header.h"
template <class mint, int g>
struct ntt_env {
  vector<mint> w{1};
  void init(int n) {
    w.reserve(n);
    while ((int)w.size() < n) {
      int m = w.size();
      mint wn = qpow(mint(g), (mint::mod - 1) / m >> 2);
      w.resize(m << 1);
      for (int i = m; i < m << 1; i++) w[i] = wn * w[i ^ m];
    }
  }
  void dif(vector<mint> &a) {
    int n = a.size();
    init(n);
    for (int len = n, k = n >> 1; k >= 1; len = k, k >>= 1) {
      for (int i = 0, t = 0; i < n; i += len, t++) {
        for (int j = 0; j < k; j++) {
          mint x = a[i + j], y = a[i + j + k] * w[t];
          a[i + j] = x + y, a[i + j + k] = x - y;
        }
      }
    }
  }
  void dit(vector<mint> &a) {
    int n = a.size();
    init(n);
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
  }
};
template <class mint, int g = 3 ,class Func>
vector<mint> concalc(int n, vector<vector<mint>> vec, Func&& func) {
  static ntt_env<mint, g> ntt;
  int lim = glim(n);
  int m = vec.size();
  for (int j = 0; j < m; j++) vec[j].resize(lim), ntt.dif(vec[j]);
  vector<mint> tmp(m), ret(lim);
  for (int i = 0; i < lim; i++) {
    for (int j = 0; j < m; j++) tmp[j] = move(vec[j][i]);
    ret[i] = func(tmp);
  }
  ntt.dit(ret);
  return ret;
}
