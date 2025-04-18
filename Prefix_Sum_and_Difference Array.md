# 前缀和 (Prefix Sum)
## 一维前缀和

`s[i+1]=s[i]+a[i]`

**a[left] 到 a[right] 的元素和等于s[right+1]−s[left]**

### 实现代码
```cpp
for (int i = 0; i < nums.size(); i++) {
        s[i + 1] = s[i] + nums[i];
}
```


## 二维前缀和

`s[i+1][j+1]`表示左上角为`a[0][0]`右下角为`a[i][j]`的子矩阵元素和

**定义方法：** `s[i+1][j+1]=s[i+1][j]+s[i][j+1]-s[i][j]+a[i][j]`

### 计算子矩阵之和：  

**设子矩阵左上角为a[r1][c1],右下角为a[r2][c2]:**

`sum=s[r2+1][c2+1]-s[r2+1][c1]-s[r1][c2+1]+s[r1][c1]`


# 差分 (Difference Array)
###  一维差分
**差分数组 D[i] 是原数组 A[i] 与 A[i-1] 的差值。**

`D[0] = A[0]`

`D[i] = A[i] - A[i-1] （i ≥ 1）`

**区间修改：**
**对 [L, R] 区间加 K：**
**D[L] += K，D[R+1] -= K（若 R+1 ≤ n）**
```cpp
const int SIZE = 6;
int A[SIZE] = {0, 1, 2, 3, 4, 5}; // A[0..5]
int D[SIZE] = {0};

void build_diff() {
    D[0] = A[0];
    for (int i = 1; i < SIZE; i++) {
        D[i] = A[i] - A[i-1];
    }
}

void update(int L, int R, int K) {
    D[L] += K;
    if (R+1 < SIZE) D[R+1] -= K;
}

// 通过差分数组还原数组
void restore() {
    A[0]=D[0];
    for (int i = 1; i < SIZE; i++) {
        A[i] = A[i-1] + D[i];
    }
}
```
