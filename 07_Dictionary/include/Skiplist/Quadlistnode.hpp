template <typename T> struct QNode;
template <typename T> using QNodePosi = QNode<T>*;

//QNode节点:自身的词条数据、前驱、后继、上邻、下邻指针
template <typename T> struct QNode{
	T entry;
	QNodePosi<T> pred , succ, above, below;
	
	QNode(T e = T(), QNodePosi<T> p = NULL, QNodePosi<T> s = NULL, 
        QNodePosi<T> a = NULL, QNodePosi<T> b = NULL): 
        entry(e), pred(p), succ(s), above(a), below(b) { }
	QNodePosi<T> insert(T const& e, QNodePosi<T> b = NULL);
};

