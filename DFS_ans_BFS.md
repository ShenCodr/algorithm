# 常用的搜索模板
**这类题目都比较简单，不需要死记模板，多练即可（连我都觉得不难那是真不难）**
### **这里给出[刷题题单](https://leetcode.cn/discuss/post/3580195/fen-xiang-gun-ti-dan-wang-ge-tu-dfsbfszo-l3pa/)，只需写出基础题单的前几题熟悉即可**
## DFS(深度优先搜索)
**应用场景：**

1.寻找所有可能的路径 (如迷宫的所有解)

2.连通区域标记 (如计算岛屿的数量)

3.解决不需要最短路径的问题

4.空间复杂度通常较低，适合深层次探索

5.递归实现简洁，容易编写

### 首先是判断边界函数
```c++
// 检查坐标是否在网格内且未访问过
    bool isValid(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols && !visited[x][y];//visited数组初始化为false。
    }
```
### DFS核心代码
```c++
// DFS实现
    void dfs(vector<vector<int>>& grid, int x, int y) {
        // 标记当前单元格为已访问
        visited[x][y] = true;
        
        // 处理当前单元格
        //这里根据题目意思来写
        
        // 遍历四个方向，需要提前实现dx，dy数组，根据题目要求的方向来
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            // 检查新坐标是否有效且未访问过
            if (isValid(nx, ny)) {
                // 这里可以添加额外条件，如检查单元格值是否为特定值
                // if (grid[nx][ny] == 某个条件) 
                dfs(grid, nx, ny);
            }
        }
    }
```

## BFS(广度优先搜索)
**应用场景：**

1.寻找最短路径 (如迷宫最短路径)

2.层次遍历 (如计算到起点的距离)

3.需要按照"距离"顺序访问的场景

4.在无权图中找最短路径更高效

5.适合解决"最少步数"类型的问题

### 首先是判断边界函数(和DFS相同)
```c++
// 检查坐标是否在网格内且未访问过
    bool isValid(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols && !visited[x][y];//visited数组初始化为false。
    }
```
### BFS核心代码
```c++
    // BFS实现
    void bfs(vector<vector<int>>& grid, int startX, int startY) {
        queue<pair<int, int>> q;
        
        // 将起始点加入队列并标记为已访问
        q.push({startX, startY});
        visited[startX][startY] = true;
        
        while (!q.empty()) {
            // 取出队首元素
            auto [x, y] = q.front();
            q.pop();
            
            // 处理当前单元格
            //这里根据题目意思来写
            
            // 遍历四个方向
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                
                // 检查新坐标是否有效且未访问过
                if (isValid(nx, ny)) {
                    // 将新坐标加入队列并标记为已访问
                    q.push({nx, ny});
                    visited[nx][ny] = true;
                }
            }
        }
    }
```

