#pragma once
#include "poly/base.hpp"
#include "poly/internal_math.hpp"
namespace poly {
template <unsigned umod>
struct modint {
  static constexpr int mod = umod;
  unsigned v;
  modint() = default;
  template <class T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
  modint(const T &_y)
      : v((unsigned)(_y % mod + (std::is_signed<T>() && _y < 0 ? mod : 0))) {}
  modint operator+() const { return *this; }
  modint operator-() const { return modint::raw(v ? mod - v : 0); }
  friend int raw(const modint &self) { return self.v; }
  static modint raw(int _y) { mint x; x.v = _y; return x; }
  friend std::ostream &operator<<(std::ostream &os, const modint &self) {
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
    int x = rhs.v;
    assert(x > 0);
    if (internal::isprime(mod)) {
      static constexpr int lim = 1 << 21;
      static vector<modint> inv{0, 1};
      while (x >= lim) *this *= mod - mod / x, x = mod % x;
      while (x >= (int)inv.size()) {
        int m = (int)inv.size();
        inv.resize(m << 1);
        for (int i = m; i < m << 1; i++)
          inv[i] = (mod - mod / i) * inv[mod % i];
      }
      return *this *= inv[x];
    } else {
      auto ret = internal::exgcd(x, mod);
      assert(std::get<2>(ret) == 1);
      return *this *= std::get<0>(ret);
    }
  }
  friend modint qpow(modint a, LL b) {
    if (b < 0) b = -b, a = 1 / a;
    modint r = 1;
    for (; b; b >>= 1, a *= a)
      if (b & 1) r *= a;
    return r;
  }
  friend modint operator+(modint lhs, const modint &rhs) { return lhs += rhs; }
  friend modint operator-(modint lhs, const modint &rhs) { return lhs -= rhs; }
  friend modint operator*(modint lhs, const modint &rhs) { return lhs *= rhs; }
  friend modint operator/(modint lhs, const modint &rhs) { return lhs /= rhs; }
  friend bool operator==(const modint &lhs, const modint &rhs) {
    return lhs.v == rhs.v;
  }
  friend bool operator!=(const modint &lhs, const modint &rhs) {
    return lhs.v != rhs.v;
  }
  explicit operator bool() const { return v != 0; }
};
}  // namespace poly
