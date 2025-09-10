#include "C++/DSA/03_stack_queue/Queue.hpp"
#include "C++/DSA/01_vector/Vector.hpp"
#include <climits>

typedef enum{UNDISCOVERED, DISCOVERED, VISITED} VStatue;
typedef enum{UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD} EType;
//enum 是 枚举类型（enumeration）的关键字
//花括号 {} 里面写的是 枚举常量，它们会被自动映射为整数值（从 0 开始，逐个递增）


template <typename Tv, typename Te> class Graph{
private:
	void reset(){
		for(int i = 0; i < n; i++){
			statue(i) = UNDISCOVERED;
			fTime(i) = fTime(i) = -1;
			parent(i) = -1;
			priority(i) = INT_MAX;//常数climits库中的最大常数
			for(int j = 0; j<n;j++){
				if(exist(i,j)) type(i,j) = UNDETERMINED;
			}
		}
	}
	void BFS(int, int&);//广度优先搜索算法
	void DFS(int, int&);//深度优先搜索算法
	void DFS_I(int, int&);//深度优先算法的迭代版本
	void BCC(int, int&, Stack<int>&);//基于DFS的双连通分量分解算法
	bool TSort(int, int&, Stack<Tv>*);//基于DFS的拓扑排序算法
	template <typename PU> void PFS(int, PU);//优先级搜索
	
public:
//顶点 
	int n;
	virtual int insert(Tv const&) = 0;//纯虚函数，必须由子类提供实现。这样的类叫做抽象类。抽象类不能直接实例化，只能作为基类使用。//插入顶点，返回*编号*
	virtual Tv remove(int) = 0;//删除顶点及其关联边，返回该顶点的信心
	virtual Tv& vertex(int) = 0;//顶点v的数据（该顶点的确存在）
	virtual int inDegree(int) = 0;
	virtual int outDegree(int) = 0;
	virtual int firstNbr(int) = 0;//顶点v的首个邻接顶点
	virtual int nextNbr(int, int) = 0;//顶点v的（相对于顶点j的）下一个邻接顶点
	virtual VStatue* status(int) = 0;//顶点v的状态
	virtual int& dTime(int) = 0;
	virtual int& fTime(int) = 0;
	virtual int& parent(int) = 0;
	virtual int& priority(int) = 0;
//边
	int e;
	virtual bool exists(int, int) = 0;
	virtual void insert(Te const&, int ,int, int) = 0;
	virtual Te remove(int, int) = 0;
	virtual EType& type(int, int) = 0;
	virtual Te& edge(int, int) = 0;
	virtual int& weight(int, int) = 0;
//算法
	void bfs(int);
	void dfs(int);
	void bcc(int);
	Stack<Tv>* tSort (int);
	void prim (int);
	void dijkstra(int);
	template<typename PU> void pfs(int, PU);
};

//广度优先搜索算法 BFS
template <typename Tv, typename Te> void Graph<Tv, Te>::BFS(int v, int& clock){//先遍历到的顶点，先访问其邻接顶点
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
			else{
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

//深度优先搜索算法：DFS的递归版本
template <typename Tv, typename Te> void Graph<Tv, Te>::DFS(int v, int& clock){//后遍历到的顶点，先访问其邻接顶点
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
			default://status(u) == VISITED
				type(v, u) = (dTime(v) > dTime(u) ? FORWARD : CROSS);
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
	while(s != (v = (v++ % n)));
}

//拓扑排序：零出度算法
template <typename Tv, typename Te>
bool Graph<Tv, Te>::TSort(int v, int& clock, Stack<Tv>* S){
	status(v) = DISCOVERED;
	dTime(v) = ++clock;
	for(int u = firstNbr(v); -1<u; u = next(v, u)){
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
			default:
				type(v, u) = (dTime(v) < dTime(u)? FORWARD : CROSS;)
				break;
		}
	}
	status(v) = VISITED;
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
#endef hca
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

//优先级搜索
template <typename Tv, typename Te> template <typename PU> 
void Graph<Tv, Te>::PFS(int v, PU prioUpdater){
	priority(s) = 0;
	status(s) = VISITED;
	parent(s) = -1;
	while(1){
		for(int w = firstNbr(s); -1< w; w = nextNbr(s, w))//
			prioUpdater(this, s, w);
		for(int shortest = INT_MAX, w = 0; w < n; w++){
			if(status(w) == UNDISCOERED)
				if(shortest > priority(w)){
					shortest = priority(w);
					s = w;
				}
		}
		if (status(s) == VISITED) break;
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

