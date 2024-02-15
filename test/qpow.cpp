int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);
#endif
  int n;
  string str;
  stringstream ss;
  cin >> n;
  cin >> str;
  ss << str << " " << str;
  mint k;
  modint<mint::mod - 1> k0;
  ss >> k >> k0;
  poly a(n);
  for (auto& x : a) cin >> x;
  for (auto x : qpow(a, k, k0, n)) cout << x << " ";
  cout << endl;
  return 0;
}
