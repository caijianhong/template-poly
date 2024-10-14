#include "poly/modint.hpp"
#include "poly/getinv.hpp"
#include <iostream>
#include <cstdio>
using namespace poly;
using mint = modint<998244353>;
int main() {
  int n;
  scanf("%d", &n);
  vector<mint> f(n);
  for (int i = 0, x; i < n; i++) scanf("%d", &x), f[i] = x;
  f = getInv(f, n);
  for (int i = 0; i < n; i++) printf("%d%c", raw(f[i]), " \n"[i == n - 1]);
  return 0; 
}

