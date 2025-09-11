#include "../06_BinSearchTree/BST.hpp"

template <typename T> class Splay: public BST<T>{
protected:
	BinNodePosi(T) splay (BinNodePosi(T) v);
public:
	BinNodePosi(T)& search(const T& e);
	BinNodePosi(T) inset (const T& e);
	bool remove (const T& e);
};

