#include "Graph.hpp"

// ============================================================
// ========================  BFS/DFS  =========================
// ============================================================
//----------------------------------
// [1] 广度优先搜索算法 BFS
// [2] 先遍历到的顶点，先访问其邻接顶点
//----------------------------------
template <typename Tv, typename Te> void Graph<Tv, Te>::BFS(int v, int& clock){
    Queue<int> Q;
	Q.enqueue(v);
	dTime(v) = ++clock;
	status(v) = DISCOVERED;
	while(!Q.empty()){
		int v = Q.dequeue();
		for(int u = firstNbr(v); -1 < u; u = nextNbr(v, u)){
			if(status(u) == UNDISCOVERED){
				Q.enqueue(u);
				status(u) = DISCOVERED;
				dTime(u) = ++clock;
				type (v, u) = TREE;
				parent(u) = v;
			}
			else{//无论是DISCOVERED还是VISITED
				type (v, u) = CROSS;
			}
		}
		status(v) = VISITED;
	}
}
template <typename Tv, typename Te> void Graph<Tv, Te>::bfs(int v){
	reset();
	int clock = 0;
	int s = v;
	do
		if(status(v) == UNDISCOVERED)//加判断，如果v的状态是没有被发现。
			BFS(v, clock);
	while(s != (v = (v++ % n)));
}