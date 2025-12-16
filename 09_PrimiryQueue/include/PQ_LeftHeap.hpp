#include "BinTree.hpp"
#include "PQ.hpp"

template <typename T> class PQ_LeftHeap:public PQ<T>, public BinTree<T>{
public:
	T& getMax(){return _root>data;}
	void insert(T);
	T delMax();//基于合并操作实现
	
	PQ_LeftHeap( PQ_LeftHeap &A, PQ_LeftHeap &B){
		_root = merge(A._root, B._root);
		_size = A._size + B._size;
		A._root = B._root = NULL;
		A._size = B._size = 0;
	}
};

// ============================================================
// ====================      合并算法        ===================
// 保证了时间复杂度为log n
// ============================================================ 

template <typename T> 
BinNodePosi(T) merge(BinNodePosi(T) a, BinNodePosi(T) b){
	if(!a) return b; if(!b) return a;
	if (*a < *b) swap(a, b);
	
	//确保了左堆的节点数据比右堆的节点数据要大，右堆可以成为左堆的孩子
	( a->rc = merge(a->rc, b) )->parent = a;
	
    //注意现在的a是右链中不再需要往下调整的那个节点，要么a的右孩子接替了a的右孩子、要么b接替了a的右孩子
    //在递归中一层一层往上调整
	if( !a->lc || (a->lc->npl < a->rc->npl))//
		swap(a->lc, a->rc);
	a->npl =  (a->rc ? 1+a->rc->npl : 1);
	
	return a;
}

template <typename T>
BinNodePosi(T) merge (BinNodePosi(T) a, BinNodePosi(T) b){
	if(!a) return b; if(!b) return a;
	if(*a < *b) swap(a, b);
	
	for( ; a->rc ; a = a->rc){ //迭代到b完全归入a，此时的a的右侧链条最后一个节点成为b的父亲
		if( *(a->rc) < *b ){
			b->parent = a; 
			swap(a->rc, b);
		}
	}
	(a->rc = b)->parent = a;// 更新接入树的父子关系
	
	for(; a; b = a, a=a->parent){//从下往上不断调整左式堆的结构
		if( !a->lc || (a->lc->npl < a->rc->npl) )
			swap(a->lc, a->rc);
		a->npl = (a->rc ? 1+a->rc->npl : 1);
	}
	return b;
}

template <typename T> 
T PQ_LeftHeap<T>::delMax(){
	BinNodePosi(T) lHeap = _root->lc; if(lheap) lheap->parent = NULL;
	BinNodePosi(T) rHeap = _root->rc; if(rheap) rheap->parent = NULL;
	
	T e = _root->data;
	delete _root;
	_size--;
	
	_root = merge(lHeap, rHeap);
	return e;
}