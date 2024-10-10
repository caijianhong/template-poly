# 【模板】多项式初等函数

同时作为 <https://github.com/caijianhong/template-poly> 的 document。

## 杂项

数域为 $\mathbb F_{998244353}$，以下假装定义了 `mint` 为 `modint<998244353>`，并 `typedef vector<mint> poly`（代码中没有这两个定义）。

代码中 `mint` 是模板参数，可以同时在模板参数里面塞入原根（计划去掉），如 multiple 的完整定义是：

```cpp
template <class mint, int g = 3>
vector<mint> multiple(const vector<mint>& a, const vector<mint>& b);
```

这使得可以 `multiple<998244353, 3>(a, b)` 传入真实的原根，主要用于应对未知模数，所有涉及 ntt 的操作都有这个模板参数。

- `poly cut(poly vec, int lim);` 效果等同于截断到 $lim$ 项或补零至 $lim$ 项后返回自己（就是 `vector<mint>::resize()`）
- `poly concalc(int n, vector<poly> vec, const function<mint(vector<mint>)>& func);` 这个接口主要用于实现牛顿迭代，$n$ 是答案最大项数，$vec$ 是若干多项式，$func$ 是一个计算的回调函数，如计算多项式乘法是这样的：
  - `concalc(len, {a, b}, [](vector<mint> vec) { return vec[0] * vec[1]; });`
  - 即计算 $a\cdot b$。$a, b$ 都是多项式。
  - 最终返回一个长为 `glim(n)` 的多项式。
  - 使用 ntt 实现。


## 多项式单点求值

### 问题

给出有限项的多项式 $F(x)$ 和 $x_0$，求 $F(x_0)$。

```cpp
mint getValue()(const poly& vec, const mint& x);
```

### solution

秦九韶算法。即从最高项开始，每次做形如 $ans = ans\times x+a_i$ 的工作。$O(n)$。

## 多项式加法、减法、数乘

### 问题

给出有限项的多项式 $F(x),G(x)$ 和 $\lambda$，求 $H(x)=F(x)\pm G(x)$ 或 $H(x)=\lambda F(x)$。

```cpp
poly operator+(poly a, const poly& b);
poly operator-(poly a, const poly& b);
```

有对应的 `operator+=`，`operator-=`。

### solution

对应位相加、相减。$O(n)$。

## 多项式乘法

### 问题

给出多项式 $F(x), G(x)$，求 $H(x)=F(x)G(x)$。

```cpp
poly multiple(const poly& a, const poly& b);
```

### solution

<https://www.cnblogs.com/caijianhong/p/template-fft.html>。$O(n\log n)$。

### code

便于记背。

```cpp
// ntt0.hpp
typedef modint<998244353> mint;
int glim(const int& x) { return 1 << (32 - __builtin_clz(x - 1)); }
int bitctz(const int& x) { return __builtin_ctz(x); }
void poly::ntt(int op) {
  static bool wns_flag = false;
  static vector<mint> wns;
  if (!wns_flag) {
    wns_flag = true;
    for (int j = 1; j <= 23; j++) {
      wns.push_back(qpow(mint(3), raw(mint(-1)) >> j));
    }
  }
  vector<mint>& a = *this;
  int n = a.size();
  for (int i = 1, r = 0; i < n; i++) {
    r ^= n - (1 << (bitctz(n) - bitctz(i) - 1));
    if (i < r) std::swap(a[i], a[r]);
  }
  vector<mint> w(n);
  for (int k = 1, len = 2; len <= n; k <<= 1, len <<= 1) {
    mint wn = wns[bitctz(k)];
    for (int i = raw(w[0] = 1); i < k; i++) w[i] = w[i - 1] * wn;
    for (int i = 0; i < n; i += len) {
      for (int j = 0; j < k; j++) {
        mint x = a[i + j], y = a[i + j + k] * w[j];
        a[i + j] = x + y, a[i + j + k] = x - y;
      }
    }
  }
  if (op == -1) {
    mint iz = mint(1) / n;
    for (int i = 0; i < n; i++) a[i] *= iz;
    reverse(a.begin() + 1, a.end());
  }
}
```

### dit-dif 优化

