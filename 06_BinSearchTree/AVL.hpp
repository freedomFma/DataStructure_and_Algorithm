#include "./BST.hpp"
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

template <typename T> class AVL : public BST<T>> {
public:
    BinNodePosi(T) insert (const T& e);
    bool remove (const T& e);
};