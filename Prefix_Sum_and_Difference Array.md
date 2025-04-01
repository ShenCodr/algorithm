# 前缀和 (Prefix Sum)
### 一维前缀和

`s[i+1]=s[i]+a[i]`

**a[left] 到 a[right] 的元素和等于s[right+1]−s[left]**

### 实现代码
```cpp
for (int i = 0; i < nums.size(); i++) {
        s[i + 1] = s[i] + nums[i];
}
```

# 差分 (Difference Array)
###  一维差分
**差分数组 D[i] 是原数组 A[i] 与 A[i-1] 的差值。**

`D[0] = A[0]`

`D[i] = A[i] - A[i-1] （i ≥ 1）`

**区间修改：**
**对 [L, R] 区间加 K：**
**D[L] += K，D[R+1] -= K（若 R+1 ≤ n）**
```cpp
int A[] = {0, 1, 2, 3, 4, 5}; // A[0..5]
int D[6] = {0};

void build_diff() {
    D[0] = A[0];
    for (int i = 1; i < A.size(); i++) {
        D[i] = A[i] - A[i-1];
    }
}

void update(int L, int R, int K) {
    D[L] += K;
    if (R+1 <= n) D[R+1] -= K;
}

// 通过差分数组还原数组
void restore() {
    A[0]=D[0];
    for (int i = 1; i < A.size(); i++) {
        A[i] = A[i-1] + D[i];
    }
}
```
