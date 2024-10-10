int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);
#endif
  int n;
  string str;
  stringstream ss;
  cin >> n;
  cin >> str;
  poly a(n);
  for (auto& x : a) cin >> x;
  for (auto x : qpow(a, str, n)) cout << x << " ";
  cout << endl;
  return 0;
}
