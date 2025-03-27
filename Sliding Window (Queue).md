# 滑动窗口(单调队列)
--- 
## 定长窗口

### 求最小
```c++
vector<int> slidingWindowMinimum(vector<int>& nums, int k) {
    vector<int> result;
    deque<int> dq; // 存放索引的双端队列
    
    for (int i = 0; i < nums.size(); i++) {
        // 1. 移除超出窗口范围的元素（队头）
        if (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // 2. 维护单调队列，移除队尾比当前元素大的值
        while (!dq.empty() && nums[dq.back()] > nums[i]) {
            dq.pop_back();
        }
        
        // 3. 将当前索引加入队列
        dq.push_back(i);
        
        // 4. 当窗口形成时，输出结果
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    
    return result;
}
```

### 求最大
```c++
vector<int> slidingWindowMaximum(vector<int>& nums, int k) {
    vector<int> result;
    deque<int> dq;
    
    for (int i = 0; i < nums.size(); i++) {
        // 移除超出窗口范围的元素
        if (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // 维护单调队列 - 注意这里比较方向变了喵！
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    
    return result;
}
```

## 不定长窗口
```c++
// 可变大小窗口的通用模板（如：最长满足某条件的子数组）
int variableSizeWindowTemplate(vector<int>& nums) {
    int left = 0;
    int result = 0;  // 存储最终结果
    
    for (int right = 0; right < nums.size(); right++) {
        // 添加nums[right]到窗口
        
        // 收缩窗口直到满足条件
        while (/* 窗口需要收缩的条件 */) {
            // 移除nums[left]的影响
            left++;
        }
        
        // 更新结果
        result = max(result, right - left + 1);
    }
    
    return result;
}
```
**不定长窗口多搭配unordered_map使用**

这里介绍unordered_map的部分用法

1.**创建**
```c++

unordered_map<string, int> map;
```


2.**插入**
```c++
map["ShenCodr"] = 95;    // 使用[]运算符

map.insert({"key", value});  // 使用insert

map.emplace("key", value);  // 原地构造，避免临时对象
```

3.**查找**

```c++
// 使用[]运算符 - 注意：如果键不存在会创建一个！
//所以通常不用这个
int value = map["key"];  

// 使用find() - 返回迭代器，不会插入新元素
//如果不存在的话，迭代器会指向end
auto it = map.find("key");
if (it != map.end()) {
    int value = it->second;
} else {
    cout << "键不存在" << endl;
}

// 使用count() - 检查键是否存在
// 同样不会插入新元素
if (map.count("key") > 0) {
    // 键存在
}
```

4.**删除**

```c++
map.erase("key");  // 删除指定键
map.clear();       // 清空所有元素
```

5.**其他用法**

```c++
size_t size = map.size();  // 获取元素个数
bool empty = map.empty();  // 检查是否为空

// 遍历所有元素
for (const auto& [key, value] : map) {  // C++17结构化绑定
    std::cout << key << ": " << value << std::endl;
}
```
