#pragma once

#define BinNodePosi(T) BinNode<T>*

#if defined (RedBlack)
	#define stature(p) ((p)? (p->height) : 0)
#else
	#define stature(p) ((p)? (p->height) : -1)
#endif

typedef enum {RB_RED, RB_BLACK} RBColor;
#define IsRoot(x) (!((x).parent))//x是节点不是指针
#define IsLChild(x) ( !IsRoot(x) && (&(x) == (x).parent->lc)) //&(x)取x的地址
#define IsRChild(x) ( !IsRoot(x) && (&(x) == (x).parent->rc)) //&(x)取x的地址
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define Isleaf(x) (!HasChild(x))
#define sibling(p) \
	(IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
#define uncle(x) \
	(IsLChild(*(x.parent)) ? (x).parent->parent->rc : (x).parent->parent->lc) 
#define FromParentTo(x) \
	(IsRoot(x)? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))
#define IsBlack(x) ((x)->color == RB_BLACK)
#define IsRed(x) ((x)->color == RB_RED)
#define uncle(x) \
	(IsLChild(*(x.parent)) ? (x).parent->parent->rc : (x).parent->parent->lc)

template <typename T> class BinTree;

//BinNode模版类定义
template <typename T> struct BinNode{
//内部成员变量
	T data;
	BinNodePosi(T) parent;
	BinNodePosi(T) lc;
	BinNodePosi(T) rc;
	int height;//高度
	int npl;// 空节点通路长度null path length.左式堆
	RBColor color;
//构造函数
	BinNode():
		parent(NULL),lc(NULL),rc(NULL),height(0),npl(1),color(RB_RED){ }
	BinNode(T e, BinNodePosi(T) p= NULL, 
		BinNodePosi(T) lc= NULL, BinNodePosi(T) rc= NULL, 
		int h = 0, int npl = 1, RBColor c = RB_RED):
		data(e), parent(p),lc(lc),rc(rc),height(h),npl(npl),color(c){ }
//接口
	int size();//当前节点的后代总数，这个节点作为根的子树的规模。
	BinNodePosi(T) insertAsLC(T const& e);//作为当前节点的左孩子插入
	BinNodePosi(T) insertAsRC(T const& e);//作为当前节点的左孩子插入
	BinNodePosi(T) attachLc(BinTree<T>* &S);//将T作为当前节点的左子树接入
	BinNodePosi(T) attachRc(BinTree<T>* &S);//将T作为当前节点的右子树接入

	BinNodePosi(T) succ();//取当前节点的直接后继
	template <typename VST> void travLevel (VST&);
	template <typename VST> void travPre (VST&);
	template <typename VST> void travIn (VST&);
	template <typename VST> void travPost (VST&);
	bool operator< (BinNode const& bn){ return data < bn.data;}//两个节点的数据进行表示抽象成两个节点进行比较
	bool operator== (BinNode const& bn) {return data == bn.data;}//两个节点的数据进行表示抽象成两个节点进行比较
};


//接口实现
template <typename T> int BinNode<T>::size(){
	int s = 1;
	if(lc) s += lc->size();
	if(rc) s += rc->size();
	return s;
}

// ============================================================
// ===============  层序遍历  ===============
// ============================================================
template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC(T const&e){
	return lc = new BinNode(e, this);
}
template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC(T const&e){
	return rc = new BinNode(e, this);
}
// ============================================================
// ===============  层序遍历  ===============
// ============================================================ 
//将T作为当前节点的左子树接入
template <typename T>
BinNode<T>* BinNode<T>::attachLc(BinTree<T>* &S){
	if(this->lc = S->_root) this->lc->parent = this;//将T的根节点接入当前节点的左孩子，明确父子关系
	S->root = NULL;//指向子树根节点的指针置空
	S->_size = 0;//子树规模置0
	release(S);//释放 BinTree<T> 这个对象本身（注意不是释放它里面的节点，因为节点已经并到主树里去了）。
	S = NULL;
	return this->lc;//返回接入的左子树根节点位置
}
//将T作为当前节点的右子树接入
template <typename T>
BinNode<T>* BinNode<T>::attachRc(BinTree<T>* &S){
	if(this->rc = S->_root) this->rc->parent = this;//将T的根节点接入当前节点的右孩子，明确父子关系
	S->root = NULL;//指向子树根节点的指针置空
	S->_size = 0;//子树规模置0
	release(S);//释放 BinTree<T> 这个对象本身（注意不是释放它里面的节点，因为节点已经并到主树里去了）。
	S = NULL;
	return this->rc;//返回接入的右子树根节点位置
}


template <typename T> template <typename VST> void BinNode<T>::travIn (VST& visit){
	switch( rand() % 5 ){
		case 1: travIn_I1(this, visit); break;//迭代版#1
		case 2: travIn_I2(this, visit); break;//迭代版#2
		case 3: travIn_I3(this, visit); break;//迭代版#3
		case 4: travIn_I4(this, visit); break;//迭代版#4
		default: travIn_R(this, visit); break;//递归版
	}
}
template <typename T> template <typename VST> void BinNode<T>::travLevel(VST& visit){
	BinNodePosi(T) x = this;
	Queue<BinNodePosi(T)> Q;
	Q.enqueue(x);
	while(!Q.empty()){
		x = Q.dequeue();
		visit(x->data);
		if(HasLChild(*x)) Q.enqueue(x->lc);
		if(HasRChild(*x)) Q.enqueue(x->rc);
	}
}