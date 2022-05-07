// 建立邻接表，总共n个节点
vector<vector<int>> e(n);

// 单向边 u -> v
e[u].emplace_back(v);

// 双向边 == 两个单向边
e[u].emplace_back(v);
e[v].emplace_back(u);

// 无向图遍历
void dfs(int u,int fa){
	...
	for(int v:e[u]){
		if(v == fa) continue; // 避免访问父节点
		...
		dfs(v, u);
		...
	}
}
// 调用
dfs(root, -1);// 根节点的father定义为-1即可
///////////////////////////////////

// 带边权版本
using pii = pair<int,int>;
vector<vector<pii>> e(n);

// 单向边 u -> v, 边权为w
// 写成(w,v)而不是(v,w)可以方便后面写Dijkstra的优先队列
e[u].emplace_back(pair(w,u));

// 双向边 == 两个单向边
e[u].emplace_back(pair(w,v));
e[v].emplace_back(pair(w,u));

// Dijkstra优先队列(两种写法)
// 1. 写成小根堆，权值保持不变
priority_queue<pii,vector<pii>,greater<pii>>> q;
q.push(pair(w, ...));
// 2. 写成大根堆，权值加负号
priority_queue<pii>
q.push(pair(-w, ...));
//////////////////////////////////

// 最大流版本(u, capacity, u在e[v]中的序号)
vector<vector<tuple<int,int,int>>> e;

// 加边, 正向+反向
void addedge(int u,int v,int w){
    e[u].emplace_back(make_tuple(v,w,(int)e[v].size()));
    e[v].emplace_back(make_tuple(u,0,(int)e[u].size()-1));
}
