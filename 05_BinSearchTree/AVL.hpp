#include "BST.hpp"
#define Balanced(x) ( stature((x).lc) == stature((x).rc ) )
#define BalFac(x) ( stature(x).lc - stature(x).rc )
#define AvlBalanced ( (-2< BalFac(x)) && (BalFac(x) < 2) )
#define tallerChild(x) (\
	stature ( (x)->lc ) >  stature ( (x)->rc ) ? (x)->lc : (\
        stature ( (x)->lc ) <  stature ( (x)->rc ) ? (x)->rc : (\
            IsLChild(*(x)) ? (x)->lc : (x)->rc \
        )\
    ) \
)

template <typename T> class AVL : public BST<T> {
public:
    BinNodePosi(T) insert (const T& e);
    bool remove (const T& e);
};

// ============================================================
// ===================  插入算法 insert(e)  =====================
// ============================================================
template <typename T> BinNodePosi(T) AVL<T>::insert(const T& e){
    //首先查找:目标指针要么命中，要么指向假想的命中节点NULL
	BinNodePosi(T) &x = search(e);//指针引用，方便修改指针的指向
	if (x) return;//如果存在直接返回
    //新建好节点
	BinNodePosi(T) xx = x = new BinNode<T>(e, _hot); _size++;

    //从x的父节点开始，逐层向上检查是否失衡
    // 注意:父节点不可能失衡，因为插入节点只会增加高度1
	for(BinNodePosi(T) g = _hot; g; g = g->parent){
		if( !AvlBalanced(*g) ){
            FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
            break;//一次调整就复原了AVL树的平衡性
            //这个节点g一定是平衡因子=|2|,因此在调整完成之后它的平衡因子恢复
            //并且它的高度不会发生任何变化，这不会给上层任何祖父节点带来平衡因子的失衡
        }
        else{
            updateHeight(g);
        }
	}
    return xx;
} 
// ============================================================
// ===================  删除算法 remove(e)  =====================
// ============================================================
template <typename T> bool AVL<T>::remove(const T& e){
    //首先查找:目标指针要么命中，要么指向假想的命中节点NULL
    BinNodePosi(T) &x = search(e);//指针引用，方便修改指针的指向
	if (!x) return false;
    //删除节点
    removeAt(e, _hot);
    _size--;
    for(BinNodePosi(T) g = _hot; g; g = g->parent){
		if( !AvlBalanced(*g) ){
            g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
            //这里可能回一直失衡，因为子树的高度可能变小了，这会一直向上传播
        }
        updateHeight(g);
	}
    return true;
}

