#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define endl "\n"
#define debug(...) void(0)
#endif
typedef long long LL;
template <unsigned umod>
struct modint {
  static constexpr int mod = umod;
  unsigned v;
  modint() : v(0) {}
  template <class T, enable_if_t<is_integral<T>::value>* = nullptr>
  modint(T x) {
    x %= mod;
    if (x < 0) x += mod;
    v = x;
  }
  modint(const string& str) {
    v = 0;
    size_t i = 0;
    if (str.front() == '-') i += 1;
    while (i < str.size()) {
      assert(isdigit(str[i]));
      v = (v * 10ull % umod + str[i] - '0') % umod;
      i += 1;
    }
    if (str.front() == '-' && v) v = umod - v;
  }
  modint operator+() const { return *this; }
  modint operator-() const { return modint() - *this; }
  friend int raw(const modint& self) { return self.v; }
  friend istream& operator>>(istream& is, modint& self) {
    string str;
    is >> str;
    self = str;
    return is;
  }
  friend ostream& operator<<(ostream& os, const modint& self) {
    return os << raw(self);
  }
  modint& operator+=(const modint& rhs) {
    v += rhs.v;
    if (v >= umod) v -= umod;
    return *this;
  }
  modint& operator-=(const modint& rhs) {
    v -= rhs.v;
    if (v >= umod) v += umod;
    return *this;
  }
  modint& operator*=(const modint& rhs) {
    v = static_cast<unsigned>(1ull * v * rhs.v % umod);
    return *this;
  }
  modint& operator/=(const modint& rhs) {
    static constexpr size_t ilim = 1 << 20;
    static modint inv[ilim + 10];
    static int sz = 0;
    assert(rhs.v);
    if (rhs.v > ilim) return *this *= qpow(rhs, mod - 2);
    if (!sz) inv[1] = sz = 1;
    while (sz < (int)rhs.v) {
      for (int i = sz + 1; i <= sz << 1; i++) inv[i] = -mod / i * inv[mod % i];
      sz <<= 1;
    }
    return *this *= inv[rhs.v];
  }
  template <class T>
  friend modint qpow(modint a, T b) {
    modint r = 1;
    for (; b; b >>= 1, a *= a)
      if (b & 1) r *= a;
    return r;
  }
  friend modint operator+(modint lhs, const modint& rhs) { return lhs += rhs; }
  friend modint operator-(modint lhs, const modint& rhs) { return lhs -= rhs; }
  friend modint operator*(modint lhs, const modint& rhs) { return lhs *= rhs; }
  friend modint operator/(modint lhs, const modint& rhs) { return lhs /= rhs; }
  friend bool operator==(const modint& lhs, const modint& rhs) {
    return lhs.v == rhs.v;
  }
  friend bool operator!=(const modint& lhs, const modint& rhs) {
    return lhs.v != rhs.v;
  }
};
typedef modint<998244353> mint;
int glim(const int& x) { return 1 << (32 - __builtin_clz(x - 1)); }
int bitctz(const int& x) { return __builtin_ctz(x); }
struct poly : vector<mint> {
  poly() {}
  explicit poly(int n) : vector<mint>(n) {}
  poly(const vector<mint>& vec) : vector<mint>(vec) {}
  poly(initializer_list<mint> il) : vector<mint>(il) {}
  mint operator()(const mint& x) const;
  poly& cut(int lim);
  void ntt(int op);
};
void print(const poly& a) {
  for (size_t i = 0; i < a.size(); i++) debug("%d, ", raw(a[i]));
  debug("\n");
}
istream& operator>>(istream& is, poly& a) {
  for (auto& x : a) is >> x;
  return is;
}
ostream& operator<<(ostream& os, const poly& a) {
  bool flag = false;
  for (auto& x : a) {
    if (flag)
      os << " ";
    else
      flag = true;
    os << x;
  }
  return os;
}
mint poly::operator()(const mint& x) const {
  const auto& a = *this;
  mint res = 0;
  for (int i = (int)a.size() - 1; i >= 0; i--) {
    res = res * x + a[i];
  }
  return res;
}
poly& poly::cut(int lim) {
  resize(lim);
  return *this;
}
void poly::ntt(int op) {
  static bool wns_flag = false;
  static vector<mint> wns;
  if (!wns_flag) {
    wns_flag = true;
    for (int j = 1; j <= 23; j++) {
      wns.push_back(qpow(mint(3), raw(mint(-1)) >> j));
    }
  }
  vector<mint>& a = *this;
  int n = a.size();
  for (int i = 1, r = 0; i < n; i++) {
    r ^= n - (1 << (bitctz(n) - bitctz(i) - 1));
    if (i < r) std::swap(a[i], a[r]);
  }
  vector<mint> w(n);
  for (int k = 1, len = 2; len <= n; k <<= 1, len <<= 1) {
    mint wn = wns[bitctz(k)];
    for (int i = raw(w[0] = 1); i < k; i++) w[i] = w[i - 1] * wn;
    for (int i = 0; i < n; i += len) {
      for (int j = 0; j < k; j++) {
        mint x = a[i + j], y = a[i + j + k] * w[j];
        a[i + j] = x + y, a[i + j + k] = x - y;
      }
    }
  }
  if (op == -1) {
    mint iz = mint(1) / n;
    for (int i = 0; i < n; i++) a[i] *= iz;
    reverse(a.begin() + 1, a.end());
  }
}
poly concalc(int n, vector<poly> vec,
             const function<mint(vector<mint>)>& func) {
  int lim = glim(n);
  int m = vec.size();
  for (auto& f : vec) f.resize(lim), f.ntt(1);
  vector<mint> tmp(m);
  poly ret(lim);
  for (int i = 0; i < lim; i++) {
    for (int j = 0; j < m; j++) tmp[j] = vec[j][i];
    ret[i] = func(tmp);
  }
  ret.ntt(-1);
  return ret;
}
poly getInv(const poly& a, int lim) {
  poly b{1 / a[0]};
  for (int len = 2; len <= glim(lim); len <<= 1) {
    poly c = vector<mint>(a.begin(), a.begin() + min(len, (int)a.size()));
    b = concalc(len << 1, {b, c}, [](vector<mint> vec) {
          return vec[0] * (2 - vec[0] * vec[1]);
        }).cut(len);
  }
  return b.cut(lim);
}
poly operator+=(poly& a, const poly& b) {
  if (a.size() < b.size()) a.resize(b.size());
  for (size_t i = 0; i < b.size(); i++) a[i] += b[i];
  return a;
}
poly operator-=(poly& a, const poly& b) {
  if (a.size() < b.size()) a.resize(b.size());
  for (size_t i = 0; i < b.size(); i++) a[i] -= b[i];
  return a;
}
poly operator*=(poly& a, const mint& k) {
  if (k == 1) return a;
  for (size_t i = 0; i < a.size(); i++) a[i] *= k;
  return a;
}
poly operator/=(poly& a, const mint& k) { return a *= 1 / k; }
poly operator<<=(poly& a, const int& k) {
  // mnltiple by x^k
  a.insert(a.begin(), k, 0);
  return a;
}
poly operator>>=(poly& a, const int& k) {
  // divide by x^k
  a.erase(a.begin(), a.begin() + min(k, (int)a.size()));
  return a;
}
poly operator*(const poly& a, const poly& b) {
  if (a.empty() || b.empty()) return {};
  int rlen = a.size() + b.size() - 1;
  int len = glim(rlen);
  if (1ull * a.size() * b.size() <= 1ull * len * bitctz(len)) {
    poly ret(rlen);
    for (size_t i = 0; i < a.size(); i++)
      for (size_t j = 0; j < b.size(); j++) ret[i + j] += a[i] * b[j];
    return ret;
  } else {
    return concalc(len, {a, b},
                   [](vector<mint> vec) { return vec[0] * vec[1]; })
        .cut(rlen);
  }
}
poly operator/(poly a, poly b) {
  if (a.size() < b.size()) return {};
  int rlen = a.size() - b.size() + 1;
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  a = (a * getInv(b, rlen)).cut(rlen);
  reverse(a.begin(), a.end());
  return a;
}
poly operator-(poly a, const poly& b) { return a -= b; }
poly operator%(const poly& a, const poly& b) {
  return (a - (a / b) * b).cut(b.size() - 1);
}
poly operator*=(poly& a, const poly& b) { return a = a * b; }
poly operator/=(poly& a, const poly& b) { return a = a / b; }
poly operator%=(poly& a, const poly& b) { return a = a % b; }
poly operator+(poly a, const poly& b) { return a += b; }
poly operator*(poly a, const mint& k) { return a *= k; }
poly operator*(const mint& k, poly a) { return a *= k; }
poly operator/(poly a, const mint& k) { return a /= k; }
poly operator<<(poly a, const int& k) { return a <<= k; }
poly operator>>(poly a, const int& k) { return a >>= k; }
poly getDev(poly a) {
  a >>= 1;
  for (size_t i = 1; i < a.size(); i++) a[i] *= i + 1;
  return a;
}
poly getInt(poly a) {
  a <<= 1;
  for (size_t i = 1; i < a.size(); i++) a[i] /= i;
  return a;
}
poly getLn(const poly& a, int lim) {
  assert(a[0] == 1);
  return getInt(getDev(a) * getInv(a, lim)).cut(lim);
}
poly getExp(const poly& a, int lim) {
  assert(a[0] == 0);
  poly b{1};
  for (int len = 2; len <= glim(lim); len <<= 1) {
    poly c = vector<mint>(a.begin(), a.begin() + min(len, (int)a.size()));
    b = concalc(len << 1, {b, getLn(b, len), c}, [](vector<mint> vec) {
          return vec[0] * (1 - vec[1] + vec[2]);
        }).cut(len);
  }
  return b.cut(lim);
}
poly qpow(const poly& a, string k, int lim) {
  size_t i = 0;
  while (i < a.size() && a[i] == 0) i += 1;
  if (i == a.size() || (i > 0 && k.size() >= 9) ||
      1ull * i * raw(mint(k)) >= 1ull * lim)
    return poly(lim);
  lim -= i * raw(mint(k));
  return getExp(getLn(a / a[i] >> i, lim) * k, lim) *
             qpow(a[i], raw(modint<mint::mod - 1>(k)))
         << i * raw(mint(k));
}
poly qpow(const poly& a, LL k, int lim) {
  size_t i = 0;
  while (i < a.size() && a[i] == 0) i += 1;
  if (i == a.size() || (i > 0 && k >= 1e9) ||
      1ull * i * k >= 1ull * lim)
    return poly(lim);
  lim -= i * k;
  return getExp(getLn(a / a[i] >> i, lim) * k, lim) *
             qpow(a[i], raw(modint<mint::mod - 1>(k)))
         << i * k;
}
mint sqrt(const mint& c) {
  static const auto check = [](mint c) {
    return qpow(c, (mint::mod - 1) >> 1) == 1;
  };
  if (raw(c) <= 1) return 1;
  if (!check(c)) throw "No solution!";
  static mt19937 rng{random_device{}()};
  mint a = rng();
  while (check(a * a - c)) a = rng();
  typedef pair<mint, mint> number;
  const auto mul = [=](number x, number y) {
    return make_pair(x.first * y.first + x.second * y.second * (a * a - c),
                     x.first * y.second + x.second * y.first);
  };
  const auto qpow = [=](number a, int b) {
    number r = {1, 0};
    for (; b; b >>= 1, a = mul(a, a))
      if (b & 1) r = mul(r, a);
    return r;
  };
  mint ret = qpow({a, 1}, (mint::mod + 1) >> 1).first;
  return min(raw(ret), raw(-ret));
}
poly getSqrt(const poly& a, int lim) {
  poly b{sqrt(a[0])};
  for (int len = 2; len <= glim(lim); len <<= 1) {
    poly c = vector<mint>(a.begin(), a.begin() + min(len, (int)a.size()));
    b = (c * getInv(b * 2, len) + b / 2).cut(len);
  }
  return b.cut(lim);
}
template <class T>
mint divide_at(poly f, poly g, T n) {
  for (; n; n >>= 1) {
    poly r = g;
    for (size_t i = 1; i < r.size(); i += 2) r[i] *= -1;
    f *= r;
    g *= r;
    for (size_t i = n & 1; i < f.size(); i += 2) f[i >> 1] = f[i];
    f.resize((f.size() + 1) >> 1);
    for (size_t i = 0; i < g.size(); i += 2) g[i >> 1] = g[i];
    g.resize((g.size() + 1) >> 1);
  }
  return f.empty() ? 0 : f[0] / g[0];
}
template <class T>
mint linear_rec(poly a, poly f, T n) {
  // a[n] = sum_i f[i] * a[n - i]
  a.resize(f.size() - 1);
  f = poly{1} - f;
  poly g = a * f;
  g.resize(a.size());
  return divide_at(g, f, n);
}
poly BM(poly a) {
  poly ans, lst;
  int w = 0;
  mint delta = 0;
  for (size_t i = 0; i < a.size(); i++) {
    mint tmp = -a[i];
    for (size_t j = 0; j < ans.size(); j++) tmp += ans[j] * a[i - j - 1];
    if (tmp == 0) continue;
    if (ans.empty()) {
      w = i;
      delta = tmp;
      ans = vector<mint>(i + 1, 0);
    } else {
      auto now = ans;
      mint mul = -tmp / delta;
      if (ans.size() < lst.size() + i - w) ans.resize(lst.size() + i - w);
      ans[i - w - 1] -= mul;
      for (size_t j = 0; j < lst.size(); j++) ans[i - w + j] += lst[j] * mul;
      if (now.size() <= lst.size() + i - w) {
        w = i;
        lst = now;
        delta = tmp;
      }
    }
  }
  return ans << 1;
}
poly lagrange(const vector<pair<mint, mint>>& a) {
  poly ans(a.size()), product{1};
  for (size_t i = 0; i < a.size(); i++) {
    product *= poly{-a[i].first, 1};
  }
  auto divide2 = [&](poly a, mint b) {
    poly res(a.size() - 1);
    for (size_t i = (int)a.size() - 1; i >= 1; i--) {
      res[i - 1] = a[i];
      a[i - 1] -= a[i] * b;
    }
    return res;
  };
  for (size_t i = 0; i < a.size(); i++) {
    mint denos = 1;
    for (size_t j = 0; j < a.size(); j++) {
      if (i != j) denos *= a[i].first - a[j].first;
    }
    poly numes = divide2(product, -a[i].first);
    ans += a[i].second / denos * numes;
  }
  return ans;
}
