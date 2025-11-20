#include "../04_BinTree/BinTree.hpp"
//BST 模版类定义
template <typename T> class BST: public BinTree{
protected:
	BinNodePosi(T) _hot;//命中节点的父亲 
	BinNodePosi(T) connect34(BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
	BinNodePosi(T) rotateAt(BinNodePosi(T) x);
public:
	virtual BinNodePosi(T) &search (const T& e);
	virtual BinNodePosi(T) insert (const T& e);
	virtual bool remove (const T& e);
};

// ============================================================
// ====================  查找算法 search(e)   ==================
// ============================================================
//接口实现
//查找，返回目标节点的指针引用，或者返回假想命中节点的空节点的指针引用
template <typename T> BinNodePosi(T)& BST<T>::search (const T& e){
	_hot = NULL;//根节点的父节点为NUll
	searchIn(_root, e, _hot);
}
template <typename T> static 
BinNodePosi(T)& searchIn (BinNodePosi(T) & v, const T& e, BinNodePosi(T)& hot){
	if(!v || (v->data == e)) return v; //递归基，找到了或者到达空节点（返回的节点有可能是一个空节点）
	hot = v;//调用之后的hot总是v的父节点
	return searchIn(((v->data < e) ? v->lc : v->rc) , e, hot);//递归
}//这里的_hot不断更新是为了插入算法中使用


// ============================================================
// ====================  插入算法 insert(e)   ==================
// ============================================================
//插入
template <typename T> BinNodePosi(T) BST<T>::insert (const T& e){
	BinNodePosi(T) x = search(e); 
	if(x) return x;
	x = new BinNode<T>(e, _hot);
	++_size;
	updateHeightAbove(x);
	return x;
}

// ============================================================
// ====================  BST 删除算法 remove(e)   ==============
// ============================================================
//----------------------------------
// [1] remove(e)
// [2] 查找到x之后，实施removeAt(x, hot)
//----------------------------------
template <typename T> bool BST<T>::remove (const T& e){
	BinNodePosi(T) x = search(e);
	if(!x) return false;
	removeAt(x, _hot);
	_size --;
	updateHeightAbove(_hot);
	return true;
}
//----------------------------------
// [1] removeAt(x, hot) 
// [2] 最终都是一棵子树代替被删除节点x或者w的位置
//----------------------------------
template <typename T> static BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot){
	BinNodePosi(T) w = x;
	BinNodePosi(T) succ = NULL;
	
	// 三种情况
	if( !HasLChild(*x) )//没有左孩子
		succ = x = x->rc;//那么他的右孩子直接代替它
	
	else if( !HasRChild(*x) )//有左孩子但是没有右孩子
		succ = x = x->lc;//那么他的左孩子直接代替它

	else{//既有左孩子又有右孩子
		w = w->succ();//将w设置为带删除节点的后继.w不可能有lc. 待删除的节点顺利转移到w，此时 $w \neq x$.
		swap(x->data, w->data);//交换x和x后继的数据，待删除的数据转移到待删除的节点
		BinNodePosi(T) u = w->parent; //待删除节点的父节点u
		//更新u与w的父子关系
		((u == x ) ? u->rc : u->lc) = succ = w->rc; //判断被删除的节点是左孩子还是右孩子
		//u等于x，意味着x的后继是u(x)的rc；u不等于x，意味着x的后继是u的lc
	}

	hot = w->parent;//待删除节点的父亲（要么是无左右孩子的节点x的父亲，要么是x的后继w的父亲）
	if(succ) 
		succ->parent = hot;//如果x有后继，那么更新后继的父亲为hot
	release( w->data );
	release(w);
	return succ;
}


// ============================================================
// =============  旋转调整 connect34 单旋操作   ==================
// ============================================================

//----------------------------------
// [1] connect34(a,b,c,T0,T1,T2,T3)
// [2] 使用情况：00和11——p父节点调整为根节点，01和10——v孩子节点调整为根节点
// [3] 00和11——单旋操作。与splay双层调整不一样
// [4] 01和10——双旋操作。与splay双层调整一样
//----------------------------------
template <typename T> BinNodePosi(T) BST<T>::connect34
(BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c, 
BinNodePosi(T) T0, BinNodePosi(T) T1 , BinNodePosi(T) T2, BinNodePosi(T) T3){
    a->lc = T0; if(T0) T0->parent = a;
    a->rc = T1; if(T1) T1->parent = a; 
    updateHeight(a);
    c->lc = T2; if(T0) T2->parent = c;
    c->rc = T3; if(T1) T3->parent = c; 
    updateHeight(c);
    b->lc = a; a->parent = b;
    b->rc = c; c->parent = b;
    updateHeight(b);
    return b;
}

//----------------------------------
// [1] rotateAt(x)
// [2] 注意:参数v三代中最底层的节点
//----------------------------------
template <typename T> BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v){
    BinNodePosi(T) p = v->parent;
    BinNodePosi(T) g = p->parent;
	//0x
    if ( IsLChild(*p) ){
		//00
        if( IsLChild(*v) ){
            p->parent  = g->parent;
            return connect34(v, p ,g , v->lc, v->rc, p->rc, g->rc);
        }
		//01
        else{
            v->parent = g->parent;
            return connect34(p, v ,g , p->lc, v->lc, v->rc, g->rc);
        }
    }
	//1x
    else{
		//11
        if( IsRChild(*v) ){
            p->parent  = g->parent;
            return connect34(g, p ,v , g->lc, p->lc, v->lc, v->rc, );
        }
		//10
        else{
            v->parent = g->parent;
            return connect34(p, v ,g , g->lc, v->lc, v->rc, p->rc);
        }
    }
}