int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  poly f(n + 1), g(m + 1);
  for (int i = 0; i <= n; i++) scanf("%u", &f[i].v);
  for (int i = 0; i <= m; i++) scanf("%u", &g[i].v);
  auto q = f / g;
  for (int i = 0; i < q.size(); i++)
    printf("%d%c", raw(q[i]), " \n"[i == n - m]);
  auto r = f % g;
  for (int i = 0; i < r.size(); i++)
    printf("%d%c", raw(r[i]), " \n"[i == m - 1]);
  return 0;
}
