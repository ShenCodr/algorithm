# 这里介绍unordered_map的部分用法

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
