#pragma once
#include "poly/base.hpp"
namespace poly {
namespace internal {
constexpr bool isprime(int n) {
  if (n <= 2) return n == 2;
  for (int i = 2; i <= n / i; i++)
    if (n % i == 0) return false;
  return true;
}
// @param b >= 0
constexpr LL qpow(LL a, LL b, int mod) {
  LL r = 1;
  for (; b; b >>= 1, a = a * a % mod) {
    if (b & 1) r = r * a % mod;
  }
  return r;
}
// @param p must be prime
constexpr int pmtroot(int p) {
  int dvs[20]{}, cnt = 0, n = p - 1;
  for (int i = 2; i <= n / i; i++) {
    if (n % i) continue;
    dvs[cnt++] = i;
    while (n % i == 0) n /= i;
  }
  if (n > 1) dvs[cnt++] = n;
  for (int g = 1; g < p; g++) {
    bool flag = true;
    for (int i = 0; i < cnt && flag; i++)
      flag &= qpow(g, (p - 1) / dvs[i], p) != 1;
    if (flag) return g;
  }
  return -1;
}
template <class T>
constexpr std::tuple<T, T, T> exgcd(T a, T b) {
  T x1 = 1, y1 = 0, x2 = 0, y2 = 1;
  while (b) {
    auto c = a / b;
    std::swap(a, b), b -= c * a;
    std::swap(x1, x2), x2 -= c * x1;
    std::swap(y1, y2), y2 -= c * y1;
  }
  return std::make_tuple(x1, y1, a);
}
}  // namespace internal
}  // namespace poly
