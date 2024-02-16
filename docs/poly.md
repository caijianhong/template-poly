# 【模板】多项式初等函数

同时作为 <https://github.com/caijianhong/template-poly> 的 document。

## 杂项

数域为 $\mathbb F_{998244353}$，所以定义了 `mint` 为 `modint<998244353>`。

`poly` 是多项式的类型，从 `std::vector<mint>` 继承而来。`poly` 的构造函数如下：

```cpp
poly();
explicit poly(int n); // n 为项数，n 个 0
poly(const vector<mint>& vec); // vec[0] 为常数项，vec[1] 为一次项，以此类推
poly(initializer_list<mint> il);
```

以及 

- `poly& poly::cut(int lim);` 效果等同于截断到 $lim$ 项或补零至 $lim$ 项后返回自己。

- `istream& operator>>(istream& is, poly& a);` 和 `ostream& operator<<(ostream& os, const poly& a);` 如其名。

- `poly operator<<(poly a, const int& k);` 和`poly operator>>(poly a, const int& k);` 分别是乘 $x^k$ 和除 $x^k$（$<k$ 次项舍弃）。有对应的 `operator<<=` 和 `operator>>=`。

- `void poly::ntt(int op)`; 是 NTT，$op=1$ 是 DFT，$op=-1$ 是 IDFT。

- `poly concalc(int n, vector<poly> vec, const function<mint(vector<mint>)>& func);` 这个接口主要用于实现牛顿迭代，$n$ 是最高次数，$vec$ 是若干多项式，$func$ 是一个计算的回调函数，如计算多项式乘法是这样的：

  - `concalc(len, {a, b}, [](vector<mint> vec) { return vec[0] * vec[1]; });`
  - 即计算 $a\cdot b$。$a, b$ 都是多项式。


## 多项式单点求值

### 问题

给出有限项的多项式 $F(x)$ 和 $x_0$，求 $F(x_0)$。

```cpp
mint poly::operator()(const mint& x) const;
```

### solution

秦九韶算法。$O(n)$。

## 多项式加法、减法、数乘

### 问题

给出有限项的多项式 $F(x),G(x)$ 和 $\lambda$，求 $H(x)=F(x)\pm G(x)$ 或 $H(x)=\lambda F(x)$。

```cpp
poly operator+(poly a, const poly& b);
poly operator-(poly a, const poly& b);
poly operator*(poly a, const mint& k);
poly operator*(const mint& k, poly a);
poly operator/(poly a, const mint& k);
```

有对应的 `operator+=`，`operator-=`，`operator*=` 和 `operator/=`。

### solution

对应位相加、相减、数乘。$O(n)$。

## 多项式乘法

### 问题

给出多项式 $F(x), G(x)$，求 $H(x)=F(x)G(x)$。

```cpp
poly operator*(const poly& a, const poly& b);
```

有对应的 `operator*=`

### solution

<https://www.cnblogs.com/caijianhong/p/template-fft.html>。$O(n\log n)$。

## 多项式乘法逆

### 问题

给出 $F(x)$，求 $H(x)\bmod x^{lim}$ 满足 $H(x)F(x)\equiv 1\pmod{x^{lim}}$。注意，此处 $H(x)$ 是无限项的多项式，我们只需要 $H(x)\bmod x^{lim}$。

```cpp
poly getInv(const poly& a, int lim);
```

### Newton's Method

给出 $F(x), G(H(x))$，我们需要找到 $H(x)$ 使得 $G(H(x))=0$。

设 $n$ 为偶数，已经知道了 $H_*(x)=H(x)\bmod{x^{n/2}}$ 满足 $G(H_*(x))\equiv 0\pmod{x^{n/2}}$（$H(0)$ 需要特殊计算）。想知道 $H(x)\bmod x^{n}$。

在 $H(x)=H_*(x)$ 处对 $G(H(x))$ 作泰勒展开。

$$
G(H(x))=\sum_{i=0}^{+\infty}\dfrac{G^{(i)}(H_*(x))}{i!}(H(x)-H_*(x))^i=0
$$
上式，若两边 $\bmod x^{n}$，因为 $H(x)-H_*(x)$ 的前 $n/2$ 项系数全零，所以 $(H(x)-H_*(x))^i$ 在 $i\geq 2$ 时是零。

$$
G(H(x))\equiv \sum_{i=0}^{+\infty}\dfrac{G^{(i)}(H_*(x))}{i!}(H(x)-H_*(x))^i\equiv 0\pmod{x^n}
$$

$$
G(H(x))\equiv G(H_*(x))+G'(H_*(x))(H(x)-H_*(x))\equiv 0\pmod{x^n}
$$

