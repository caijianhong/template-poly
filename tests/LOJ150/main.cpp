#include "all"
using namespace std;
int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);
#endif
  using mint = modint<998244353>;
  using poly = vector<mint>;
  int n;
  string k;
  cin >> n >> k;
  poly a(n + 1);
  for (int i = 0; i <= n; i++) cin >> a[i].v;
  auto ret = getDev(qpow(getLn(a + poly{2 - a[0]} - getExp(getInt(getInv(getSqrt(a, n), n)), n + 1), n + 1) + poly{1}, k, n + 1));
  for (int i = 0; i < n; i++) cout << ret[i] << " \n"[i == n];
  return 0;
}

