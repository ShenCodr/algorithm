#include<iostream>
#include<vector>
#include<numeric> 

using namespace std;

class WeightedUnionFind {
private:
    vector<int> parent; // 父节点数组：parent[i] 表示节点 i 的父节点
    vector<int> weight; // 权值数组：weight[i] 表示节点 i 到其父节点 parent[i] 的相对权值（例如差值）
                        // 定义：value[i] = value[parent[i]] + weight[i]

public:
    // 构造函数：初始化 n 个节点
    WeightedUnionFind(int n) {
        parent.resize(n);
        // 使用 iota 初始化父节点数组，每个节点的父节点初始为它自己
        iota(parent.begin(), parent.end(), 0);
        // 初始化权值数组，所有节点的初始权值为 0 (节点到自身的权值为0)
        weight.assign(n, 0);
    }

    // 查找操作（带路径压缩和权值更新）
    // 返回节点 x 所在集合的根节点
    int find(int x) {
        if (parent[x] != x) {
            int old_parent = parent[x]; // 记录原始父节点
            // 递归查找根节点，并将 x 的父节点直接指向根节点
            parent[x] = find(old_parent);
            // 更新权值：
            // 在递归调用 find(old_parent) 后，weight[old_parent] 已经是 old_parent 到根节点的权值
            // 根据 value[x] = value[old_parent] + weight[x] (原始)
            // 和   value[old_parent] = value[root] + weight[old_parent] (更新后)
            // 推导出 value[x] = value[root] + weight[old_parent] + weight[x] (原始)
            // 所以，x 到新的父节点(根节点)的权值需要累加上旧父节点到根节点的权值
            weight[x] += weight[old_parent];
        }
        return parent[x];
    }

    // 合并操作 - 固定方向为 x->y
    bool merge(int x, int y, int w) {
        // 查找 x 和 y 的根节点，同时进行路径压缩和权值更新
        int rootX = find(x);
        int rootY = find(y);

        // 如果 x 和 y 已经在同一个集合中
        if (rootX == rootY) {
            return false; 
        }
        // 固定合并方向：rootX -> rootY（将x的根节点连接到y的根节点下）
        parent[rootX] = rootY;
        
        // 更新 rootX 的权值 weight[rootX]
        // 目标是满足：value[rootX] = value[rootY] + weight[rootX]
        // 已知关系：value[y] - value[x] = w
        // find后已知：value[x] = value[rootX] + weight[x]
        //            value[y] = value[rootY] + weight[y]
        // 代入关系式：(value[rootY] + weight[y]) - (value[rootX] + weight[x]) = w
        // 整理得到：value[rootX] - value[rootY] = weight[y] - weight[x] - w
        // 所以，weight[rootX] 应该设置为 weight[y] - weight[x] - w
        weight[rootX] = weight[y] - weight[x] - w;
        return true; // 合并成功
    }

    // 判断两个节点是否在同一个集合中
    bool is_same(int x, int y) {
        return find(x) == find(y);
    }

    // 查询节点 x 和节点 y 之间的权值差 (value[y] - value[x])
    // **前提**：x 和 y 必须在同一个集合中！否则结果无意义。
    int diff(int x, int y) {
        // 确保 x 和 y 的路径都被压缩，并且 weight[x] 和 weight[y] 都更新为相对于根节点的值
        int rootX = find(x);
        int rootY = find(y);
        // 如果根不同，说明不在同一集合，差值无意义
        if (rootX != rootY) {
             return -999999; // 返回一个特殊值
        }

        // 因为 find(x) 保证了 value[x] = value[rootX] + weight[x]
        // 且   find(y) 保证了 value[y] = value[rootY] + weight[y]
        // 又因为 rootX == rootY
        // 所以 value[y] - value[x] = weight[y] - weight[x]
        return weight[y] - weight[x];
    }
};
