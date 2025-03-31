# multiset
**时间复杂度为logn**

**使用前请务必确保包含<set>头文件**
### 声明
```cpp
multiset<int> ms1;                   // 默认升序
multiset<int, greater<int>> ms2; // 降序
multiset<int,cmp>ms3                 //自定义排序函数
```
### 插入
```cpp
ms1.insert(3);
ms1.emplace(4); // 等同于 insert(4)
```
### 删除
```cpp
erase(val)：删除所有值为val的元素，返回被删除的数量。
erase(iterator)：删除迭代器指向的元素。
erase(start, end)：删除区间[start, end)内的元素。
```
### 查找
```cpp
find(val)：返回第一个值为val的迭代器，未找到则返回end()。
count(val)：返回值为`val`的元素数量。
lower_bound(val)：返回第一个大于等于val的迭代器。
upper_bound(val)：返回第一个大于val的迭代器。
```
**multiset不支持直接修改元素，这里推荐先删除再插入新元素**

### 补充
| 函数         | 类型                | 方向       | 起始位置                     |
|--------------|---------------------|------------|------------------------------|
| `begin()`    | **正向迭代器**      | 从前向后   | 指向容器的**第一个元素**     |
| `rbegin()`   | **反向迭代器**      | 从后向前   | 指向容器的**最后一个元素**   |
#### **正向遍历（`begin()`）**
```cpp
multiset<int> ms = {3, 1, 4, 1};
for (auto it = ms.begin(); it != ms.end(); ++it) {
    cout << *it << " "; // 输出：1 1 3 4
}
```

#### **反向遍历（`rbegin()`）**
```cpp
for (auto rit = ms.rbegin(); rit != ms.rend(); ++rit) {
    cout << *rit << " "; // 输出：4 3 1 1
}
```

## 应用
1. **滑动窗口**
```cpp
// 滑动窗口最大值/最小值问题
multiset<int> window;
for (int i = 0; i < n; ++i) {
    window.insert(arr[i]);
    if (i >= k) window.erase(window.find(arr[i-k])); // 注意用find，不是直接erase值
    if (i >= k-1) {
        // *window.begin() 最小值
        // *window.rbegin() 最大值
        cout << *window.rbegin() << " "; // 输出当前窗口最大值
    }
}
```
2.**维护第K大/小元素**
**维护第K小元素**  
   - 始终保持`multiset`中最多有K个元素。
   - 当插入新元素后，若元素数量超过K，删除最大的元素（保证剩余元素均为较小的K个）。
   - 此时`multiset`中的最大元素（`*rbegin()`）即为当前第K小的元素。
   ```cpp
 int add(multiset<int> data,int val) {
          data.insert(val);
           if (data.size() > k) {
               data.erase(--data.end()); // 删除最大的元素
           }
           return data.size() >= k ? *data.rbegin() : -1
  }
   ```
