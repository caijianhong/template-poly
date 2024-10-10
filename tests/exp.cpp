int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);
#endif
  int n;
  cin >> n;
  poly a(n);
  for (auto& x : a) cin >> x;
  for (auto x : getExp(a, n)) cout << x << " ";
  cout << endl;
  return 0;
}
