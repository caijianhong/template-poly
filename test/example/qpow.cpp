#include <bits/stdc++.h>
#include "modint.hpp"
#include "qpow.hpp"
using namespace std;
#ifdef LOCAL
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define endl "\n"
#define debug(...) void(0)
#endif
typedef long long LL;
string testcases[] = {
R"(9 18948465
1 2 3 4 5 6 7 8 9
1 37896930 597086012 720637306 161940419 360472177 560327751 446560856 524295016)",
R"(4 1
1 1 0 0
1 1 0 0)",
R"(4 2
0 1 0 0
0 0 1 0)",
R"(4 2
1 1 0 0
1 2 1 0)",
R"(4 3
1 1 0 0
1 3 3 1)"
};
int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);  
#endif
  for (auto test : testcases) {
    stringstream ss{test};
    int n;
    string k;
    ss >> n >> k;
    using poly = vector<modint<998244353>>;
    poly a(n);
    for (int i = 0, x; i < n; i++) ss >> x, a[i] = x;
    auto ret = qpow(a, k, n);
    for (int i = 0, x; i < n; i++) ss >> x, assert(x == ret[i]);
  }
  return 0;
}
