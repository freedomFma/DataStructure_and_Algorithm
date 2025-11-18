#include "../05_BinSearchTree/BST.hpp"

template <typename T> class Splay: public BST<T>{
protected:
	BinNodePosi(T) splay (BinNodePosi(T) v);
public:
	BinNodePosi(T)& search(const T& e);//
	BinNodePosi(T) insert (const T& e);
	bool remove (const T& e);
};

//伸展算法，将节点v提升至根节点
template <typename T> BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v){
	if (!v) return NULL;
	BinNodePosi(T) p,g,gg;
	while( (p = v->parent) && (g = p->parent) ){
		BinNodePosi(T) gg = g->parent;
		switch( (IsRChild(p)) <<1 | (IsRChild(v)) ){
		case 0b00://zig(g)-zig(p)
			g->attachLc(p->rc);
			p->attachLc(v->rc);
			p->attachRc(g);
			v->attachRc(p);
			break;
		case 0b01://zag(p)-zig(g)
			p->attachRc(v->lc);
			g->attachLc(v->rc);
			v->attachLc(p);
			v->attachRc(g);
			break;
		case 0b10://zig(p)-zag(g)
			p->attachLc(v->rc);
			g->attachRc(v->lc);
			v->attachLc(g);
			v->attachRc(p);
			break;
		default://0b11 zag(g)-zag(p)
			g->attachLRc(p->lc);
			p->attachRc(v->lc);
			p->attachLc(g);
			v->attachLc(p);
			break;
		}
		if(!gg) v->parent = NULL;
		else(g==gg->lc)? gg->attachLc(v) : gg->attachRc(v);
		//注意，这里只是更新了gpv三个节点的高度，
		//之所以没有对所有的节点进行高度更新是因为随着伸展的过程，v逐步上升至根彼时所有的高度都更新了。
		g->updateHeight();
		p->updateHeight();
		v->updateHeight();
	}
	if(p = v->parent){
		if(IsLChild(v)){
			p->attachLc(v->rc);
			v->attachRc(p);
		}
		else{
			p->attachRc(v->lc);
			v->attachLc(p);
		}
		//更新高度只更新pv两个节点高度原因如上。
		p-updateHeight();
		v->updateHeight();
	}
	v->parent = NULL;
	return v;
}


template <typename T> 
BinNodePosi(T)& Splay<T>::search(const T& e){
	BinNodePosi(T) p = BST<T>::search(e);
	_root = ( p ? (splay(p)) : (_hot? splay(_hot) : NULL));
	return _root;
}

//搜索节点e，若命中则将该节点伸展至根，否则将最后访问的节点伸展至根
template <typename T> 
BinNodePosi(T) Splay<T>::insert(const T& e){
	//如果是空树，e作为根节点插入，完成操作。
	if(!_root){
		_size = 1;
		return _root = new BinNode<T>(e);//直接返回
	}
	
	//插入的主体部分
	BinNodePosi(T) t =search(e);
	//互译元素的插入结果（每个元素只能存在一个）
	if(e == t->data) return t;//直接返回
	if(t->data < e){
		_root = t->parent = new BinNode<T>(e,NULL,t,t->rc);
		t->rc = NULL;
	}
	else{// e < t->data
		_root = t->parent = new BinNode<T>(e, NULL, t->lc, t);
		t->lc = NULL;
	}
	
	//插入结束后的收尾工作，只有if-else的情况还未返回，参与其中
	_size++;
	v->updateHeight();//t->updateHeightAbove();
	return _root;
}

//删除节点e
template <typename T> 
bool Splay<T>::remove(const T& e){
	//确保被删除节点被伸展至根
	if( !_root || e != search(e)->data ) 
		return false;

	//删除节点e的主题操作部分
	BinNodePosi(T) L = _root->lc;
	BinNodePosi(T) R = _root->rc;
	delete _root;
	if(!R){//右子树不存在
		if(L) L->parent = NULL;
		_root = L;
	}
	else{//右子树存在，优先让右子树中最小值当根（也就是大于目标元素的最小值）
		_root = R; R->parent = NULL;
		search(e);
		_root->attachLc(L);
	}

	//收尾工作
	_size --;
	if(_root) _root->updateHeight();
	return true;
}