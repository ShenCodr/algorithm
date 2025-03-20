#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

//基于Union_find的krusral的时间复杂度为nlogn，优于prim，所以我主要学习krusral

/*
kruscal的思路：

边的权值排序，因为要优先选最小的边加入到生成树里
遍历排序后的边
如果边首尾的两个节点在同一个集合，说明如果连上这条边图中会出现环
如果边首尾的两个节点不在同一个集合，加入到最小生成树，并把两个节点加入同一个集合
*/

//接下来先实现Union_find（简化版，没有考虑树的高度）
class Union_find {
private:
    vector<int>father;
public:
    //初始化
    Union_find(int n) {
        father.resize(n + 1);
        //我这里节点从1开始，若从0开始自行更改即可
        for (int i = 1; i <= n; i++) {
            father[i] = i;//使他们的父节点指向自己，说明最初大家都是根节点
        }
    }

    //查找根节点
    int find(int x) {
        if (father[x] == x)return x;//这里如果x的父节点指向自己，说明x是根节点
        else return father[x] = find(father[x]);//否则寻找父节点的根节点,这里用了路径压缩
    }

    //这里的插入算法相对比较简化,将v的父节点指向u
    void insert(int u, int v) {//这里是将v的父节点指向u
        int new_u = find(u);//使他们指向自己的根节点
        int new_v = find(v);
        if (new_u == new_v)return;//如果根节点相同就直接返回
        father[new_v] = new_u;//将v的父节点指向u
    }

    //判断是否属于同一个集合
    bool is_same(int u, int v) {
        int new_u = find(u);//使他们指向自己的根节点
        int new_v = find(v);
        return new_u == new_v;
    }
};


//创建边权类型结构体
struct Edge {
    int u, v, val;//起点，终点，边值
};
int main() {

    int node_nums;//节点数量
    int edge_nums;//边的数量
    cin >> node_nums>>edge_nums;

    int u, v, val;//起点，终点，边值
    vector<Edge>edges;
    for (int i = 0; i < edge_nums; i++) {
        cin >> u >> v >> val;
        edges.push_back({ u,v,val });
    }
    //下面对edges排序，因为krusral就是选择最小的边权并且两点不能在同一集合中
    sort(edges.begin(), edges.end(), [](const Edge u, const Edge v) {
        return u.val < v.val;//按边权由小到大排序；
        });

    vector<Edge> result; // 存储最小生成树的边
    int result_sum = 0;//最小生成树的总代价
    //初始化
    Union_find krusral(node_nums);

    for (Edge& edge : edges) {

        int u = krusral.find(edge.u);
        int v = krusral.find(edge.v);

        if (u != v) {
            result.push_back(edge);
            result_sum += edge.val;
            krusral.insert(u, v);
        }
    }

    //打印结果
    for (Edge edge : result) {
        cout << edge.u << " ———— " << edge.v << " : " << edge.val << endl;
    }

    cout << "The Total Val Is: " << result_sum << endl;
}

