#include "./BinNode.hpp"
#include "../03_stack_queue/Stack.hpp"

/** 模版类的定义 **/ 
template <typename T> class BinTree{
protected:
	int _size;
	BinNode<T>* _root;
	virtual int updateHeight(BinNodePosi(T) x);//更新节点x的高度
	void updateHeightAbove (BinNodePosi(T) x);//更新节点x以及其祖先的高度
public:
//构造函数和析构函数
	BinTree() : _size(0),_root (NULL) { }
	~BinTree() {if (0 < _size) remove(_root);}//remove()这个方法是删除掉某个节点作为树根的子树
//只读接口
	int size() const {return _size;}
	bool empty() const {return !_root;}
	BinNodePosi(T) root() const {return _root;}

//可写接口
	BinNodePosi(T) insertAsRoot(T const& e);
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);//e作为x的左孩子插入
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);//e作为x的右孩子插入
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &T);//T作为x左子树插入
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &T);//T作为x右子树插入
	int remove(BinNodePosi(T) x);//删除以位置x处节点为根的子树，返回该子树原先的规模
	BinTree<T>* secade (BinNodePosi(T) x);//将子树x从当前树中摘除，并将其转换成为一棵独立的子树
//遍历
	template <typename VST> void travLevel(VST& visit);
	template <typename VST> void travPre(VST& visit);
	template <typename VST> void travIn(VST& visit);
	template <typename VST> void travPost(VST& visit);
//比较器
	bool operator<(BinTree<T> const& t){return _root && t._root && lt(_root,t._root);}
	bool operator==(BinTree<T> const& t){return _root && t._root && (_root == t._root);}
};


/** 方法的实现 **/ 
//更新二叉树节点的高度
template <typename T> int BinTree<T>::updateHeight(BinNodePosi(T) x){
	return x->height = 1+max(stature(x->lc),stature(x->rc));
}
//更新二叉树节奇迹所有祖先的高度
template <typename T> void BinTree<T>::updateHeightAbove(BinNodePosi(T) x){
	while(x){
		updateHeight(x);
		x = x->parent;
	}
}
//插入根节点
template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot (T const &e){
	_size = 1;
	return _root = new BinNode<T>(e);
}
//插入左孩子
template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x,T const& e){
	_size ++;
	x->insertAsLC(e);
	updateHeightAove(x);
	return x->lc;
}
//插入右孩子
template <typename T> BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x,T const& e){
	_size ++;
	x->insertAsRC(e);
	updateHeightAove(x);
	return x->rc;
}
//接入左子树
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &T){
	if(x->lc = T->_root) x->lc->parent = x;//将子树接入x左孩子节点，孩子父子关系明确
	_size += T->size();//更新二叉树大小
	updateHeightAbove(x);//更新x祖先高度
	T->_root = NULL;//指向子树根节点的指针置空
	T->_size = 0;//子树规模置0
	release(T);//释放 BinTree<T> 这个对象本身（注意不是释放它里面的节点，因为节点已经并到主树里去了）。
	T = NULL;//释放后，把指针设为 NULL，防止成为“悬空指针”（dangling pointer）。
	return x;
}
//接入右子树，与左子树一样是对称的操作
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &T){
	if(x->rc = T->_root) x->rc->parent = x;
	_size += T->size();
	updateHeightAbove(x);
	T->_root = NULL;
	T->_size = 0;
	release(T);
	T = NULL;
	return x;
}




//删除这个节点子树
template <typename T>int BinTree<T>::remove(BinNodePosi(T) x){
	FromParentTo(*x) = NULL;//将这个节点的父母的孩子设置为NULL
	updateHeightAbove(x->parent);//更新自父母节点及其之上的高度
	int n = removeAt(x);
	_size -= n;
	return n;
}
template <typename T> static int removeAt(BinNodePosi(T) x){
	if(!x) return 0;//如果不存在直接返回
	int n = 1+removeAt(x->rc)+removeAt(x->lc);
	release(x->data);
	release(x);
	return n;
}

template <typename T> BinTree<T>* BinTree<T>::secade(BinNodePosi(T) x){
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);//将原先树中x删除掉；
	BinTree<T>* S = new BinTree<T>;
	S->_root = x;
	S->_size = x->size();
	_size -= S->_size;
	return S;
}

// ============================================================
// ===============  层序遍历  ===============
// ============================================================
template <typename T> template <typename VST> 
void BinTree<T>::travLevel(VST& visit){
	BinNodePosi(T) x = _root;
	Queue<BinNodePosi(T)> Q;
	Q.enqueue(x);
	while(!Q.empty()){
		x = Q.dequeue();
		visit(x->data);
		if(HasLChild(*x)) Q.enqueue(x->lc);
		if(HasRChild(*x)) Q.enqueue(x->rc);
	}
}

// ============================================================
// ===============  前序遍历  ===============
// ============================================================
template <typename T> template <typename VST> void BinTree<T>::travPre(VST& visit){
	switch( rand() % 3 ){
		case 1: travPre_R(this, VST& visit); break;
		case 2: travPre_I1(this, VST& visit); break;
		case 3: travPre_I2(this, VST& visit); break;
	}
}
template <typename T, typename VST> 
void travPre_R(BinNodePosi(T) x, VST& visit){
	if(!x) return;
	visit(x->data);
	travPre_R(x->lc, visit);
	travPre_R(x->rc, visit);
}
template <typename T, typename VST> 
void travPre_I1(BinNodePosi(T) x, VST& visit){
	Stack<BinNodePosi(T)> S;
	if (x) S.push(x);
	while(!S.empty()){
		x = S.pop(); 
		visit(x->data);
		if(HasRChild(*x)) S.push(x->rc);
		if(HasLChild(*x)) S.push(x->lc);
	}
}
template <typename T, typename VST> 
void visitAlongVine(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)> S){
	while(x){
		visit(x->data);//访问当前的节点数据
		S.push(x->rc);//将右孩子压入栈中
		x = x->lc;//更新x为x的左孩子.
	}
}
template <typename T, typename VST> 
void travPre_I2(BinNodePosi(T) x, VST& visit){
	Stack<BinNodePosi(T)> S;
	while(x){
		visitAlongVine(x, visit, S);//遍历x的左藤蔓，将右孩子（子树压入栈中）
		if(S.empty()) break;//如果栈为空就终止，遍历完成
		x = S.pop();//x为下一个出栈的右子树
	}
}

// ============================================================
// ===============  中序遍历  ===============
// ============================================================
template <typename T> template <typename VST> void BinTree<T>::travIn(VST& visit){
	switch( rand() % 5 ){
		case 1: travIn_I1(this, visit); break;//迭代版#1
		case 2: travIn_I2(this, visit); break;//迭代版#2
		case 3: travIn_I3(this, visit); break;//迭代版#3
		case 4: travIn_I4(this, visit); break;//迭代版#4
		default: travIn_R(this, visit); break;//递归版
	}
}
template <typename T> template <typename VST> void BinTree<T>::travPost(VST& visit){

}