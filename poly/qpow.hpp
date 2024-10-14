#pragma once
#include "getexp.hpp"
#include "getln.hpp"
#include "header.h"
#include "modint.hpp"
template <class mint>
vector<mint> qpow_base(vector<mint> a, int km, int ke, int lim) {
  assert(a[0] != 0);
  mint coek = qpow(a[0], ke), icoe = 1 / a[0];
  for (int i = 0; i < (int)a.size(); i++) a[i] *= icoe;
  a = getLn(a, lim);
  for (int i = 0; i < lim; i++) a[i] *= km;
  a = getExp(a, lim);
  for (int i = 0; i < lim; i++) a[i] *= coek;
  return a;
}
template <class mint>
vector<mint> qpow(vector<mint> a, LL k, int lim) {
  int i =
      find_if(a.begin(), a.end(), [](mint x) { return x != 0; }) - a.begin();
  if (i == (int)a.size() || (i >= 1 && (k >= lim || i * k >= lim)))
    return vector<mint>(lim);
  if (i) a.erase(a.begin(), a.begin() + i);
  auto ret = qpow_base(a, k % mint::mod, k % (mint::mod - 1), lim);
  if (i) ret.insert(ret.begin(), i * k, 0);
  return ret;
}
template <class mint>
vector<mint> qpow(vector<mint> a, string k, int lim) {
  int i =
      find_if(a.begin(), a.end(), [](mint x) { return x != 0; }) - a.begin();
  if (i == (int)a.size() ||
      (i >= 1 && (k.size() > to_string(lim).size() || i * stoll(k) >= lim)))
    return vector<mint>(lim);
  if (i) a.erase(a.begin(), a.begin() + i);
  LL km = 0, ke = 0;
  for (int i = 0; i < (int)k.size(); i++) {
    km = (km * 10 + k[i] - '0') % mint::mod;
    ke = (ke * 10 + k[i] - '0') % (mint::mod - 1);
  }
  auto ret = qpow_base(a, km, ke, lim);
  if (i) ret.insert(ret.begin(), i * stoll(k), 0);
  return ret;
}
