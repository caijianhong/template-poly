#pragma once
#include "header.h"
#include "internal_math.hpp"
template <unsigned umod>
struct modint {
  static constexpr int mod = umod;
  unsigned v;
  modint() = default;
  template <class T, enable_if_t<is_integral<T>::value, int> = 0>
    modint(const T& _y) : v(_y % mod + (is_signed<T>() && _y < 0 ? mod : 0)) {}
  modint operator+() const { return *this; }
  modint operator-() const { return modint() - *this; }
  friend int raw(const modint &self) { return self.v; }
  friend ostream &operator<<(ostream &os, const modint &self) {
    return os << raw(self);
  }
  modint &operator+=(const modint &rhs) {
    v += rhs.v;
    if (v >= umod) v -= umod;
    return *this;
  }
  modint &operator-=(const modint &rhs) {
    v -= rhs.v;
    if (v >= umod) v += umod;
    return *this;
  }
  modint &operator*=(const modint &rhs) {
    v = (unsigned)(1ull * v * rhs.v % umod);
    return *this;
  }
  modint &operator/=(const modint &rhs) {
    int v = rhs.v;
    assert(v > 0);
    if (poly_internal::isprime(mod)) {
      static constexpr int lim = 1 << 21;
      static vector<modint> inv{0, 1};
      while (v >= lim) *this *= mod - mod / v, v = mod % v;
      while (v >= (int)inv.size()) {
        int m = (int)inv.size();
        inv.resize(m << 1);
        for (int i = m; i < m << 1; i++) inv[i] = (mod - mod / i) * inv[mod % i];
      }
      v = raw(inv[v]);
    } else {
      auto ret = poly_internal::exgcd(v, mod);
      assert(get<2>(ret) == 1);
      v = get<0>(ret);
    }
    return *this *= v;
  }
  friend modint qpow(modint a, LL b) {
    if (b < 0) b = -b, a = 1 / a;
    modint r = 1;
    for (; b; b >>= 1, a *= a) if (b & 1) r *= a;
    return r;
  }
  friend modint operator+(modint lhs, const modint &rhs) { return lhs += rhs; }
  friend modint operator-(modint lhs, const modint &rhs) { return lhs -= rhs; }
  friend modint operator*(modint lhs, const modint &rhs) { return lhs *= rhs; }
  friend modint operator/(modint lhs, const modint &rhs) { return lhs /= rhs; }
  friend bool operator==(const modint& lhs, const modint &rhs) { return lhs.v == rhs.v; }
  friend bool operator!=(const modint& lhs, const modint &rhs) { return lhs.v != rhs.v; }
  explicit operator bool() const { return v != 0; }
};
