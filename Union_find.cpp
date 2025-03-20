#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

class Union_find {
private:
	vector<int> parent;//父节点
	vector<int> ranksize;//树的高度

public:
	Union_find(int n) {//初始化
		parent.resize(n);
		ranksize.resize(n, 0);
		for (int i = 0; i < n; i++) {
			parent[i] = i;
		}
	}

	int find(int x) {//查找根节点
		if (parent[x] != x) {
			parent[x] = find(parent[x]);//使x的父节点parent[x]指向根节点
		}
			return parent[x];
	}

	void merge(int x, int y) {//合并算法
		int rootx = find(x);//定义x的根节点
		int rooty = find(y);//定义y的根节点
		if (rootx == rooty) return;//如果x和y的根节点相同，直接返回
		else if (ranksize[rootx] > ranksize[rooty]) {//谁大跟谁
			parent[rooty] = rootx;
		}
		else if (ranksize[rootx] < ranksize[rooty]) {//谁大跟谁
			parent[rootx] = rooty;
		}
		else {//一样高
			parent[rooty] = rootx;
			ranksize[rootx]++;
		}
	}

	bool is_same(int x, int y) {//判断是否在同一集合
		return find(x) == find(y);
	}
};
