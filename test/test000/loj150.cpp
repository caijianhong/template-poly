int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);
#endif
  int n;
  string k;
  cin >> n >> k;
  poly a(n + 1);
  cin >> a;
  cout << getDev(qpow(getLn(a + poly{2 - a[0]} -
                                getExp(getInt(getInv(getSqrt(a, n), n)), n + 1),
                            n + 1) +
                          poly{1},
                      k, n + 1))
       << endl;
}
