typedef enum{UNDISCOVERED, DISCOVERED, VISITED} VStatue;//顶点状态
typedef enum{UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD} EType;//边的状态
//enum 是 枚举类型（enumeration）的关键字
//花括号 {} 里面写的是 枚举常量，它们会被自动映射为整数值（从 0 开始，逐个递增）

template<typename Tv> struct Vertex{
	Tv data;
	int inDegree,outDegree;//入度和出度
	VStatus status;//顶点状态
	int dTime,fTime;//时间标签：发现时间（discovered）和完成时间（visited）
	int parent;//父母节点
	int priority;//优先级
	Vertex(Tv const& d = (Tv) 0):
		data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), 
        dTime(-1), fTime(-1), parent(-1), priority(INT_MAX){ }//
		//INT_MAX是<climits>中的一个常量。
};
template<typename Te> struct Edge{
	Te data;//数据的写法 Te edge(v, u);
	int weight;//权重
	Etype type;//边的类型
	Edge(Te const& d, int w):
		data(d), weight(w), type(UNDETERMINED) { }
};