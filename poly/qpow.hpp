#pragma once
#include "poly/getexp.hpp"
#include "poly/getln.hpp"
#include "poly/modint.hpp"
namespace poly {
namespace internal {
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
}  // namespace internal
template <class mint>
vector<mint> qpow(vector<mint> a, LL k, int lim) {
  auto chk = [](mint x) { return x != 0; };
  int i = (int)(std::find_if(a.begin(), a.end(), chk) - a.begin());
  if (i == (int)a.size() || (i >= 1 && (k >= lim || i * k >= lim)))
    return vector<mint>(lim, 0);
  if (i) a.erase(a.begin(), a.begin() + i);
  auto ret = internal::qpow_base(a, k % mint::mod, k % (mint::mod - 1), lim);
  if (i) ret.insert(ret.begin(), i * k, 0);
  return ret;
}
template <class mint>
vector<mint> qpow(vector<mint> a, std::string k, int lim) {
  auto chk = [](mint x) { return x != 0; };
  int i = (int)(std::find_if(a.begin(), a.end(), chk) - a.begin());
  if (i == (int)a.size() || (i >= 1 && (k.size() > std::to_string(lim).size() ||
                                        i * stoll(k) >= lim)))
    return vector<mint>(lim, 0);
  if (i) a.erase(a.begin(), a.begin() + i);
  LL km = 0, ke = 0;
  for (char ch : k) {
    km = (km * 10 + ch - '0') % mint::mod;
    ke = (ke * 10 + ch - '0') % (mint::mod - 1);
  }
  auto ret = internal::qpow_base(a, (int)km, (int)ke, lim);
  if (i) ret.insert(ret.begin(), i * stoll(k), 0);
  return ret;
}
}  // namespace poly
