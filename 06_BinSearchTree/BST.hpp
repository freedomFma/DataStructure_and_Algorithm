#include "C++/DSA/04_BinTree/BinTree.hpp"
//BST 模版类定义
template <typename T> class BST: public BinTree{
protected:
	BinNodePosi(T) _hot;//命中节点的父亲 ❓暂时不太理解为什么要有这个数据
	BinNodePosi(T) connect34(BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
	BinNodePosi(T) rotateAt(BinNodePosi(T) x);
public:
	virtual BinNodePosi(T) &search (const T& e);
	virtual BinNodePosi(T) insert (const T& e);
	virtual bool remove (const T& e);
};

//接口实现
//查找，返回目标节点的指针引用，或者假想命中节点的空节点的指针引用
template <typename T> BinNodePosi(T)& BST<T>::search (const T& e){
	_hot = NULL;
	searchIn(_root, e, _hot);
}
template <typename T> static BinNodePosi(T) &searchIn (BinNodePosi(T) & v, const T& e, BinNodePosi(T) hot){
	if(!v || (v->data == e)) return hot = v;
	hot = v;
	return searchIn(((v->data < e) ? v->lc : v->rc) , e, hot);
}

//插入
template <typename T> BinNodePosi(T) BST<T>::insert (const T& e){
	BinNodePosi(T) x = search(e); 
	if(x) return x;
	x = new BinNode<T>(e, _hot);
	++_size;
	updateHeightAbove(x);
	return x;
}

//删除
template <typename T> bool BST<T>::remove (const T& e){
	BinNodePosi(T) x = search(e);
	if(!x) return false;
	removeAt(x, _hot);
	_size --;
	updateHeightAbove(_hot);
	return true;
}
template <typename T> static BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot){
	BinNodePosi(T) w = x;
	BinNodePosi(T) succ = NULL;
	if( !HasLChild(*x) )
		succ = x = x->rc;//偷天换日，此时x已经被掉包
	else if( !HasRChild(*x) )
		succ = x = x->lc;//偷天换日，此时x已经被掉包
	else{
		w = w->succ();//将w设置为带删除节点的后继.w不可能有lc. 待删除的节点顺利转移到w，此时 $w \neq x$.
		swap(x->data, w->data);//交换x和x后继的数据，待删除的数据转移到待删除的节点
		BinNodePosi(T) u = w->parent; //待删除节点的父节点u
		((u == x ) ? u->rc : u->lc) = succ = w->rc; //判断被删除的节点是左孩子还是右孩子
	}
	hot = w->parent;
	if(succ) 
		succ->parent = hot;
	release( w->data );
	release(w);
	return succ;
}