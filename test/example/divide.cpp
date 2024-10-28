#include <bits/stdc++.h>
#include "poly/divide.hpp"
#include "poly/modint.hpp"
using namespace std;
#ifdef LOCAL
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define endl "\n"
#define debug(...) void(0)
#endif
using LL = long long;
int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);
#endif
  int n, m;
    scanf("%d%d", &n, &m);
    vector<poly::modint<998244353>> f(n + 1), g(m + 1);
    for (int i = 0; i <= n; i++) scanf("%u", &f[i].v);
    for (int i = 0; i <= m; i++) scanf("%u", &g[i].v);
    auto q = f / g;
    for (int i = 0; i < q.size(); i++) printf("%d%c", raw(q[i]), " \n"[i == n - m]);
    auto  r = cut(f-q*g,g.size() - 1);
    for (int i = 0; i < r.size(); i++) printf("%d%c", raw(r[i]), " \n"[i == m - 1]);
  return 0;
}

