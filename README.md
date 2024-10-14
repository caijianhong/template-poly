# template-poly

OI 中的多项式模板，使用 `std::vector<modint<998244353>>` 实现。

## 已实现

- `modint`
- 多项式单点求值
- NTT（可选择是否使用 dit-dif 优化）
- 多项式加法、减法
- 多项式乘法
- 多项式乘法逆
- 多项式除法、取模
- 多项式对数函数
- 多项式指数函数
- 多项式快速幂
- 多项式开根
- 分式 $f(x)/g(x)$ 的第 $n$ 项
- 常系数齐次线性递推
- 求最短递推式的 BM 算法
- $O(n^2)$ 的拉格朗日插值

## 未实现

- 多项式复合、多点求值、快速插值（这些不知道有没有用）

## 使用方法

见 `docs/poly.md`。

将 `poly/` 文件夹放于代码同一目录，可以在代码中 `#include "poly/all"`获得所有功能，可以 `#include "poly/qpow.hpp"` 获得多项式快速幂，具体可以写的可以参见 `docs/tree.md`。

若在本地可以在编译选项中加入 `-I.` 以编译，或者可以使用 `test/expander.py` 将所有 `include` 展开，使用方法

```sh
$ ./expander.py main.cpp
```

将 `main.cpp` 展开到 `combined.cpp`，其它选项可以 `./expander.py --help` 查看。注意有一些选项可以在这个命令行里面改，见 `docs/tree.md`。
