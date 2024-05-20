# 文件目录

函数名具体用途看 docs/poly.md。

- header.h 是所有文件的头文件。
- modint.hpp 是 modint，实现相近于 ac-library。
- base.hpp
  - getValue
  - cut
- ntt.hpp 下分两个版本
  - ntt0.hpp 是纯真写法
  - ntt1.hpp 使用 dit-dif 优化，建议以编译器命令行参数 `-DNTT 1` 或 expander.py 参数 `--ntt 1` 启用
  - 没有指定任何版本时，启用 ntt1.hpp
- arithmetic.hpp
  - plusminus.hpp
    - operator+
    - operator-
  - multiple.hpp
    - multiple
  - getinv.hpp 注意是小写
    - getInv 注意是大写
  - divide.hpp
    - divide
  - getdevint
    - getDev
    - getInt
  - getln
    - getLn
  - getexp
    - getExp
  - qpow.hpp
    - qpow

all 包括以上全部内容。