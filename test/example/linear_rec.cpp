#include "poly/modint.hpp"
#include "poly/linear_rec.hpp"
#include <vector>
#include <iostream>
using namespace std;
int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);
#endif
  int n, k;
  cin >> n >> k;
  vector<poly::modint<998244353>> f(k + 1), a(k);
  for (int i = 1, x; i <= k; i++) cin >> x, f[i] = x;
  for (int i = 0, x; i < k; i++) cin >> x, a[i] = x;
  auto ret = linear_rec(a, f, n);
  cout << ret << endl;
  return 0;

}
