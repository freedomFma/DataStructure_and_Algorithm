#include "Queue.hpp"
#include "Vector.hpp"
#include "Vertex_Edge.hpp"
#include <climits>

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
	virtual int insert(Tv const&) = 0;//纯虚函数，必须由子类提供实现。这样的类叫做抽象类。
	//抽象类不能直接实例化，只能作为基类使用。//插入顶点，返回*编号*
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