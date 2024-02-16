int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);
#endif  
  int n, k;
  cin >> n >> k;
  vector<pair<mint, mint>> a(n);
  for (auto& elem : a) cin >> elem.first >> elem.second;
  cout << lagrange(a)(k) << endl;
  cerr << lagrange(a) << endl;
  return 0;
}

