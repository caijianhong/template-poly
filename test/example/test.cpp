#include "poly/ntt.hpp"
#include "poly/modint.hpp"
#include <iostream>
using namespace std;
using mint = poly::modint<998244353>;
int main() {
  vector<mint> a{1, 2, 3};
  auto ret = dit(dif(a, 4));
  for (int i = 0; i < 4; i++) cout << ret[i] << " ";
  cout << endl;
}
