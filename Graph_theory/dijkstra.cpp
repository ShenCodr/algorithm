#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
#include<list>
using namespace std;

//默认的堆是大根堆，这里我们需要使用小根堆来优化算法
//比较函数，second表示边权，我们在这里按边权排序
struct cmp {
	bool operator()(const pair<int, int>x, const pair<int, int>y) {
		//这里注意，堆的判断函数方向与sort函数相反
		return x.second > y.second;
	}
};

//我们这里利用邻接表来实现
//定义Edge类型
struct Edge {
	int next_node;//邻接顶点
	int val;//边权
	//构造函数
	Edge(int x, int y) :next_node(x), val(y) {};
};

/*
 dijkstra 三部曲：
第一步，选源点到哪个节点近且该节点未被访问过
第二步，该最近节点被标记访问过
第三步，更新非访问节点到源点的距离（即更新minDist数组）
*/

int main() {
	int n, m, u, v, val;//分别是顶点数，边数，起点，终点，边权
	cin >> n >> m;
	//邻接表
	vector<list<Edge>>grid(n + 1);

	//建表
	while (m--) {
		cin >> u >> v >> val;
		/*Edge *temp = new Edge(v, val);
		grid[u].push_back(*temp);*/
		grid[u].push_back(Edge(v, val));  // 直接构造对象并添加到列表中，防止内存泄漏
	}

	//明确起点和终点
	int start = 1; int end = n;

	//各个点到源点的距离,初始是无穷大
	vector<int>MinDist(n + 1, INT_MAX);

	//标记各个顶点到源点的路径是否确定
	vector<bool>check(n + 1, false);

	//优先队列，存储<节点，节点到源点的权值>，这里用的是小根堆，堆顶存放最小权值
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp>q;

	//初始化优先队列,源点到源点的距离为0
	q.push({ start,0 });
	MinDist[start] = 0;

	//记录路径
	vector<int> parent(n + 1, -1);

	//开始三部曲
	while (!q.empty()) {

		// 1. 第一步，选源点到哪个节点近且该节点未被访问过 （通过优先级队列来实现）
		pair<int, int>curr = q.top();
		q.pop();

		//被访问过了就跳过
		if (check[curr.first])continue;

		//第二步，该最近节点被标记访问过
		check[curr.first] = true;

		//第三步，更新非访问节点到源点的距离（即更新minDist数组）
		//起初，grid存放的是所有与源点直接相连的点
		for (Edge& edge : grid[curr.first]) {
			//对于源点来说，MinDist[curr.frist]==0，edge.val就是源点到与他直接相连的节点的权值，此时的MinDist[edge.next_node]==INT_MAX
			//所以肯定会更新MinDist
			if (!check[edge.next_node] && MinDist[curr.first] + edge.val < MinDist[edge.next_node]) {
				MinDist[edge.next_node] = MinDist[curr.first] + edge.val;
				q.push({ edge.next_node,MinDist[edge.next_node] });
				//更新路径
				//curr.frist->edge.next_node
				parent[edge.next_node] = curr.first;
			}
		}

	}
	if (MinDist[end] == INT_MAX) cout << -1 << endl; // 不能到达终点
	else {
		cout << MinDist[end] << endl; // 到达终点最短路径
		// 输出从起点到终点的完整路径
		cout << "最短路径: ";
		vector<int> path;
		for (int at = end; at != -1; at = parent[at]) {
			path.push_back(at);
		}
		// 反转路径（因为我们是从终点开始回溯的）
		reverse(path.begin(), path.end());

		// 漂亮地打印路径
		for (int i = 0; i < path.size(); i++) {
			cout << path[i];
			if (i < path.size() - 1) cout << " -> ";
		}
		cout << endl;
	}
}