[再探 FFT - DIT 与 DIF，另种推导和优化 – Charles Wu的博客](https://charleswu.site/archives/3065)。

## 多项式乘法逆

### 问题

给出 $F(x)$，求 $H(x)\bmod x^{lim}$ 满足 $H(x)F(x)\equiv 1\pmod{x^{lim}}$。

注意，此处 $H(x)$ 是无限项的多项式，我们只需要 $H(x)\bmod x^{lim}$。另外需要保证 $F(0)\neq 0$，否则逆元在  $\mathbb F_{998244353}$ 上不存在（如果是其他的域，要求 $F(0)$ 存在逆元）。

```cpp
poly getInv(const poly& a, int lim);
```

### Newton's Method

给出 $G(H(x))$，我们需要找到 $H(x)$ 使得 $G(H(x))=0$。

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

注意这个 $G'$ 是一个导数，我们最好指明它导的是 $H_*(x)$ 而不是 $x$。这意味着与 $H_*(x)$ 无关的项应视作常数。

$$
H(x)\equiv H_*(x)-\dfrac{G(H_*(x))}{\dfrac{\mathrm d}{\mathrm dH_*(x)}G(H_*(x))}\pmod {x^n}
$$

### solution

需要找到 $H(x)$，使得 $G(H(x))=\dfrac{1}{H(x)}-F(x)=0$。（注意这个构造）

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

 - $Q(x)$ 次数为 $n-m$，$R(x)$ 次数小于 $m$（钦定，$R(x)$ 的次数恰好为 $m-1$）。
 - $F(x) = Q(x) * G(x) + R(x)$。

```cpp
pair<poly, poly> divide(poly a, poly b); // {Q(x), R(x)}
```

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

## 多项式形式导数与不定积分

### 问题

给出 $F(x)$，求 $H(x)$ 满足 $H(x)=\dfrac{\mathrm{d}}{\mathrm dx}F(x)$（形式导数）或者 $H(x)=\displaystyle \int F(x)\mathrm dx$（形式不定积分）。

这里默认形式不定积分的常数项为 $0$，尽管应该是任意常数。

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

给出 $F(x)$，求 $H(x)\bmod x^{lim}$ 满足 $H(x)\equiv \ln F(x)\pmod{x^{lim}}$。

注意，此处 $H(x)$ 是无限项的多项式，我们只需要 $H(x)\bmod x^{lim}$。另外需要保证 $F(0)=1$，否则在  $\mathbb F_{998244353}$ 上不存在。

```cpp
poly getLn(const poly& a, int lim);
```

### 级数表示

给出 $\ln$ 的麦克劳林级数：
$$
\ln(1+x)=\sum_{i=1}^{+\infty}\dfrac{(-1)^{i+1}}{i}x^i
$$

$$
\ln(1-x)=-\sum_{i=1}^{+\infty}\frac{x^i}{i}
$$

要点：$\ln(1+x)$ 的关于 $x$ 的导数是复合函数求导，是 $\frac{1}{1+x}$，二阶导也是复合函数，是 $\frac{-1}{(1+x)^2}$。

$$
\ln(x)=\sum_{i=1}^{+\infty}\dfrac{(-1)^{i+1}}{i}(x-1)^i
$$

### 链式法则

复合函数求导的链式法则：$(F(G(x)))'=F'(G(x))G'(x)$。具体来说是

$$
\dfrac{\mathrm d}{\mathrm dx}F(G(x))=\dfrac{\mathrm d}{\mathrm dG(x)}F(G(x))\cdot \dfrac{\mathrm d}{\mathrm dx}G(x)
$$

### solution

对 $\ln F(x)$ 求导再积分得到
$$
\dfrac{\mathrm d}{\mathrm dx}\ln F(x)=\dfrac{\dfrac{\mathrm d}{\mathrm dx}F(x)}{F(x)}\implies \ln F(x)=\int\mathrm d\ln F(x)=\int \dfrac{\dfrac{\mathrm d}{\mathrm dx}F(x)}{F(x)}\mathrm dx
$$

即 
$$
\ln F(x)=\int \frac{F'(x)}{F(x)}\mathrm dx
$$
~~注意不要把 dx 约掉~~。

## 多项式对数函数（exp）

### 问题

给出 $F(x)$，求 $H(x)\bmod x^{lim}$ 满足 $H(x)\equiv \exp F(x)\pmod{x^{lim}}$。

注意，此处 $H(x)$ 是无限项的多项式，我们只需要 $H(x)\bmod x^{lim}$。另外需要保证 $F(0)=0$，否则在 $\mathbb F_{998244353}$ 上不存在。

```cpp
poly getExp(const poly& a, int lim);
```

### 级数表示

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

需要通过微调使得 $F(0)=1$，首先将 $F(x)$ 除 $x$ 直到有常数项，然后所有系数除掉 $F(0)$。最后再搞回去。这里注意的是取模问题，有两个定理帮助我们：

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

---

（以下内容还未实现）

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

$n$ 个点 $(x_i,y_i)$ 可以唯一地确定一个 $n-1$ 次多项式 $f(x)$。现在，给定这 $n$ 个点，请你确定这个多项式。

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

正确性比较显然。具体实现时先暴力求出 $\prod_i(x-x_i)$，然后每次 $O(n)$ 的除掉一个二项式。$O(n^2)$。

## Berlekamp–Massey 算法（最短线性递推式）

### 问题

给出一个数列 $P$ 从 $0$ 开始的前 $n$ 项 $\{P_0, P_1, P_2, \cdots, P_{n-1}\}$。求序列 $P$ 在 $\bmod~998244353$ 下的最短线性递推式。注意需要保证最短线性递推式长度 $\leq n/2$（意思是：如果这个序列不是线性递推的，会返回长度为 $n/2$ 的假的递推式）。

```cpp
poly BM(poly a);
```

### solution

将 $P$ 下标从 $1$ 开始，递推式下标从 $0$ 开始。记 $P[1...i]$ 的最短线性递推式为 $R_i$，特别地有 $R_0=\{\}$。已知 $R[0...(i-1)]$，怎么求 $R_i$？

首先计算一个 $\Delta(R_{i-1}, i)=del_{i}=\sum_{j=0}R_{i-1, j}a_{i-j-1}-a_i$。如果 $\Delta(R_{i-1}, i)=0$ 那么说明 $R_i=R_{i-1}$，结束。否则就失配了。第一种情况是 $R_{i-1}=\{\}$，只需要使得 $R_i$ 为 $i$ 个 $0$，即强制使得前面这 $i$ 个数是初始给定不用管的。

第二种情况，我们实际上是要考虑找出一个 $R'=\{R'_0, R'_1, \cdots,R'_{k-1}\}$ 使得对于 $k<p<i$ 都有 $\sum_{j=0}^{k-1}R'_{j}a_{p-j-1}=0$ 而且唯独有 $\sum_{j=0}^{k-1}R'_{j}a_{i-j-1}=-del_i$，然后 $R_i=R_{i-1}+R'$ 就好了，这里加法是对应位相加。这个事情就很严重。解决方法是任选一个 $w$，然后回忆起 $R_w$ 和当时的 $del_{w+1}=delta$，构造 $R'=\{0, 0, \cdots, 0, del_i/delta, -del_i/delta\times R_w\}$，后面这个 $\times R_w$ 是这个序列去数乘上前面的数再接上前面的序列，然后有 $i-w-2$ 个零在前面。然后我们验证一下它合法。

设 $k=i-w-1+|R_w|$。对于 $k<p<i$：

$$
\Delta(R', p)+a_p=\sum_{j=0}^{k-1}R'_{ j}a_{p-j-1}=\dfrac{del_i}{delta}(a_{p-i + w + 1}-\sum_{j=0}R_wa_{p-j-i+w})=-\dfrac{del_i}{delta}\Delta(R_w, p-i+w+1).
$$

因为 $p<i$，所以 $p-i+w+1\leq w$，根据定义，$\Delta(R_w, p-i+w+1)=0$。满足条件。

对于 $p=i$。
$$
\Delta(R', i)+a_i=\sum_{j=0}^{k-1}R'_{ j}a_{i-j-1}=-\dfrac{del_i}{del_w}\Delta(R_w, w+1).
$$
因为这里 $\Delta(R_w, w+1)=del_{w+1}=delta$，所以这玩意等于 $-del_i$，全对。

为了使得 $R_i$ 最短，选使 $R'$ 最短的 $w$ 即可。

### code

具体代码有 0 下标细节等，可以在这里看一下。注意最终返回递推式下标从 $1$ 开始。

```cpp
poly BM(poly a) {
  poly ans, lst;
  int w = 0;
  mint delta = 0;
  for (int i = 0; i < a.size(); i++) {
    mint tmp = -a[i];
    for (int j = 0; j < ans.size(); j++) tmp += ans[j] * a[i - j - 1];
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
      if (now.size() <= lst.size() + i - w) { // 注意此时无符号数溢出，注意移项
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

给出多项式 $F(x), G(x)$ 和 $n$，求 $[x^n]F(x)/G(x)$。

```cpp
template <class T>
mint divide_at(poly f, poly g, T n);
```

### solution

$$
[x^n]\frac{F(x)}{G(x)}=[x^n]\frac{F(x)G(-x)}{G(x)G(-x)}.
$$

因为 $G(x)G(-x)$ 是一个偶函数（函数 $H(x)$ 为偶函数当且仅当 $H(x)=H(-x)$，如绝对值函数，如 $H(x)=x^2$ 等只有偶次项有值的多项式函数），所以它只有偶次项，不妨直接记作 $v(x^2)=G(x)G(-x)$。为了适应之，我们将 $F(x)G(-x)$ 按照奇偶次项分裂，分为 $c_0(x^2)+xc_1(x^2)$，$c_0(x^2)$ 是只拿偶次项，$xc_1(x)$ 是只拿奇次项，这样，$c_0(x)$ 就是很连续的东西，$c_1(x)$ 也是。
$$
=[x^n]\frac{c_0(x^2)+xc_1(x^2)}{v(x^2)}=[x^n]\frac{c_0(x^2)}{v(x^2)}+[x^{n-1}]\frac{c_1(x^2)}{v(x^2)}=\begin{cases}
[x^{n/2}]\dfrac{c_0(x)}{v(x)}, 2\mid n,\\
[x^{(n-1)/2}]\dfrac{c_1(x)}{v(x)}, 2\not \mid n.
\end{cases}
$$
于是 $n$ 的规模减少一半，这样只需要 $O(\log n)$ 次操作就能到达 $n=0$ 的情况，答案为 $F(0)/G(0)$。同时每次减少问题规模，多项式 $F(x), G(x)$ 的长度都不变。这样时间复杂度为 $O(m\log m\log n)$ 其中 $m$ 是 $\max(\deg F(x), \deg G(x))$。

## 常系数齐次线性递推  

### 问题

求一个满足 $k$ 阶齐次线性递推数列 ${a_i}$ 的第 $n$ 项，即：

$$
a_n=\sum\limits_{i=1}^{k}f_i \times a_{n-i}
$$

给出的是 $a_0,a_1,\cdots,a_{k-1}$ 和 $f_1, f_2, \cdots, f_k$ 注意下标。

```cpp
template <class T>
mint linear_rec(poly a, poly f, T n);
```

### solution

我们只需要构造 $F(x), G(x)$ 使得 $[x^n]\dfrac{F(x)}{G(x)}=a_n$ 即可。以下记 $F_i=[x^i]F(x)$。

为了使得 $F(x)$ 的项数足够小，考虑钦定 $F_i=0$ 当 $i\geq k$ 时。那么根据定义：
$$
F(x)=G(x)a(x)\implies 0=\sum_{j=0}^i G_ja_{i-j}\implies G_0a_i=\sum_{j=1}^i-G_ja_{i-j}
$$
使得 $G_0=1, G_i=-f_i(1\leq i\leq k)$，其他项都是零。

又因为 $F(x)=G(x)a(x)\bmod {x^k}$，于是暴力计算 $F(x)$。

然后应用 Bostan-Mori 算法即可。即我们想要算的是以下东西：
$$
[x^n]\dfrac{a(1-f)\bmod x^{k}}{1-f}.
$$
注意 $f$ 下标从 $1$ 开始。
