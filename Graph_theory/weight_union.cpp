#include<iostream>
#include<vector>
#include<numeric> // 包含 std::iota

// 使用 std 命名空间
using namespace std;

class WeightedUnionFind {
private:
    vector<int> parent; // 父节点数组：parent[i] 表示节点 i 的父节点
    vector<int> rank;   // 秩数组：用于按秩合并优化，rank[i] 表示以 i 为根的子树的秩（大致高度）
    vector<int> weight; // 权值数组：weight[i] 表示节点 i 到其父节点 parent[i] 的相对权值（例如差值）
                        // 定义：value[i] = value[parent[i]] + weight[i]

public:
    // 构造函数：初始化 n 个节点
    WeightedUnionFind(int n) {
        parent.resize(n);
        // 使用 iota 初始化父节点数组，每个节点的父节点初始为它自己
        iota(parent.begin(), parent.end(), 0);
        // 初始化秩数组，所有节点的初始秩为 0
        rank.assign(n, 0);
        // 初始化权值数组，所有节点的初始权值为 0 (节点到自身的权值为0)
        weight.assign(n, 0);
    }

    // 查找操作（带路径压缩和权值更新）
    // 返回节点 x 所在集合的根节点
    int find(int x) {
        // 路径压缩：如果 x 不是根节点 (父节点不是自己)
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
        // 返回根节点
        return parent[x];
    }

    // 合并操作
    // 尝试合并包含 x 和 y 的两个集合
    // 参数 w 代表已知的关系：value[y] - value[x] = w
    // 如果 x 和 y 已经在同一集合，则检查权值关系是否冲突（可选，这里仅返回false）
    // 如果不在同一集合，则进行合并，并更新权值
    // 返回 true 如果合并成功，false 如果 x 和 y 已经在同一集合
    bool merge(int x, int y, int w) {
        // 查找 x 和 y 的根节点，同时进行路径压缩和权值更新
        // find(x) 后，weight[x] 存储的是 value[x] - value[rootX]
        // find(y) 后，weight[y] 存储的是 value[y] - value[rootY]
        int rootX = find(x);
        int rootY = find(y);

        // 如果 x 和 y 已经在同一个集合中
        if (rootX == rootY) {
            // 可选：检查现有权值是否与新权值 w 矛盾
            // 检查 (weight[y] - weight[x] == w) 是否成立
            // cout << "节点 " << x << " 和 " << y << " 已在同一集合。" << endl;
            // cout << "预期差值: " << w << ", 实际差值: " << (weight[y] - weight[x]) << endl;
            // return (weight[y] - weight[x] == w); // 如果需要严格检查冲突，可以这样返回
            return false; // 这里简单返回 false 表示无需合并
        }

        // 按秩合并：将秩小的树合并到秩大的树上
        if (rank[rootX] < rank[rootY]) {
            // 将 rootX 的父节点设为 rootY
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

        } else { // rank[rootX] >= rank[rootY]
            // 将 rootY 的父节点设为 rootX
            parent[rootY] = rootX;
            // 更新 rootY 的权值 weight[rootY]
            // 目标是满足：value[rootY] = value[rootX] + weight[rootY]
            // 已知关系：value[y] - value[x] = w
            // find后已知：value[x] = value[rootX] + weight[x]
            //            value[y] = value[rootY] + weight[y]
            // 代入关系式：(value[rootY] + weight[y]) - (value[rootX] + weight[x]) = w
            // 整理得到：value[rootY] - value[rootX] = weight[x] - weight[y] + w
            // 所以，weight[rootY] 应该设置为 weight[x] - weight[y] + w
            weight[rootY] = weight[x] - weight[y] + w; // 注意这里符号推导

             // 如果两个根节点的秩相同，合并后 rootX 的秩加 1
            if (rank[rootX] == rank[rootY]) {
                rank[rootX]++;
            }
        }
        return true; // 合并成功
    }

    // 判断两个节点是否在同一个集合中
    bool is_same(int x, int y) {
        // 通过比较它们的根节点是否相同来判断
        return find(x) == find(y);
    }

