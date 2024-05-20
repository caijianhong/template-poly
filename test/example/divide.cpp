#include <bits/stdc++.h>
#include "modint.hpp"
#include "divide.hpp"
using namespace std;
#ifdef LOCAL
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define endl "\n"
#define debug(...) void(0)
#endif
typedef long long LL;
typedef vector<modint<998244353>> poly;
int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);  
#endif
  poly a{1, 9, 2, 6, 0, 8};
  poly b{1, 7};
  poly c{237340659, 335104102, 649004347, 448191342, 855638018};
  poly d{760903695};
  auto [e, f] = divide(a, b);
  for (int i = 0; i < e.size(); i++) cout << e[i] << " \n"[i + 1 == e.size()];
  for (int i = 0; i < f.size(); i++) cout << f[i] << " \n"[i + 1 == f.size()];
  assert(divide(a, b) == make_pair(c, d));
  return 0;
}
