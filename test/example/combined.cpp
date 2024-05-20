#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define endl "\n"
#define debug(...) void(0)
#endif
typedef long long LL;
template <class T>
using must_int = enable_if_t<is_integral<T>::value, int>;
template <unsigned umod>
struct modint {
  static constexpr int mod = umod;
  unsigned v;
  modint() : v(0) {}
  template <class T, must_int<T> = 0>
  modint(T _v) {
    int x = _v % (int)umod;
    v = x < 0 ? x + umod : x;
  }
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
  friend bool operator==(const modint &lhs, const modint &rhs) {
    return lhs.v == rhs.v;
  }
  friend bool operator!=(const modint &lhs, const modint &rhs) {
    return lhs.v != rhs.v;
  }
};
int glim(int x) { return x == 1 ? 1 : 1 << (32 - __builtin_clz(x - 1)); }
int bitctz(int x) { return __builtin_ctz(x); }
template <class mint>
mint getValue(const vector<mint>& a, const mint& x) {
  mint res = 0;
  for (int i = (int)a.size() - 1; i >= 0; i--) {
    res = res * x + a[i];
  }
  return res;
}
template <class mint>
vector<mint> cut(vector<mint> a, int lim) {
  a.resize(lim);
  return a;
}
template <class mint>
vector<mint> getDev(vector<mint> a) {
  a.erase(a.begin());
  for (int i = 1; i < (int)a.size(); i++) a[i] *= i + 1;
  return a;
}
template <class mint>
vector<mint> getInt(vector<mint> a) {
  a.insert(a.begin(), 0);
  for (int i = 1; i < (int)a.size(); i++) a[i] /= i;
  return a;
}
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
template <class mint, int g = 3>
vector<mint> concalc(int n, vector<vector<mint>> vec,
                     const function<mint(vector<mint>)> &func) {
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
template <class mint, int g = 3>
vector<mint> multiple(const vector<mint>& a, const vector<mint>& b) {
  int rlen = a.size() + b.size() - 1;
  auto func = [](vector<mint> vec) -> mint { return vec[0] * vec[1]; };
  auto ret = concalc<mint, g>(rlen, {a, b}, func);
  return cut(ret, rlen);
}
template <class mint, int g = 3>
vector<mint> getInv(const vector<mint>& a, int lim) {
  vector<mint> b{1 / a[0]};
  for (int len = 2; len <= glim(lim); len <<= 1) {
    vector<mint> c(a.begin(), a.begin() + min(len, (int)a.size()));
    auto func = [](vector<mint> vec) { return vec[0] * (2 - vec[0] * vec[1]); };
    b = cut(concalc<mint, g>(len << 1, {b, c}, func), len);
  }
  return cut(b, lim);
}
template <class mint, int g = 3>
vector<mint> getLn(const vector<mint>& a, int lim) {
  assert(a[0] == 1);
  return cut(getInt(multiple<mint, g>(getDev(a), getInv(a, lim))), lim);
}
template <class mint, int g = 3>
vector<mint> getExp(const vector<mint>& a, int lim) {
  assert(a[0] == 0);
  vector<mint> b{1};
  for (int len = 2; len <= glim(lim); len <<= 1) {
    vector<mint> c =
        vector<mint>(a.begin(), a.begin() + min(len, (int)a.size()));
    auto func = [](auto vec) { return vec[0] * (1 - vec[1] + vec[2]); };
    b = cut(concalc<mint, g>(len << 1, {b, getLn(b, len), c}, func), len);
  }
  return cut(b, lim);
}
template <class mint, int g = 3>
vector<mint> qpow_base(vector<mint> a, int km, int ke, int lim) {
  assert(a[0] != 0);
  mint coek = qpow(a[0], ke), icoe = 1 / a[0];
  for (int i = 0; i < (int)a.size(); i++) a[i] *= icoe;
  a = getLn<mint, g>(a, lim);
  for (int i = 0; i < lim; i++) a[i] *= km;
  a = getExp<mint, g>(a, lim);
  for (int i = 0; i < lim; i++) a[i] *= coek;
  return a;
}
template <class mint, int g = 3>
vector<mint> qpow(vector<mint> a, LL k, int lim) {
  int i =
      find_if(a.begin(), a.end(), [](mint x) { return x != 0; }) - a.begin();
  if (i == (int)a.size() || (i >= 1 && (k >= lim || i * k >= lim)))
    return vector<mint>(lim);
  if (i) a.erase(a.begin(), a.begin() + i);
  auto ret = qpow_base<mint, g>(a, k % mint::mod, k % (mint::mod - 1), lim);
  if (i) ret.insert(ret.begin(), i * k, 0);
  return ret;
}
template <class mint, int g = 3>
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
  auto ret = qpow_base<mint, g>(a, km, ke, lim);
  if (i) ret.insert(ret.begin(), i * stoll(k), 0);
  return ret;
}
#ifdef LOCAL
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define endl "\n"
#define debug(...) void(0)
#endif
typedef long long LL;
int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);
#endif
  auto&ss=cin;
    int n;
    string k;
    ss >> n >> k;
    using poly = vector<modint<998244353>>;
    poly a(n);
    for (int i = 0, x; i < n; i++) ss >> x, a[i] = x;
    auto ret = qpow(a, k, n);
    for (int i = 0, x; i < n; i++) cout << ret[i] << " ";
    cout << endl;
  return 0;
}

