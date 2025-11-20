#include "../05_BinSearchTree/BST.hpp"
#define BlackHeightUpdtaed(x) ( stature(x->lc) == stature(x->rc) )
//如果节点的左右孩子的黑高度都没有发生变化，那么意味着这个节点的黑高度也没有发生变化

template <typename T> class RedBlack: public BST<T>{
public:
	BinNodePosi(T) insert (const T& e);
	bool remove(const T& e);
protected:
	void solveDoubleRed(BinNodePosi(T) x);
	void solveDoubleBlack (BinNodePosi(T) x);
	int updateHeight(BinNodePosi(T)x);
};

// ============================================================
// =======================  更新黑高度  =========================
// ============================================================
template <typename T> int RedBlack<T>::updateHeight
(BinNodePosi(T) x){
	x->height = max( stature(x->lc), stature(x->rc) );
	if( IsBlack(x) ) x->height++;
	return x->height;
}


// ============================================================
// ==================  红黑树的插入操作&双红修正  =================
// ============================================================

//----------------------------------
// insert(e) 插入算法
//----------------------------------
template <typename T> 
BinNodePosi(T) RedBlack<T>::insert(const T& e){
	BinNodePosi(T) &x = search(e);
	if(x) return x;
	
	x = new BinNode<T> (e, _hot, NULL, NULL, -1);//创建的红色节点的黑高度是-1
	_size++;
	
	BinNodePosi(T) xOld = x;
	solveDoubleRed(x) ; 
	return xOld;
}
//----------------------------------
// solveDouble(x) 双红修正
// RR-1 叔叔节点为黑色，3+4调整（O(1)调整好）
// RR-2 叔叔节点为红色，染色调整（可能会向上传递）
//----------------------------------
template <typename T> void RedBlack<T>::solveDoubleRed(BinNodePosi(T) x){
	while(1){//内部会使用return语句退出
		//---------------------------------------------
        //插入的节点本身是根节点，那么它的颜色为黑色
		if(IsRoot(x)){
			x->color = RB_BLACK;
			x->height++;
			return ;//退出
		}
		//---------------------------------------------
        //插入节点的父节点为黑色，符合红黑树定义，无需修正
		BinNodePosi(T) p = x->parent;
		if(IsBlack(p)) return;//退出
        //新插入节点的父节点本身就是黑色，此时符合红黑树定义，没有双红修正的需求

		//---------------------------------------------
		//当插入节点的父节点为红色，视父节点的兄弟u（也就是x的叔叔）而分为两种双红修正
		BinNodePosi(T) g = p->parent;
		BinNodePosi(T) u = uncle(x);
        //----------------------------------
		//RR-1 叔叔节点为黑色，主需要3+4调整
		if( IsBlack(u) ){
			//染色调整
			// if( IsLChild(*x) == IsLChild(*p) ) p->color = RB_BLACK;
			// else x->color = RB_BLACK;
            (( IsLChild(*x) == IsLChild(*p) )? p : x)->color = RB_BLACK;
			g->color = RB_RED;
			//旋转结构调整
			BinNodePosi(T) gg = g->parent;
			BinNodePosi(T) b = FromParentTo(g) = rotateAt(x);
			b->parent = gg;
            return ;//退出
		}
        //----------------------------------
		//RR-2 叔叔节点为红色，只需要染色操作 无需旋转
        //但是可能会造成双红的不断向上传递，需要递归处理
		else{
			//染色调整又可能导致双红不断向上传播
			p->color = u->color = RB_BLACK;p->height++;
			g->color = RB_RED;g->height++;
			// if(!IsRoot(*g)) g->color = RB_RED; // 这里无需判断是否为根节点，因为根节点在下一次循环中会被处理
            g->color = RB_RED;
			x = g; //继续向上检查是否双红
		}
	}
}



// ============================================================
// ==================  红黑树的删除操作&双黑修正  =================
// ============================================================

