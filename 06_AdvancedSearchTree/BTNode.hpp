#include "../01_vector/Vector.hpp"
template <typename T> struct BTNode;  // 前向声明
template <typename T> using BTNodePosi = BTNode<T>*;

template <typename T> struct BTNode{
	BTNodePosi<T> parent;
	Vector<T> key;
	Vector< BTNodePosi<T> > child;
	
	BTNode(){parent = NULL; child.insert(NULL)}
	BTNode(T e, BTNodePosi<T> lc = NULL, BTNodePosi<T> rc = NULL){
		parent = NULL;
		key.insert(e);
		child.insert(lc); 
		if(lc) lc->parent = this;
		child.insert(rc); 
		if(rc) rc->parent = this;
	}
};