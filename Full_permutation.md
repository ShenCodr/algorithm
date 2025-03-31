# next_permutation
头文件：algorithm

**作用**：

1.将容器（`vector`）中的元素重新排列为当前序列的下一个字典序更大的排列。

2.若存在下一个更大的排列，返回 `true` 并修改容器内容。

3.若当前已经是最大字典序排列（如 `[3,2,1]`），返回 `false`，并将容器恢复为最小字典序排列（如 `[1,2,3]`）。

**特性**:

1.字典序：排列按字典序递增生成。

2.修改原容器：直接修改传入的容器，无需返回值。

3.重复元素处理：自动跳过重复排列（例如 [1,1,2] 会生成唯一排列）。


**配套函数**：`prev_permutation `用于生成前一个字典序更小的排列

### 核心代码

```cpp
    vector<int> nums = {1, 2, 3};
    // 必须先排序，否则无法遍历全部排列
    sort(nums.begin(), nums.end());
    
    do {
        for (int num : nums) cout << num << " ";
        cout << endl;
    } while (next_permutation(nums.begin(), nums.end()));
    
/*输出：
1 2 3 
1 3 2 
2 1 3 
2 3 1 
3 1 2 
3 2 1 
*/
   
```
