# 快速幂
**时间复杂度（logn）**


### 核心思想

**1. 取模运算性质**

利用取模的分配律
每一步乘法后立即取模，避免溢出。

**2. 分治思想与指数分解**

将指数 \( b \) 分解为二进制形式，通过平方底数、折半指数的方式减少计算次数。
- **偶数**：底数平方，指数折半。  
- **奇数**：分离一个底数后转为偶数处理。  


**3. 位运算优化**

- **奇偶判断**：用 `b & 1` 代替 `b % 2`，更快判断指数是否为奇数。  
- **指数折半**：用 `b >>= 1` 代替 `b /= 2`，减少运算时间。  


### 代码实现
```cpp
typedef long long ll;
ll fastPow(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod; // 初始取模，防止a过大
    while (b) {
        if (b & 1) res = (res * a) % mod; // 当前二进制位为1时累乘
        a = (a * a) % mod; // 底数平方
        b >>= 1; // 指数右移一位
    }
    return res;
}
```
