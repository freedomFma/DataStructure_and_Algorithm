#include "./Quadlistnode.hpp"
template <typename T> struct Quadlist{
	Rank _size;
	QNodePosi<T> head, tail;
	void init();
	int clear();
	Quadlist() { init(); }
	~Quadlist() { clear(); delete head; delete tail; }
	T remove( QNodePosi<T> p );
	QNodePosi<T> insert( T const& e, QNodePosi<T> p, QNodePosi<T> b = NULL);
};