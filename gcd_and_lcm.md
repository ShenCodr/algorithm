**沟槽的比赛仅支持C＋＋11，这玩意还要老子自己写**
### GCD(最大公约数)
*复杂度log(min(a,b))*
```cpp
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;//辗转相除法
}
```
### LCM(最小公倍数)
```cpp
int lcm(int a, int b) {
    return a / gcd(a, b) * b;  // 先除后乘防止溢出
}
```