所以

$$
G(H_*(x))+G'(H_*(x))H(x)\equiv G'(H_*(x))H_*(x)\pmod{x^n}
$$

$$
H(x)\equiv H_*(x)-\dfrac{G(H_*(x))}{G'(H_*(x))}\pmod {x^n}
$$

注意这个 $G'$ 是一个导数，我们最好指明它导的是 $H(x)$ 而不是 $x$。这意味着与 $H(x)$ 无关的项应视作常数。

$$
H(x)\equiv H_*(x)-\dfrac{G(H_*(x))}{\dfrac{\mathrm d}{\mathrm dH(x)}G(H_*(x))}\pmod {x^n}
$$

### solution

需要找到 $H(x)$，使得 $G(H(x))=\dfrac{1}{H(x)}-F(x)=0$。

$$
H(x)\equiv H_*(x)-\dfrac{\dfrac{1}{H_*(x)}-F(x)}{-\dfrac{1}{H_*^2(x)}}\pmod {x^n}
$$

这里 $F(x)$ 与 $H(x)$ 无关，是常数，求导时消失了。

$$
H(x)\equiv 2H_*(x)-H_*^2(x)F(x)\pmod {x^n}
$$

时间复杂度 $T(n)=T(n/2)+O(n\log n)=O(n\log n)$。

## 多项式除法与取模（整除）

### 问题

给定一个 $n$ 次多项式 $F(x)$ 和一个 $m$ 次多项式  $G(x)$ ，请求出多项式 $Q(x)$, $R(x)$，满足以下条件：

 - $Q(x)$ 次数为 $n-m$，$R(x)$ 次数小于 $m$（钦定，$R(x)$ 的次数恰好为 $m-1$）
 - $F(x) = Q(x) * G(x) + R(x)$

```cpp
poly operator/(poly a, poly b);
poly operator%(const poly& a, const poly& b);
```

有对应的 `operator/=` 和 `operator%=`。

### solution

若 $R(x)=0$，则直接使用多项式求逆解决。不妨，定义

$$
F^R(x)=x^nF\left(\dfrac{1}{x}\right)
$$

注意，$n$ 是 $F(x)$ 最高次项的次数。发现这样 $x^0$ 项系数成为 $x^n$ 项系数，$x^n$ 项系数成为 $x^0$ 项系数，系数的顺序翻转了。而且有 $(F^R)^R(x)=F(x)$。

$$
F(1/x) = Q(1/x) * G(1/x) + R(1/x)
$$

$$
x^nF(1/x) = x^{n-m}Q(1/x) * x^{m}G(1/x) + x^{n-m+1}x^{m-1}R(1/x)
$$

$$
F^R(x)=Q^R(x)G^R(x)+x^{n-m+1}R^R(x)
$$

$$
F^R(x)\equiv Q^R(x)G^R(x)+x^{n-m+1}R^R(x)\pmod{x^{n-m+1}}
$$

$$
F^R(x)\equiv Q^R(x)G^R(x)\pmod{x^{n-m+1}}
$$

消除了 $R(x)$ 的影响，一次求逆和一次乘法可以求出 $Q(x)$。然后有 $R(x)=F(x)-Q(x)G(x)$。

$O(n\log n)$。

## 多项式形式导数、形式不定积分

### 问题

给出 $F(x)$，求 $H(x)$ 满足 $H(x)=\dfrac{\mathrm{d}}{\mathrm dx}F(x)$ 或者 $H(x)=\displaystyle \int F(x)\mathrm dx$。这里默认形式不定积分的常数项为 $0$，尽管应该是任意常数。

```cpp
poly getDev(poly a); // 形式导数
poly getInt(poly a); // 形式不定积分
```

### solution

$$
\dfrac{\mathrm{d}}{\mathrm dx}x^k=kx^{k-1}\implies \int x^k\mathrm dx=\dfrac{1}{k+1}x^{k+1}
$$

求导和不定积分都有线性性，每项分开计算。$O(n)$。

## 多项式对数函数（ln）

### 问题

给出 $F(x)$，求 $H(x)\bmod x^{lim}$ 满足 $H(x)\equiv \ln F(x)\pmod{x^{lim}}$。注意，此处 $H(x)$ 是无限项的多项式，我们只需要 $H(x)\bmod x^{lim}$。另外需要保证 $F(0)=1$ 否则在这个域上不存在。

```cpp
poly getLn(const poly& a, int lim);
```

给出 $\ln$ 的麦克劳林级数：

$$
\ln(1+x)=\sum_{i=0}^{+\infty}\dfrac{(-1)^{i+1}}{i}x^i
$$

$$
\ln(1-x)=-\sum_{i=0}^{+\infty}\frac{x^i}{i}
$$

要点：$\ln(1+x)$ 的关于 $x$ 的导数是复合函数求导，是 $\frac{1}{1+x}$，二阶导也是复合函数，是 $\frac{-1}{(1+x)^2}$。

### solution

复合函数求导的链式法则：$(F(G(x)))'=F'(G(x))G'(x)$ 具体来说是

$$
\dfrac{\mathrm d}{\mathrm dx}F(G(x))=\dfrac{\mathrm d}{\mathrm dG(x)}F(G(x))\cdot \dfrac{\mathrm d}{\mathrm dx}G(x)
$$

对 $\ln F(x)$ 求导再积分得到

$$
\dfrac{\mathrm d}{\mathrm dx}\ln F(x)=\dfrac{\dfrac{\mathrm d}{\mathrm dx}F(x)}{F(x)}\implies \ln F(x)=\int\mathrm d\ln F(x)=\int \dfrac{\dfrac{\mathrm d}{\mathrm dx}F(x)}{F(x)}\mathrm dx
$$

即 $\ln F(x)=\int F'(x)/F(x)\mathrm dx$。~~注意不要把 dx 约掉~~。

## 多项式对数函数（exp）

### 问题

给出 $F(x)$，求 $H(x)\bmod x^{lim}$ 满足 $H(x)\equiv \exp F(x)\pmod{x^{lim}}$。注意，此处 $H(x)$ 是无限项的多项式，我们只需要 $H(x)\bmod x^{lim}$。另外需要保证 $F(0)=0$ 否则在这个域上不存在。

```cpp
poly getExp(const poly& a, int lim);
```

给出 $\exp$ 的麦克劳林级数：

$$
\exp x=\sum_{i=0}^{+\infty}\frac{x^i}{i!}
$$

### solution

需要找到 $H(x)$，使得 $G(H(x))=\ln H(x)-F(x)=0$。应用 Newton's Method。

$$
H(x)\equiv H_*(x)-\dfrac{\ln H_*(x)-F(x)}{\dfrac{1}{H_*(x)}}\pmod {x^n}
$$

$$
H(x)\equiv H_*(x)(1-\ln H_*(x)+F(x))\pmod {x^n}
$$

时间复杂度 $T(n)=T(n/2)+O(n\log n)=O(n\log n)$。

## 多项式快速幂

### 问题

给出 $F(x)$ 和 $k$，求 $H(x)\bmod x^{lim}$ 满足 $H(x)\equiv F^k(x)\pmod{x^{lim}}$。注意，此处 $H(x)$ 是有限项但真的很多项的多项式，我们只需要 $H(x)\bmod x^{lim}$。

```cpp
poly qpow(const poly& a, string k, int lim); // k 是高精度数
poly qpow(const poly& a, LL k, int lim);
```

### solution

$$
H(x)=F^k(x)=\exp(\ln F^k(x))=\exp(k\ln F(x))
$$

需要通过微调使得 $F(0)=1$，首先将 $F(x)$ 除 $x$ 直到有常数项，然后所有系数除掉 $F(0)$。最后再搞回去。这里注意的是取模问题，有两个定理：

### 定理一

$p$ 是质数。来源：[这里第一篇题解](https://www.luogu.com.cn/problem/solution/P5245)、[这个链接暂时无法访问](https://www.luogu.com.cn/blog/_post/304253)

$$
F^p(x)\equiv F(x^p)\pmod p
$$

证明略。反正可以得出，因为 $n<p$，所以 $F^p(x)\equiv F(x^p)\equiv F(0)\equiv 1\pmod {x^{n}}$（在 $\mathbb F_p$ 上）。

所以在对 $\ln F(x)$ 点乘 $k$ 时，$k$ 可以对 $p$ 取模，这里的 $p=998244353$。

### 定理二

$p$ 是质数，$a\not\equiv0\pmod p$，费马小定理：

$$
a^{p-1}\equiv 1\pmod p
$$

所以将常数项乘回去时，$k$ 要对 $p-1$ 取模，即最终的多项式要乘 $F^{k\bmod (p-1)}(0)$ 再乘上 $x$ 的若干次方。

## 多项式开根

### 问题

给出 $F(x)$，求 $H(x)\bmod x^{lim}$ 满足 $H^2(x)\equiv  F(x)\pmod{x^{lim}}$。注意，此处 $H(x)$ 是无限项的多项式，我们只需要 $H(x)\bmod x^{lim}$。另外需要保证 $F(0)$ 在这个域上有二次剩余。

```cpp
mint sqrt(const mint& c); // 一个数求二次剩余，无解抛出异常
poly getSqrt(const poly& a, int lim);
```

### solution

需要找到 $H(x)$，使得 $G(H(x))= H^2(x)-F(x)=0$。应用 Newton's Method。

$$
H(x)\equiv H_*(x)-\dfrac{ H_*^2(x)-F(x)}{ 2H_*(x)}\pmod {x^n}
$$

$$
H(x)\equiv \dfrac{ H_*(x)}{ 2}+\dfrac{F(x)}{2H_*(x)}\pmod {x^n}
$$

时间复杂度 $T(n)=T(n/2)+O(n\log n)=O(n\log n)$。

## 拉格朗日插值

### 问题

$n$ 个点 $(x_i,y_i)$ 可以唯一地确定一个多项式 $y = f(x)$。现在，给定这 $n$ 个点，请你确定这个多项式。

```cpp
poly lagrange(const vector<pair<mint, mint>>& a);
```

### solution

定义 

$$
\ell_j(x)=\prod_{i\neq j}\frac{x-x_i}{x_j-x_i}
$$

则 

$$
f(x)=\sum_i\ell_i(x)y_i
$$

正确性比较显然。先暴力求出 $\prod_i(x-x_i)$，然后每次将他 $O(n)$ 的除掉一个二项式。$O(n^2)$。

## Berlekamp–Massey 算法（最短线性递推式）

### 问题

给出一个数列 $P$ 从 $0$ 开始的前 $n$ 项。求序列 $P$ 在 $\bmod~998244353$ 下的最短线性递推式。注意需要保证最短线性递推式长度 $\leq n/2$。

```cpp
poly BM(poly a);
```

### code

(solution is WIP, replace it with the code)

```cpp
poly BM(poly a) {
  poly ans, lst;
  int w = 0;
  mint delta = 0;
  for (size_t i = 0; i < a.size(); i++) {
    mint tmp = -a[i];
    for (size_t j = 0; j < ans.size(); j++) tmp += ans[j] * a[i - j - 1];
    if (tmp == 0) continue;
    if (ans.empty()) {
      w = i;
      delta = tmp;
      ans = vector<mint>(i + 1, 0);
    } else {
      auto now = ans;
      mint mul = -tmp / delta;
      if (ans.size() < lst.size() + i - w) ans.resize(lst.size() + i - w);
      ans[i - w - 1] -= mul;
      for (size_t j = 0; j < lst.size(); j++) ans[i - w + j] += lst[j] * mul;
      if (now.size() <= lst.size() + i - w) {
        w = i;
        lst = now;
        delta = tmp;
      }
    }
  }
  return ans << 1;
}
```

## Bostan-Mori 算法（求分式第 $n$ 项）

### 问题

给出多项式 $F(x), G(x)$ 和 $k$，求 $[x^k]F(x)/G(x)$。

```cpp
mint divide_at(poly f, poly g, T n);
```

### code

link: <https://www.cnblogs.com/Potassium/p/15130342.html>

(solution is WIP, replace it with the code)

```cpp
template <class T>
mint divide_at(poly f, poly g, T n) {
  for (; n; n >>= 1) {
    poly r = g;
    for (size_t i = 1; i < r.size(); i += 2) r[i] *= -1;
    f *= r;
    g *= r;
    for (size_t i = n & 1; i < f.size(); i += 2) f[i >> 1] = f[i];
    f.resize((f.size() + 1) >> 1);
    for (size_t i = 0; i < g.size(); i += 2) g[i >> 1] = g[i];
    g.resize((g.size() + 1) >> 1);
  }
  return f.empty() ? 0 : f[0] / g[0];
}
```

## 常系数齐次线性递推  

### 问题

求一个满足 $k$ 阶齐次线性递推数列 ${a_i}$ 的第 $n$ 项，即：

$$
a_n=\sum\limits_{i=1}^{k}f_i \times a_{n-i}
$$
给出的是 $a_0,a_1,\cdots,a_{k-1}$ 和 $f_1, f_2, \cdots, f_k$ 注意下标。

### code

link: <https://www.cnblogs.com/Potassium/p/15130342.html>

(solution is WIP, replace it with the code)

```cpp
template <class T>
mint linear_rec(poly a, poly f, T n) {
  // a[n] = sum_i f[i] * a[n - i]
  a.resize(f.size() - 1);
  f = poly{1} - f;
  poly g = a * f;
  g.resize(a.size());
  return divide_at(g, f, n);
}
```

