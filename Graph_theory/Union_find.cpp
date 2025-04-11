#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

class Union_find {
private:
	vector<int> parent;//父节点

public:
	Union_find(int n) {//初始化
		parent.resize(n);
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

	void merge(int x, int y) {
             int rootx = find(x); // 找到 x 的根
             int rooty = find(y); // 找到 y 的根
           if (rootx == rooty) return; // 同一个集合，直接返回

                // 固定把 x 的根合并到 y 的根下面（x → y）
            parent[rootx] = rooty;
	}

	bool is_same(int x, int y) {//判断是否在同一集合
		return find(x) == find(y);
	}
};
