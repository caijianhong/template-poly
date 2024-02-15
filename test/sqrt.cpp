int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  cin >> n;
  poly a(n);
  for (auto&x:a) cin >> x;
  for (auto&x:getSqrt(a, n)) cout << x << " ";
  cout << endl;
  return 0;
}
