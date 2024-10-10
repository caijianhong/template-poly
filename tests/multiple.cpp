int main() {
  int n, m;
  cin >> n >> m;
  poly a(n + 1), b(m + 1);
  for (auto& x : a) cin >> x;
  for (auto& x : b) cin >> x;
  for (auto x : a* b) cout << x << " ";
  cout << endl;
  return 0;
}
