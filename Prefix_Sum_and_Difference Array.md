# 前缀和 (Prefix Sum)
### 一维前缀和
**前缀和数组 S[i] 表示原数组 A[1..i] 的和**

`S[0] = 0`

`S[i] = S[i-1] + A[i] （i ≥ 1）`

**查询区间和：**
**计算区间 [L, R] 的和：Sum = S[R] - S[L-1]**
```cpp
int n = 5;
int A[] = {0, 1, 2, 3, 4, 5}; // A[1..5]
int S[6] = {0};

void build_prefix() {
    for (int i = 1; i <= n; i++) {
        S[i] = S[i-1] + A[i];
    }
}

int query(int L, int R) {
    return S[R] - S[L-1];
}
```

# 差分 (Difference Array)
###  一维差分
**差分数组 D[i] 是原数组 A[i] 与 A[i-1] 的差值。**


`D[1] = A[1]`

`D[i] = A[i] - A[i-1] （i ≥ 2）`

**区间修改：**
**对 [L, R] 区间加 K：**
**D[L] += K，D[R+1] -= K（若 R+1 ≤ n）**
```cpp
int n = 5;
int A[] = {0, 1, 2, 3, 4, 5}; // A[1..5]
int D[6] = {0};

void build_diff() {
    D[1] = A[1];
    for (int i = 2; i <= n; i++) {
        D[i] = A[i] - A[i-1];
    }
}

void update(int L, int R, int K) {
    D[L] += K;
    if (R+1 <= n) D[R+1] -= K;
}

// 通过差分数组还原数组
void restore() {
    for (int i = 1; i <= n; i++) {
        A[i] = A[i-1] + D[i];
    }
}
```
