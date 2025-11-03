template <typename T> struct QNode;
template <typename T> using QNodePosi = QNode<T>*;
template <typename T> struct QNode{
	T entry;
	QNodePosi<T> pred , succ, above, below;
	QNode(T e = T(), QNodePosi<T> p = NULL, QNodePosi<T> s = NULL, 
        QNodePosi<T> a = NULL, QNodePosi<T> b = NULL): 
        entry(e), pred(p), succ(s), above(a), below(b) { }
	QNodePosi<T> insert(T const& e, QNodePosi<T> b = NULL);
};

