# template-poly
The repository is still a **work in progress**.

OI 中的多项式模板，使用 `std::vector<modint<998244353>>` 实现。目前已实现：
- modint
- 单点求值
- NTT
- 多项式加法、减法、数乘
- 多项式乘法
- 多项式乘法逆
- 分式 $f(x)/g(x)$ 的第 $n$ 项
- 常系数齐次线性递推
- 求最短递推式的 BM 算法
- $O(n^2)$ 的拉格朗日插值

目前未实现：
- 多项式除法、取模
- 多项式对数函数
- 多项式指数函数
- 多项式牛顿迭代需要一个通用的接口，没想好怎么写。
- ~~文档~~

```sh
g++ poly.cpp -o main -std=c++14
```
