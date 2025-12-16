#include "Graph.hpp"
// ============================================================
// ================   基于DFS的拓扑排序算法    ===================
// ============================================================
//
//拓扑排序：零出度算法
template <typename Tv, typename Te>
bool Graph<Tv, Te>::TSort(int v, int& clock, Stack<Tv>* S){
	status(v) = DISCOVERED;
	dTime(v) = ++clock;
	for(int u = firstNbr(v); -1 < u; u = next(v, u)){//深度优先的逻辑
		switch(status(u)){
			case UNDISCOVERED:
				parent(u) = v;
				type(v, u) = TREE;
				if( !TSort(u, clock, S) )
					return false;
				break;
			case DISCOVERED:
				type(v, u) = BACKWARD;
				return false; 
			default://VISITED
				type(v, u) = (dTime(v) < dTime(u)? FORWARD : CROSS;)
				break; 
		}
	}
	status(v) = VISITED;//访问结束的节点标记为visited，入栈。（是拓扑排序的最后一个）
	S->push(vertex(v));
	return true;
}


template <typename Tv, typename Te> Stack<Tv>* Graph<Tv, Te>::tSort(int s){
	reset();
	int clock = 0;
	int v = s;
	Stack<Tv>* S = new Stack<Tv>;
	do{
		if(status(v) == DISCOVERED){
			if( !TSort(v, clock, S) ){
				while(!S->empty())
					S->pop();
				break;
			}
		}
	}
	while(s!=(v = (++v % n)));
	return S;
}