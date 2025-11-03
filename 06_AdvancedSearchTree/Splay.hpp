#include "../05_BinSearchTree/BST.hpp"

template <typename T> class Splay: public BST<T>{
protected:
	BinNodePosi(T) splay (BinNodePosi(T) v);
public:
	BinNodePosi(T)& search(const T& e);
	BinNodePosi(T) inset (const T& e);
	bool remove (const T& e);
};

//伸展算法，将节点v提升至根节点
template <typename T> BinNodePosi(T) Splay<T>::splay (BinNodePosi(T) v){
	if(!v) return NULL;
	BinNodePosi(T) p; BinNodePosi(T) g;
	while()
}