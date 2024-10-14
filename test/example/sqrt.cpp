#include <bits/stdc++.h>
#include "poly/modint.hpp"
#include "poly/getsqrt.hpp"
using namespace std;
using mint = modint<998244353>;
using poly = vector<mint>;
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  cin >> n;
  poly a(n);
  for (int i = 0; i < n; i++) cin >> a[i].v;
  auto ret = getSqrt(a, n);
  for (int i = 0; i < n; i++) cout << ret[i] << " \n"[i == n - 1];
  return 0;
}
