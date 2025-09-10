#include "C++/DSA/04_BinTree/BinNode.hpp"

/** 模版类的定义 **/ 
template <typename T> class BinTree{
protected:
	int _size;
	BinNodePosi(T) _root;
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
	template <typename VST> void travLevel(VST& visit) {if (_root) _root->travLevel(visit);}
	template <typename VST> void travPre(VST& visit) {if (_root) _root->travPrel(visit);}
	template <typename VST> void travIn(VST& visit) {if (_root) _root->travIn(visit);}
	template <typename VST> void travPost(VST& visit) {if (_root) _root->travPost(visit);}
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
template <typename T>BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &T){
	if(x->lc = T->_root) x->lc->parent = x;//将子树接入x左孩子节点，孩子父子关系明确
	_size += T->size();//更新二叉树大小
	updateHeightAbove(x);//更新x祖先高度
	T->_root = NULL;
	T->_size = 0;
	release(T);//释放 BinTree<T> 这个对象本身（注意不是释放它里面的节点，因为节点已经并到主树里去了）。
	T = NULL;//释放后，把指针设为 NULL，防止成为“悬空指针”（dangling pointer）。
	//👉 相当于告诉程序：“这棵树已经不存在了，别再用这个指针访问它了。”
	return x;
}
//接入右子树
template <typename T>BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &T){
	if(x->rc = T->_root) x->rc->parent = x;
	_size += T->size();
	updateHeightAbove(x);
	T->_root = NULL;
	T->_size = 0;
	release(T);
	T = NULL;
	return x;
}
// template <typename T>int BinTree<T>::remove(BinNodePosi(T) x){
// 	if(!x) return 0;
// 	if(!IsRoot(x)){
// 		if(IsLChild(x)){
// 			x->parent->lc = NULL;
// 			_size -= x->height;//不知道，需要遍历才知道。❗️🙅
// 			updateHeightAbove(x);
// 			release(x);
// 			x = NULL;
// 		}
// 		if(IsRChild(x)){
// 			x->parent->rc = NULL;
// 			_size -= x->height;//不知道，需要遍历才知道。❗️🙅
// 			updateHeightAbove(x);
// 			release(x);
// 			x = NULL;
// 		}

// 	}
// 	else{
// 		_root = NULL;
// 		_size = 0;
// 	} 
// }

template <typename T>int BinTree<T>::remove(BinNodePosi(T) x){
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	int n = removeAt(x);
	_size -= n;
	return n;
}
template <typename T> static int removeAt(BinNodePosi(T) x){
	if(!x) return 0;
	int n = 1+removeAt(x->rc)+removeAt(x->lc);
	release(x->data);
	release(x);
	return n;
}