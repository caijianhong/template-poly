#include <bits/stdc++.h>
#include "../../poly/all"
using namespace std;
#ifdef LOCAL
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define endl "\n"
#define debug(...) void(0)
#endif
typedef long long LL;
using mint = modint<998244353>;
int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);  
#endif
  vector<mint> a{1, 1, 4, 5, 1, 4}, b{1, 9, 1, 9, 8, 1, 0};
  assert(getValue(a, mint(0)) == 1);
  assert(getValue(a, mint(1)) == 16);
  assert(getValue(a, mint(-1)) == -4);
  assert(a + b == vector<mint>({2, 10, 5, 14, 9, 5, 0}));
  assert(a - b == vector<mint>({0, -8, 3, -4, -7, 3, 0}));
  assert(vector<mint>{1} + a == vector<mint>({2, 1, 4, 5, 1, 4}));
  assert(a + vector<mint>{1} == vector<mint>({2, 1, 4, 5, 1, 4}));
  assert(a - vector<mint>{1} == vector<mint>({0, 1, 4, 5, 1, 4}));
  vector<mint> c{1, 1};
  assert(multiple(c, c) == vector<mint>({1, 2, 1}));
  assert(multiple<mint>({1, 2}, {1, 2, 1}) == vector<mint>({1, 4, 5, 2}));
  return 0;
}

