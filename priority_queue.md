# priority_queue
**时间复杂度O(logn)**

需要引入<queue>头文件
### 声明
1.**常见的两中情况**
```cpp
priority_queue<int> pq;                              //默认最大堆，堆顶存放最大元素
priority_queue<int, vector<int>, greater<int>> pq;  //最小堆，堆顶存放最小元素
```
2.**自定义比较函数**

**注意priority_queue的自定义比较函数和sort的自定义函数的排序规则是*相反的***
```cpp
//sort
// 按 value 从小到大排序
sort(vec.begin(), vec.end(), [](const Node& a, const Node& b) {
    return a.value < b.value; // a 在前，b 在后
});


struct Node {
    int value;
    int priority;
};

struct Compare {
    bool operator()(const Node& a, const Node& b) {
        return a.value < b.value; // a 的优先级低于 b , b 在堆顶（最大堆）
    }
};
priority_queue<Node, vector<Node>, Compare> pq;
```
3.**常见用法**
```cpp
pq.push()//插入元素，不返回值
pq.pop()//弹出堆顶元素，不返回值
pq.top()//返回堆顶元素
```
