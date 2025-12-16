#include "Graph.hpp"
// ============================================================
// ================     双连通分量分解算法      ===================
// ============================================================
//基于DFS的双连通分量分解算法
#define hca(x) (fTime(x))
template <typename Tv, typename Te> 
void Graph<Tv, Te>::BCC(int v, int& clock, Stack<int>& S){
	hca(v) = dTime(v) = ++clock;
	status(v) = DISCOVERED;
	S.push(v);
	for(int u = firstNbr(v); -1 < u; u = nextNbr(v, u)){
		switch(status(u)){
			case (UNDISCOVERED):
				type(v, u) = TREE;
				parent(u) = v;
				BCC(u , clock, S);
				if(hca(u) > hca(v)){//v是关节点，连接其后代子孙和其祖先
					while(v != S.pop());//栈中弹出一个连通子图
					S.push(v);//压入v
				}else{
					hca(v) = min(hca(u), hca(v))//更新hca，取其后代hca和自身dTime的最小者
				}
				break;
			case (DISCOVERED):
				type(v, u) = BACKWARD;
				hca(v) = min(hca(u), hca(v));//这里写成dTime(u)是一定的吗？
				break;
			default:
				type(v, u) = (dTime(v) < dTime(u)? FORWARD : CROSS);
				break;
		}
	}
	status(v) = VISITED;
}
#undef hca

template <typename Tv, typename Te> void Graph<Tv, Te>::bcc(int s){
	reset();
	int clock = 0;
	int v = s;
	Stack<int> S;
	do{
		if(status(v) == UNDISCOVERED){
			BCC(v, clock, S);
			S.pop();//专门清除DFS根节点的残留
		}
	}while(s != (v = (++v % n)));
}