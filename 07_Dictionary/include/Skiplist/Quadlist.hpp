#include "./Quadlistnode.hpp"

//将QNode组织成一长条双向链表
template <typename T> struct Quadlist{
private:
	Rank _size;
	QNodePosi<T> head, tail;

protected:
	void init();
	int clear();

public:
	//构造函数与析构函数
	Quadlist() { init(); }
	~Quadlist() { clear(); delete head; delete tail; }
	//只读接口
	Rank size() const { return _size; }
	bool empty() const { return _size <= 0; }
	QNodePosi<T> first() const { return head->succ; }
	QNodePosi<T> last() const { return tail->pred; }
	bool valid(QNodePosi<T> p) { return p && (tail != p) && (head != p); }
	//可写接口
	T remove( QNodePosi<T> p );
	QNodePosi<T> //插入：将e作为p的后继、b的上邻插入
	insert( T const& e, QNodePosi<T> p, QNodePosi<T> b = NULL);
};



// ============================================================
// =====================   初始化、清除  ========================
// ============================================================
//----------------------------
// 初始化
//----------------------------
template <typename T> void Quadlist<T>::init(){
	head = new QNode<T>;
	tail = new QNode<T>;
	head->succ = tail; head->pred = NULL;
	tail->pred = head; tail->succ = NULL;
	head->above = tail->above = NULL;
	head->below = tail->below = NULL;
	_size = 0;
}
//----------------------------
// 清除
//----------------------------
template <typename T> int Quadlist<T>::clear(){
	Rank oldSize = _size;
	while(0 < _size)
		remove( head->succ );
	return oldSize;
}


// ============================================================
// ======================   插入删除  ==========================
// ============================================================
//----------------------------
// 插入
//----------------------------
template <typename T> 
QNodePosi<T> Quadlist<T>:: insert( T const& e, QNodePosi<T> p, QNodePosi<T> b = NULL){
	QNodePosi<T> x = new QNode<T>(e, p, p->succ, NULL, b);
	p->succ->pred = x;
	p->succ = x;
	if(b) b->above = x;
	_size++;
	return x;
}
//----------------------------
// 删除
//----------------------------
template <typename T>  
T Quadlist<T>::remove( QNodePosi<T> p ){
	T e = p->entry;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	if(p->below) p->below->above = p->above;
	if(p->above) p->above->below = p->below;
	delete p;
	_size--;
	return e;
}