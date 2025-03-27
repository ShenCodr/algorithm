# Binary_search
### cpp内置函数：
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
