template <unsigned umod>
struct modint {/*{{{*/
  static constexpr int mod = umod;
  unsigned v;
  modint() = default;
  template <class T, enable_if_t<is_integral<T>::value, int> = 0>
    modint(const T& y) : v(y % mod + (is_signed<T>() && y < 0 ? mod : 0)) {}
  modint& operator+=(const modint& rhs) { v += rhs.v; if (v >= umod) v -= umod; return *this; }
  modint& operator-=(const modint& rhs) { v -= rhs.v; if (v >= umod) v += umod; return *this; }
  modint& operator*=(const modint& rhs) { v = (unsigned)(1ull * v * rhs.v % umod); return *this; }
  modint& operator/=(const modint& rhs) { assert(rhs.v); return *this *= qpow(rhs, mod - 2); }
  friend modint operator+(modint lhs, const modint& rhs) { return lhs += rhs; }
  friend modint operator-(modint lhs, const modint& rhs) { return lhs -= rhs; }
  friend modint operator*(modint lhs, const modint& rhs) { return lhs *= rhs; }
  friend modint operator/(modint lhs, const modint& rhs) { return lhs /= rhs; }
  template <class T> friend modint qpow(modint a, T b) {
    modint r = 1;
    for (assert(b >= 0); b; b >>= 1, a *= a) if (b & 1) r *= a;
    return r;
  }
  friend int raw(const modint& self) { return self.v; }
  friend ostream& operator<<(ostream& os, const modint& self) { return os << raw(self); }
  explicit operator bool() const { return v != 0; }
};/*}}}*/

