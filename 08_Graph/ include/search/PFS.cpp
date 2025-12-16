#include "Graph.hpp"
// ============================================================
// =======================  优先级搜索  =========================
// ============================================================
//优先级搜索
template <typename Tv, typename Te> template <typename PU> 
void Graph<Tv, Te>::PFS(int v, PU prioUpdater){
	priority(s) = 0;
	status(s) = VISITED;
	parent(s) = -1;
	while(1){
		// 1. 遍历 s 的所有邻居 w，更新它们的 priority
		for(int w = firstNbr(s); -1< w; w = nextNbr(s, w))
			prioUpdater(this, s, w);
			
		// 2. 在所有未发现（UNDISCOVERED）的顶点中找 priority 最小的
		// 作为下一个 s
		for(int shortest = INT_MAX, w = 0; w < n; w++){
			if(status(w) == UNDISCOERED)
				if(shortest > priority(w)){
					shortest = priority(w);
					s = w;
				}
		}
		// 3. 如果选中的 s 已经是 VISITED（说明没有未发现的点了），退出
		if (status(s) == VISITED) break;
		
		// 4. 标记 s 为已访问，并记录其父边为 TREE 边
		status(s) = VISITED;
		type(parent(s), s) = TREE;
	}
}
template <typename Tv, typename Te> template <typename PU> 
void Graph<Tv, Te>::pfs(int v, PU prioUpdater){
	reset();
	int v = s;
	do{
		if(status(v) == UNDISCOVERED)
			PFS(v, prioUpdater);
	}while(s != (v = (++v % n)));
}


template <typename Tv, typename Te> template <typename PU> 
void Graph<Tv, Te>::pfs(int v, PU prioUpdater){
	reset();//初始化，所有的优先级都是正无穷
	int v = s;
	do{
		if(status(v) == UNDISCOVERED)
			PFS(v, prioUpdater);
	}while(s != (v = (++v % n)));
}

//最小支撑树Prim算法的prioUpdater
template <typename Tv, typename Te> struct PrimPU{
    virtual void operator()(Graph<Tv, Tv>* G, int uk, int v){
        if(G->status(v) == UNDISCOVERED){//如果v还没有被发现
            if(G->priority(v) > G->weight(uk, v))
                G->priority(v) = G->weight(uk, v);
                G->parent(v) = uk;
        }
    }
};

//最短路径Dijkstra算法的prioUpdater
template <typename Tv, typename Te> struct DijkPU{
    virtual void operator()(Graph<Tv, Tv>* G, int uk, int v){
        if(G->status(v) == UNDISCOVERED){
            if(G->priority(v) > G->priority(uk) + G->weight(uk, v))
                G->priority(v) = G->priority(uk) + G->weight(uk, v);
                G->parent(v) = uk;
        }
    }
};