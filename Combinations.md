# 求组合数
**时间复杂度`O(n)`**
```cpp
const int MOD = 1e9 + 7; // 模个大质数喵～
const int MAX = 1e6 + 5; // n 的最大值根据需要调喵～

ll fac[MAX], invFac[MAX];

// 快速幂：计算 base^exp % MOD
ll fastPow(ll base, ll exp) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

// 预处理阶乘和逆元
void init() {
    fac[0] = invFac[0] = 1;
    for (int i = 1; i < MAX; ++i)
        fac[i] = fac[i - 1] * i % MOD;
    invFac[MAX - 1] = fastPow(fac[MAX - 1], MOD - 2); // 费马小定理
    for (int i = MAX - 2; i >= 1; --i)
        invFac[i] = invFac[i + 1] * (i + 1) % MOD;
}

// 计算组合数 C(n, k)
ll C(ll n, ll k) {
    if (k < 0 || k > n) return 0;
    return fac[n] * invFac[k] % MOD * invFac[n - k] % MOD;
}
```
