int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  cin >> n;
  poly a(n);
  cin >> a;
  cout << getSqrt(a, n) << endl;
  return 0;
}
