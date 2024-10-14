#include "poly/modint.hpp"
#include <cstdio>

using namespace std;
using namespace poly;

using mint = modint<11>;
int main() {
    mint a = 10;
    mint b(3);

    // equal
    assert(a == 21);
    assert(a == -1);
    assert(-1 == a);

    // negative
    assert(-b == 8);

    // plus
    assert(a + b == 2);  // (10 + 3) mod 11
    assert(1 + a == 0);

    // minus
    assert(a - b == 7);  // (10 - 3) mod 11
    assert(b - a == 4);

    // mul
    assert(a * b == 8);  // (10 * 3) mod 11

    // inv
    assert(1 / b == 4);  // (3 * 4) mod 11 == 1

    // div
    assert(a / b == 7);  // (10 * 4) mod 11

    // +=, -=, *=, /=
    a += b;
    assert(a == 2 && b == 3);
    a -= b;
    assert(a == 10 && b == 3);
    a *= b;
    assert(a == 8 && b == 3);
    a /= b;
    assert(a == 10 && b == 3);

    // pow
    assert(qpow(mint(2), 4) == 5);  // 16 mod 11

    // print value
    printf("%d\n", raw(a));  // 10

    // get mod
    assert(mint::mod == 11);
    assert(5 * (modint<12>{1} / 5) == 1);

    mt19937 rng{random_device{}()};
    for (int t = 1; t <= 100; t++) {
      using modi = modint<998244353>;
      int x = rng();
      assert((modi{1} / x) * modi{x} == 1);
    }
}

