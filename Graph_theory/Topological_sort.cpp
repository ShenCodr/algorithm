#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include<algorithm>
#include<unordered_map>
#include<queue>

using namespace std;
typedef long long ll;

/*
 * 拓扑排序介绍：
 * 拓扑排序是一种针对有向无环图(DAG)的算法，用于将图中所有顶点排成一个线性序列，
 * 使得对于图中的每一条有向边(u,v)，顶点u在序列中都出现在顶点v之前。
 *
 * 应用场景：
 * 1. 任务调度：确定任务执行顺序，满足依赖关系
 * 2. 编译系统：确定编译顺序，处理文件间依赖
 * 3. 课程安排：根据课程先修关系确定学习顺序
 *
 * 算法步骤：
 * 1. 计算图中所有顶点的入度
 * 2. 将所有入度为0的顶点加入队列
 * 3. 循环从队列取出顶点，将其加入结果序列，并将其所有相邻顶点的入度减1
 * 4. 若减1后入度变为0，则将该顶点加入队列
 * 5. 重复步骤3、4直到队列为空
 * 6. 检查是否所有顶点都已加入结果序列，若是则拓扑排序成功，否则图中存在环
 */

int main() {
    int m, n;
    cin >> n >> m;  // 输入顶点数n和边数m

    vector<int> inDegree(n, 0);  // 存储每个顶点的入度
    vector<int> result;  // 存储拓扑排序结果
    unordered_map<int, vector<int>> depend;  // 邻接表表示图，记录每个顶点指向的所有顶点
    queue<int> q;  // 用于BFS的队列，存储入度为0的顶点

    // 读入所有边，构建图结构和计算入度
    int s, t;
    while (m--) {
        cin >> s >> t;  // 输入一条从s指向t的有向边
        inDegree[t]++;  // t的入度加1
        depend[s].push_back(t);  // 记录s指向t
    }

    // 将所有入度为0的顶点加入队列，这些顶点没有依赖可以最先处理
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    // 拓扑排序的核心BFS过程
    while (!q.empty()) {
        int curr_node = q.front();  // 获取一个入度为0的顶点
        q.pop();
        result.push_back(curr_node);  // 将当前顶点加入结果序列

        // 更新所有当前顶点指向的顶点的入度
        vector<int> nums = depend[curr_node];
        for (int i = 0; i < nums.size(); i++) {
            inDegree[nums[i]]--;  // 将当前顶点所指向的顶点入度减1
            if (inDegree[nums[i]] == 0) {
                q.push(nums[i]);  // 若减1后入度为0，则加入队列
            }
        }
    }

    // 检查是否所有顶点都已加入结果序列
    if (result.size() == n) {
        // 拓扑排序成功，输出结果
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << ' ';
        }
    }
    else {
        // 若结果序列不包含所有顶点，说明图中存在环
        cout << -1;
    }
    return 0;  // 主函数返回
}