#include <bits/stdc++.h>
#include "poly/internal_math.hpp"
#include "atcoder/internal_math.hpp"
using namespace std;
using namespace poly;
#ifdef LOCAL
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define endl "\n"
#define debug(...) void(0)
#endif
using LL = long long;
int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);
#endif
  using namespace poly::internal;
  cout << isprime(10) << endl;
  cout << isprime(11) << endl;
  cout << qpow(9, 2, 10) << endl;
  cout << isprime(998244353) << endl;
  for (int p : {2, 167772161, 469762049, 754974721, 998244353}) 
    assert(pmtroot(p) == atcoder::internal::primitive_root_constexpr(p));
  return 0;
}

