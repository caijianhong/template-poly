#pragma once
#include "base.hpp"
namespace poly {
template <class mint>
vector<mint> BM(const vector<mint>& a) {
  vector<mint> ans, lst;
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
  ans.insert(ans.begin(), 0);
  return ans;
}
}  // namespace poly
