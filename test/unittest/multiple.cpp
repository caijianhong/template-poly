#include "poly/modint.hpp"
#include "poly/multiple.hpp"
#include <gtest/gtest.h>
#include <vector>

using mint = modint<998244353>;
int mian(int id) {
  ifstream inf{"data/multiple/" + to_string(id) + ".in"};
  ifstream ans{"data/multiple/" + to_string(id) + ".out"};
  int n, m;
  inf >> n >> m;
  vector<mint> a(n + 1), b(m + 1);
  for (int i = 0; i <= n; i++) inf >> a[i].v;
  for (int i = 0; i <= m; i++) inf >> b[i].v;
  auto c = a * b;
  for (int i = 0, x; i <= n + m; i++) {
    ans >> x;
    assert(x == raw(c[i]));
    EXPECT_EQ(x, raw(c[i]));
  }
  return 0;
}

TEST(multiple, data1) { mian(1); }
TEST(multiple, data2) { mian(2); }
TEST(multiple, data3) { mian(3); }
TEST(multiple, data4) { mian(4); }
TEST(multiple, data5) { mian(5); }
TEST(multiple, data6) { mian(6); }
TEST(multiple, data7) { mian(7); }
TEST(multiple, data8) { mian(8); }
TEST(multiple, data9) { mian(9); }
TEST(multiple, data10) { mian(10); }
TEST(multiple, data11) { mian(11); }
TEST(multiple, data12) { mian(12); }
TEST(multiple, data13) { mian(13); }
TEST(multiple, data14) { mian(14); }
TEST(multiple, data15) { mian(15); }
TEST(multiple, data16) { mian(16); }
TEST(multiple, data17) { mian(17); }
TEST(multiple, data18) { mian(18); }
TEST(multiple, data19) { mian(19); }
TEST(multiple, data20) { mian(20); }