//----------------------------------
// remove(e) 删除算法
//----------------------------------
template <typename T> bool RedBlack<T>::remove(const T& e){
	BinNodePosi(T) &x = search(e);
	if( !x ) return false;//待删除的节点不存在，失败
	
	BinNodePosi(T) r = removeAt(x, _hot);//r是删除后的接续节点
	//删除之后是空树，成功
	if( !(--_size) ) return true;//删除之后是空树，可以直接返回
	//删除的是根节点，接续者的颜色无论红黑都可以直接染黑
	if( !_hot ){ //删除的是根节点
		_root->color = RB_BLACK;
		_root->updateHeight();
		return true;
	}
	//删除的是红色节点，黑高度没有任何变化，成功
	if( BlackHeightUpdtaed(_hot) ) return true;
	//删除的是黑色节点，但是后继是红色节点，直接把后继染黑就成功
	if( IsRed(r) ){
		r->color = RB_BLACK;
		r->height++;
		return true;
	}
	//此时删除的是黑色节点，后继也是黑色节点，因此子树的黑高度-1，需要解决双黑修正
	solveDoubleBlack(r);
	return true;
}


//----------------------------------
// 双黑修正
// [1] BB-1 兄弟节点含有一个红色的孩子，3+4调整+重染色
// [2] BB-2R 兄弟节点为黑色且父节点为红色，染色调整
// [3] BB-2B 兄弟节点为黑色且父节点为黑色，染色调整（可能会向上传递）
// [4] BB-3 兄弟节点为红色，旋转调整+重染色
//----------------------------------
template <typename T> void RedBlack<T>::solveDoubleBlack(BinNodePosi(T) r){
    while(1){//内部会使用return语句退出}
        BinNodePosi(T) p = r ? r->parent : _hot ; //r的父亲
        if(!p) return ;//待删除的是根节点，而且这个根节点也没有后继，就是单蹦个根节点杵在那，删了就删了
        //但是这种情况已经在删除节点中被明确过实现了
        
        BinNodePosi(T) s = ( r == p->lc)? p->rc : p->lc;//r的兄弟节点
        
        //兄弟节点为黑色的情况，包含BB-1，BB-2R，BB-2B
        if ( IsBlack(s) ){
            //-------------------------
            //BB-1 如果兄弟节点含有一个红色的孩子
            BinNodePosi(T) t = IsRed(s->lc)? s->lc : (IsRed(s->rc) ? s->rc :NULL);
            //3+4调整+重染色，一定完成
            if(t){
                //3+4调整
                RB_Color oldP = p->color; 
                BinNodePosi(T) b = rotateAt(t);
                //重染色
                if(HasLChild(b)){
                    b->lc->color = RB_BLACK; 
                    b->lc->updateHeight();
                }
                if(HasRChild(b)){
                    b->rc->color = RB_BLACK; 
                    b->rc->updateHeight();
                }
                b->color = oldP; b->updateHeight();
                return; //双黑修正就此完成
            }
            //-------------------------
            //BB-2R,BB-2B都仅仅只需要染色就可以
            else{
                s->color = RB_RED; s->height--;//兄弟节点无论哪种情况都需要染红
                //BB-2R父节点为红色，把父节点染黑
                if(IsRed(p)){
                    p->color = RB_BLACK;
                    return;//修复完成
                }
                //BB-2B全黑色，把兄弟染红，整个子树黑高度-1
                else{
                    p->height--;
                    r = p;
                }
            }
        }
        //兄弟节点为红色的情况，BB-3
        else{
            p->color = RB_RED;
            s->color = RB_BLACK;
            BinNodePosi(T) t = IsLChild(s) ? s->lc : s->rc;//这里一定能够保证s的两侧都有黑孩子！！因为r子树黑高度至少为1，p为红色，因此它的两个孩子一定都是黑孩
            _hot = p;//前面的删除算法调用中_hot 已经定位为x的父亲（也就是r的父亲）
            rotateAt(t);
        }
    }
}