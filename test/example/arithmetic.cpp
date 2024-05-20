#include "header.h"
#include "modint.hpp"
#include "base.hpp"
#include "arithmetic.hpp"
using mint = modint<998244353>;
int main() {
  vector<mint> a{1, 1, 4, 5, 1, 4}, b{1, 9, 1, 9, 8, 1, 0};
  assert(getValue(a, mint(0)) == 1);
  assert(getValue(a, mint(1)) == 16);
  assert(getValue(a, mint(-1)) == -4);
  assert(a + b == vector<mint>({2, 10, 5, 14, 9, 5, 0}));
  assert(a - b == vector<mint>({0, -8, 3, -4, -7, 3, 0}));
  assert(vector<mint>{1} + a == vector<mint>({2, 1, 4, 5, 1, 4}));
  assert(a + vector<mint>{1} == vector<mint>({2, 1, 4, 5, 1, 4}));
  assert(a - vector<mint>{1} == vector<mint>({0, 1, 4, 5, 1, 4}));
  vector<mint> c{1, 1};
  assert(multiple(c, c) == vector<mint>({1, 2, 1}));
  assert(multiple<mint>({1, 2}, {1, 2, 1}) == vector<mint>({1, 4, 5, 2}));
  return 0;
}

