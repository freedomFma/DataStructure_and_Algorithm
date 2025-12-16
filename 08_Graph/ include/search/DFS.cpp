#include "Graph.hpp"
// ============================================================
// ========================  BFS/DFS  =========================
// ============================================================
//----------------------------------
// [1] 深度优先搜索算法 DFS
// [2] 后遍历到的顶点，先访问其邻接顶点
//----------------------------------
//深度优先搜索算法：DFS的递归版本
template <typename Tv, typename Te> void Graph<Tv, Te>::DFS(int v, int& clock){
	status(v) = DISCOVERED;
	dTime(v) = ++clock;
	for(u = firstNbr(v); -1 < u; u = nextNbr(v, u)){
		switch(status(u)){
			case (status(u) == UNDISCOVERED):
				type(v, u) = TREE;
				parent(u) = v;
				DFS(u, clock);
				break;
			case (status(u) == DISCOVERED):
				type(v, u) = BACKWARD;
				break;
			default://status(u) == VISITED  u已经访问完毕（VISITED，有向图），则视承袭关系分为前向边或者跨边
				type(v, u) = (dTime(v) < dTime(u) ? FORWARD : CROSS);
				//u的生死都在v的生死周期之内，那么v就是u的前向边
				//如果u的生死跟v的生死没有任何关系（没有重合），那么v就是u的跨边
				break;
		}
	} 
	status(v) = VISITED;
	fTime(v) = ++clock;
}
//DFS的迭代版本（使用栈）
template <typename Tv, typename Te> void Graph<Tv, Te>::DFS_I(int v, int& clock){
	Stack<int> S;
	status(v) = DISCOVERED;
	dTime(v) = ++clock;
	S.push(v);
	while(!S.empty()){
		v = S.pop();
		for(u = firstNbr(v); -1 < u; u = nextNbr(v, u)){
			switch(status(u)){
				case (status(u) == UNDISCOVERED):
					status(u) = DISCOVERED;
					dTime(u) = ++clock;
					type(v, u) = TREE;
					parent(u) = v;
					break;
				case (status(u) == DISCOVERED):
					type(v, u) = BACKWARD;
					break;
				default://status(u) == VISITED
					type(v, u) = (dTime(v) > dTime(u) ? FORWARD : CROSS);
					break;
			}
		}
		status(v) = VISITED;
		fTime(v) = ++clock; 
	}
}
template <typename Tv, typename Te> void Graph<Tv, Te>::dfs(int v){
	reset();
	int clock = 0;
	int s = v;
	do
		if(status(v) == UNDISCOVERED)//加判断，如果v的状态是没有被发现。
			DFS(v, clock);
	while(s != (v = (v++ % n)));//这里有点巧妙呀
}