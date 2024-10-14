#pragma once
#include "poly/base.hpp"
#include "poly/internal_math.hpp"
namespace poly {
namespace internal {
template <class mint>
vector<mint> wt;
template <class mint>
vector<mint>& init(int n) {
  assert((n & (n - 1)) == 0);
  static constexpr int g = internal::pmtroot(mint::mod);
  auto& w = wt<mint>;
  if (w.empty()) w = {1};
  while ((int)w.size() < n) {
    int m = (int)w.size();
    mint wn = qpow(mint(g), (mint::mod - 1) / m >> 2);
    w.resize(m << 1);
    for (int i = m; i < m << 1; i++) w[i] = wn * w[i ^ m];
  }
  return w;
}
}  // namespace internal
template <class mint>
valarray<mint> dif(const vector<mint>& src, int n) {
  auto& w = internal::init<mint>(n);
  valarray<mint> a;
  a.resize(n, 0);
  std::memcpy(&a[0], &src[0], sizeof(mint) * std::min(n, (int)src.size()));
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
auto dit(T&& _src) {
  using mint = typename T::value_type;
  valarray<mint> src = _src;
  int n = (int)src.size();
  auto& w = internal::init<mint>(n);
  vector<mint> a(begin(src), end(src));
  for (int k = 1, len = 2; len <= n; k = len, len <<= 1) {
    for (int i = 0, t = 0; i < n; i += len, t++) {
      for (int j = 0; j < k; j++) {
        mint x = a[i + j], y = a[i + j + k];
        a[i + j] = x + y, a[i + j + k] = (x - y) * w[t];
      }
    }
  }
  mint iv = mint{1} / n;
  for (int i = 0; i < n; i++) a[i] *= iv;
  std::reverse(a.begin() + 1, a.end());
  return a;
}
template <class Func, class... Ts>
auto concalc(int len, Func&& func, Ts... args) {
  return dit(func(dif(args, len)...));
}
}  // namespace poly
