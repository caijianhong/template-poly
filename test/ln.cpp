
void TestGetLn() {
  int n;
  cin >> n;
  poly a(n);
  for (auto& x : a) cin >> x;
  for (auto x : getLn(a, n)) cout << x << " ";
  cout << endl;
}
int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);
#endif
  TestGetLn();
  return 0;
}
