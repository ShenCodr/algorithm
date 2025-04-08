# 埃氏筛
**古老但是简单的筛法(所以不太推荐)**

**核心思想：**
从 2 开始，我们认为所有的数初始时都可能是素数。然后，找到第一个未被标记的数 p（它肯定是素数），然后将所有 p 的倍数（2p, 3p, 4p, ...）标记为合数（非素数）。重复这个过程，直到检查完所有小于等于 sqrt(N) 的数（其中 N 是我们要筛选的上限）。

**算法步骤：**

创建一个布尔数组 `is_prime[N+1]`，初始化所有元素为 `true`（假设所有数都是素数）。

将 `is_prime[0]` 和 `is_prime[1]` 标记为 `false`（`0` 和 `1` 不是素数）。

从 `p = 2` 开始遍历到 `sqrt(N)`：

如果 `is_prime[p]` 为 `true`（说明 `p` 是素数）：

将 `p` 的所有倍数 `2p`, `3p`, `4p`, ... 直到 `N` 标记为 `false`（`is_prime[j] = false`，其中 `j = 2*p, 3*p, ... <= N`）。

优化: 实际上，我们可以从 `p*p` 开始标记，因为 `2p, 3p, ..., (p-1)p` 这些数在之前处理更小的素数（如 `2`, `3`, ...）时已经被标记过了。

遍历结束后，数组 `is_prime` 中所有值为 `true` 的下标 i 就是 N 以内的素数。

### 代码
```cpp
// 埃氏筛函数，找出 0 到 n 之间的所有素数
// 返回一个 vector<int> 包含所有素数
vector<int> sieve_of_eratosthenes(int n) {
    if (n < 2) {
        return {}; // 没有素数小于 2
    }
    // is_prime[i] 表示数字 i 是否是素数
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false; // 0 和 1 不是素数

    // 遍历到 sqrt(n) 即可
    for (int p = 2; p * p <= n; ++p) {
        // 如果 p 是素数
        if (is_prime[p]) {
            // 将 p 的倍数（从 p*p 开始）标记为合数
            // j += p 比 j = k * p (k=p, p+1, ...) 更高效
            for (int j = p * p; j <= n; j += p) {
                is_prime[j] = false;
            }
        }
    }
    // 收集所有素数
    vector<int> primes;
    for (int p = 2; p <= n; ++p) {
        if (is_prime[p]) {
            primes.push_back(p);
        }
    }
    return primes;
}

```

**时间复杂度 `O(N log log N)`**

# 欧拉筛
**埃氏筛的改进(推荐)**

**核心思想：**

在遍历数字 i（从 2到 N）时，我们不仅判断 i 是否为素数，还会利用已经找到的素数列表 `primes` 来筛掉合数。

关键在于，对于每个数 i，我们用`primes` 列表中的素数 p 去筛掉 i * p。

为了保证每个合数只被其最小素因子筛掉，我们增加一个判断：如果 i 是 p 的倍数`（i % p == 0）`，那么就停止用 p 以及 `primes` 中更大的素数去筛 i 的倍数。

**算法步骤：**
创建一个布尔数组 `is_prime[N+1]`，初始化为 `true`。

创建一个整数向量 `primes` 用于存储找到的素数。

将 `is_prime[0]` 和 `is_prime[1]` 设为 `false`。

从 `i = 2` 遍历到 `N`：

如果 `is_prime[i]` 为 `true`，说明 `i` 是素数，将其加入 `primes` 列表。

遍历 `primes` 列表中已找到的素数 `p（设为 primes[j]）`：

计算合数 `num = i * primes[j]`。

如果 `num > N`，则停止内层循环（因为后续的 `primes[j+1]` 乘以 `i` 会更大）。

将 `is_prime[num]` 标记为 `false`（因为 `num` 是合数，且 `primes[j]` 是它的一个素因子）。

关键步骤: 如果 `i % primes[j] == 0`，则 `break` 内层循环。这保证了 `num` 只被其最小素因子 `primes[j]` 筛掉。

遍历结束后，`primes` 列表包含了 N 以内所有的素数。

### 代码
```cpp
// 欧拉筛（线性筛）函数，找出 0 到 n 之间的所有素数
// 返回一个 vector<int> 包含所有素数
vector<int> euler_sieve(int n) {
    if (n < 2) {
        return {};
    }
    vector<bool> is_prime(n + 1, true);
    vector<int> primes; // 存储找到的素数
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; ++i) {
        // 如果 i 是素数，添加到素数列表
        if (is_prime[i]) {
            primes.push_back(i);
        }
        // 遍历已找到的素数列表 primes 来筛掉合数
        // j < primes.size() 保证不越界
        // i * primes[j] <= n 保证筛掉的合数不超过范围 n
        for (int j = 0; j < primes.size() && i * primes[j] <= n; ++j) {
            // 将 i * primes[j] 标记为合数
            // primes[j] 是 i * primes[j] 的一个素因子
            is_prime[i * primes[j]] = false;
            if (i % primes[j] == 0) {
                break;
            }
        }
    }
    return primes;
}
```

**时间复杂度： `O(N)`**



# 求区间内的素数
**方法一：**
筛到 n，然后筛选范围

如果 n 不是特别大（例如，n 能在内存中创建一个大小为 n+1 的数组，通常 n 在 10^7 或 10^8 级别以下可以接受），这是最简单的方法。

使用埃氏筛或欧拉筛，找出 0 到 n 之间的所有素数。

遍历从 m 到 n 的所有整数 i。

如果 i 在筛法结果中被标记为素数（并且 i >= m），则输出或收集 i

**方法二：**
__区间筛 (Segmented Sieve)__

**原理**

先用埃氏筛生成  `[2, sqrt(n)]`  的素数列表。
用这些素数筛选  `[m, n]`  区间内的合数，避免处理整个  `[2, n]`  范围。

```cpp
vector<int> segmentedSieve(int m, int n) {
    vector<int> primes;
    int limit = sqrt(n);
    //这里需要提前实现埃氏筛，欧拉筛也可以
    vector<bool> base_sieve = sieveOfEratosthenes(limit); // 生成基础素数表

    vector<bool> segment(n - m + 1, true); // 标记区间[m, n]的素数状态
    if (m <= 1) segment[0] = false; // 处理0和1

    for (int p = 2; p <= limit; ++p) {
        if (base_sieve[p]) {
            // 找到区间内第一个能被p整除的数
            int start = max(p * p, (m + p - 1) / p * p);
            for (int j = start; j <= n; j += p) {
                segment[j - m] = false;
            }
        }
    }

    // 收集素数
    for (int i = 0; i < segment.size(); ++i) {
        if (segment[i]) primes.push_back(i + m);
    }
    return primes;
}
```
**时间复杂度`O((n - m) log log n)`**

















