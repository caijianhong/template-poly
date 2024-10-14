#include "poly/modint.hpp"
#include "poly/multiple.hpp"

using mint = modint<998244353>;
int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);
#endif
  int n, m;
  cin >> n >> m;
  vector<mint> a(n + 1), b(m + 1);
  for (int i = 0; i <= n; i++) cin >> a[i].v;
  for (int i = 0; i <= m; i++) cin >> b[i].v;
  auto c = a * b;
  for (int i = 0; i <= n + m; i++) cout << c[i] << " \n"[i == n + m];
  return 0;
}
