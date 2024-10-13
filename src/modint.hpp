#pragma once
#include "header.h"
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
    v = 1ull * v * rhs.v % umod;
    return *this;
  }
  modint &operator/=(const modint &rhs) { return *this *= rhs.inv(); }
  modint inv() const {
    assert(v);
    static unsigned lim = 1 << 21;
    static vector<modint> inv{0, 1};
    if (v >= lim) return qpow(*this, mod - 2);
    inv.reserve(v + 1);
    while (v >= inv.size()) {
      int m = inv.size();
      inv.resize(m << 1);
      for (int i = m; i < m << 1; i++) {
        inv[i] = (mod - mod / i) * inv[mod % i];
      }
    }
    return inv[v];
  }
  template <class T, must_int<T> = 0>
  friend modint qpow(modint a, T b) {
    modint r = 1;
    for (; b; b >>= 1, a *= a)
      if (b & 1) r *= a;
    return r;
  }
  friend modint operator+(modint lhs, const modint &rhs) { return lhs += rhs; }
  friend modint operator-(modint lhs, const modint &rhs) { return lhs -= rhs; }
  friend modint operator*(modint lhs, const modint &rhs) { return lhs *= rhs; }
  friend modint operator/(modint lhs, const modint &rhs) { return lhs /= rhs; }
  bool operator==(const modint &rhs) const { return v == rhs.v; }
  bool operator!=(const modint &rhs) const { return v != rhs.v; }
  explicit operator bool() const { return v != 0; }
};
