#include "poly/modint.hpp"
#include "poly/getexp.hpp"
#include <iostream>
using namespace std;
using namespace poly;
using mint = modint<998244353>;
int main() {
  int n;
  cin >> n;
  vector<mint> f(n);
  for (int i = 0; i < n; i++) cin >> f[i].v;
  auto ret = getExp(f, n);
  for (int i = 0; i < n; i++) cout << ret[i] << " \n"[i == n - 1];
  return 0;
}
