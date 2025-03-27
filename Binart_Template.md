# Binary_search
## cpp内置函数：
``` c++
   vector<int> vec = {1, 3, 4, 5, 7, 9, 10};
    
    // 检查元素是否存在
    bool found = binary_search(vec.begin(), vec.end(), 5); // 返回true
    
    // lower_bound: 返回指向大于等于指定值的第一个元素的迭代器
    auto lower = lower_bound(vec.begin(), vec.end(), 6);
    // 返回指向7的迭代器，即第一个>=6的元素
    
    // upper_bound: 返回指向大于指定值的第一个元素的迭代器
    auto upper = upper_bound(vec.begin(), vec.end(), 7);
    // 返回指向9的迭代器，即第一个>7的元素
```
### 自定义实现
```c++
   int lowerbound(vector<int> &nums, int target){
    int l = 0;
    int r = nums.size() - 1;
    while (l <= r)
    {
        int mid = (r - l) / 2 + l;
        if (nums[mid] >= target)
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        } //此时l=r+1;//左边全部小于target，右边全部大于等于target
    }
    return l; // nums[l]就是>=target的第一个数
}
```
### 浮点二分
**需要设置精度**
```c++
   //precision表示精度
  while (right - left > precision) {
        double mid = left + (right - left) / 2;
        if (......)
            return mid;  // 找到足够接近的值
        if (......)
            left = mid;
        else
            right = mid;
    }
```
## 二分答案
对于最大化问题（例如最大化最小值）：
如果*check(mid)* 为 *true*（意味着 *mid* 是一个可能的答案，或者存在更好的答案），我们尝试更大的值，*left = mid*，并记录 *mid* 可能是一个潜在的最优解。
如果 *check(mid)* 为 *false*（意味着 *mid* 太大了，无法达到），我们需要减小答案，*right = mid - 1*。

对于最小化问题（例如最小化最大值）：
如果 *check(mid)* 为 *true*（意味着 *mid* 是一个可能的答案，或者存在更好的答案），我们尝试更小的值，*right = mid*，并记录 *mid* 可能是一个潜在的最优解。
如果 *check(mid)* 为 *false*（意味着 *mid* 太小了，无法达到），我们需要增大答案，*left = mid + 1*。

### 最大化最小值:找到一个最小的值 x，使得某个条件满足。
```c++
// 判断函数：检查mid是否可行
bool check(int mid, vector<int>& arr, int additional_param) {
    // 实现具体的判断逻辑
    // 如果mid值满足条件，返回true，否则返回false
}

int minimizeMaximum(vector<int>& arr, int param) {
    // 确定搜索范围
    int left = 0;  // 最小可能值
    int right = 1e9;  // 最大可能值，根据题目调整
    int result = right;  // 默认结果
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (check(mid, arr, param)) {
            // mid可行，尝试更小的值
            result = mid;
            right = mid - 1;
        } else {
            // mid不可行，尝试更大的值
            left = mid + 1;
        }
    }
    
    return result;
}
```

### 最小化最大值：找到一个最大的值 x，使得某个条件满足。
```c++
// 判断函数：检查mid是否可行
bool check(int mid, vector<int>& arr, int additional_param) {
    // 实现具体的判断逻辑
    // 如果mid值满足条件，返回true，否则返回false
}

int maximizeMinimum(vector<int>& arr, int param) {
    // 确定搜索范围
    int left = 0;  // 最小可能值
    int right = 1e9;  // 最大可能值，根据题目调整
    int result = left;  // 默认结果
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (check(mid, arr, param)) {
            // mid可行，尝试更大的值
            result = mid;
            left = mid + 1;
        } else {
            // mid不可行，尝试更小的值
            right = mid - 1;
        }
    }
    
    return result;
}
```