    // 查询节点 x 和节点 y 之间的权值差 (value[y] - value[x])
    // **前提**：x 和 y 必须在同一个集合中！否则结果无意义。
    // 建议调用前先使用 is_same() 检查。
    // 如果不在同一集合，可以返回一个特殊值或抛出异常（这里假设已在同一集合）
    int diff(int x, int y) {
        // 确保 x 和 y 的路径都被压缩，并且 weight[x] 和 weight[y] 都更新为相对于根节点的值
        int rootX = find(x);
        int rootY = find(y);
        // 如果根不同，说明不在同一集合，差值无意义（或者可以根据题目要求返回特定值）
        if (rootX != rootY) {
             // 例如返回一个极大/极小值或者抛出异常
             // throw std::runtime_error("Nodes are not in the same set.");
             return -999999; // 示例：返回一个特殊值
        }

        // 因为 find(x) 保证了 value[x] = value[rootX] + weight[x]
        // 且   find(y) 保证了 value[y] = value[rootY] + weight[y]
        // 又因为 rootX == rootY
        // 所以 value[y] - value[x] = (value[rootY] + weight[y]) - (value[rootX] + weight[x])
        //                        = weight[y] - weight[x]
        return weight[y] - weight[x];
    }
};

// --- 主函数示例 ---
int main() {
    // 创建一个包含 5 个元素的带权并查集 (节点 0, 1, 2, 3, 4)
    WeightedUnionFind wuf(5);

    cout << "初始化状态:" << endl;
    cout << "节点 1 和 节点 2 是否同集合? " << (wuf.is_same(1, 2) ? "是" : "否") << endl; // 否

    // 合并操作示例：
    // 假设 value[1] - value[0] = 10
    wuf.merge(0, 1, 10);
    cout << "\n合并 (0, 1, 10) 后:" << endl;
    cout << "节点 0 和 节点 1 是否同集合? " << (wuf.is_same(0, 1) ? "是" : "否") << endl; // 是
    if (wuf.is_same(0, 1)) {
        cout << "节点 1 相对于 节点 0 的权值差 (value[1]-value[0]): " << wuf.diff(0, 1) << endl; // 10
    }


    // 假设 value[2] - value[1] = 20
    wuf.merge(1, 2, 20);
    cout << "\n合并 (1, 2, 20) 后:" << endl;
    cout << "节点 0 和 节点 2 是否同集合? " << (wuf.is_same(0, 2) ? "是" : "否") << endl; // 是
    if (wuf.is_same(0, 2)) {
        // value[2] - value[0] = (value[2]-value[1]) + (value[1]-value[0]) = 20 + 10 = 30
        cout << "节点 2 相对于 节点 0 的权值差 (value[2]-value[0]): " << wuf.diff(0, 2) << endl; // 30
        cout << "节点 0 相对于 节点 2 的权值差 (value[0]-value[2]): " << wuf.diff(2, 0) << endl; // -30
    }

    // 假设 value[4] - value[3] = 5
    wuf.merge(3, 4, 5);
    cout << "\n合并 (3, 4, 5) 后:" << endl;
    cout << "节点 0 和 节点 4 是否同集合? " << (wuf.is_same(0, 4) ? "是" : "否") << endl; // 否

    // 假设 value[3] - value[1] = 50 (连接两个不同的集合)
    wuf.merge(1, 3, 50);
    cout << "\n合并 (1, 3, 50) 后:" << endl;
    cout << "节点 0 和 节点 4 是否同集合? " << (wuf.is_same(0, 4) ? "是" : "否") << endl; // 是
    if (wuf.is_same(0, 4)) {
        // value[4] - value[0] = (value[4]-value[3]) + (value[3]-value[1]) + (value[1]-value[0])
        //                    = 5 + 50 + 10 = 65
        cout << "节点 4 相对于 节点 0 的权值差 (value[4]-value[0]): " << wuf.diff(0, 4) << endl; // 65
    }

     // 尝试合并同一集合内的边，但权值与现有关系冲突
     // 当前 value[2] - value[0] = 30
     // 尝试加入 value[2] - value[0] = 40 的关系
     cout << "\n尝试合并 (0, 2, 40) (预期失败或返回false):" << endl;
     bool merge_result = wuf.merge(0, 2, 40);
     cout << "合并操作返回值: " << (merge_result ? "true" : "false") << endl; // 应为 false
     // 检查权值是否被错误修改 (不应被修改)
     cout << "节点 2 相对于 节点 0 的权值差 (value[2]-value[0]): " << wuf.diff(0, 2) << endl; // 仍为 30

    return 0;
}
