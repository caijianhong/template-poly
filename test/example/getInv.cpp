#include <bits/stdc++.h>
#include "modint.hpp"
#include "getinv.hpp"
using namespace std;
#ifdef LOCAL
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define endl "\n"
#define debug(...) void(0)
#endif
typedef long long LL;
typedef modint<998244353> mint;
int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);  
#endif
  assert(getInv<mint>({1, 6, 3, 4, 9}, 5) == vector<mint>({1, 998244347, 33, 998244169, 1020}));
  return 0;
}
