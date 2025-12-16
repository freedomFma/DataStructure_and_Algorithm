#include "./ListNode.hpp"
template <typename T> class List{
private:
	int _size;
	ListNode<T>* header;
	ListNode<T>* trailer;
protected: 
//初始化
	void init();
	void copyNode(ListNodePosi(T) p, int n);
	void clear();
	void selectSort(ListNodePosi(T) p, int n);
	void insertionSort(ListNodePosi(T) p, int n);
	void mergeSort(ListNodePosi(T) &p, int n);
	
public:
//构造函数、析构函数
	List(){ init(); } //默认构造函数
	//创建以e节点为first、尺寸为n的列表
	List(ListNode<T>& e) { init(); header->succ = e; trailer->pred = e; 
		e->pred = header; e->succ = trailer;}
	//
	List(List<T> const& L); //创建一个与List L一模一样的列表
	List(List<T> const& L, Rank r, int n);//创建List L自秩为r起的n项
	List(ListNodePosi(T) p ,int n);//创建List L自位置p起的n项
	~List();
	
//只读接口
	Rank size() const {return _size;}
	ListNodePosi(T) first() const {return header->succ;}
	ListNodePosi(T) last() const {return trailer->pred;}
	ListNodePosi(T) find(T const& e) const;
	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;
	ListNodePosi(T) search(T const& e) const;	
	ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;
	int disordered() const;
	bool valid(ListNodePosi(T) p) {return p->data != NULL;}
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
	
//可写接口
//插入
	ListNodePosi(T) insertAsFirst(T const& e);
	ListNodePosi(T) insertAsLast(T const& e);
	ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e);
	ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);
	ListNodePosi(T) insert(T const e, ListNodePosi(T) p);
	T remove( ListNodePosi(T) p );
	//排序
	void sort();
	void mergeSort(ListNodePosi(T)&p, Rank n);
	ListNodePosi(T) merge(ListNodePosi(T) p, Rank n, List<T>& L, ListNodePosi(T) q, Rank m);
	//唯一化
	int deduplicate();
	int uniquify();

//遍历
	void traverse(void (*visit) (T&));
//运算器
	T operator[](Rank r);
};


template <typename T> T List<T>::operator[](Rank r){
		listNodePosi<T> p = first();
		while(0 < r--){
			p = p->succ;
		}
		return p->data;
}


// ============================================================
// ===============    初始化    ===================
// ============================================================
template <typename T> void List<T>::init(){
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer; header->pred = NULL;
	trailer->pred = header; trailer->succ = NULL;
	_size = 0;
}
//
template <typename T> void List<T>::copyNode(ListNodePosi(T) p, int n){
	init();
	while(n--){
		insertAsLast(p->data);
		p = p->succ;
	}
}


//public：构造函数的实现
template <typename T> List<T>::List(ListNodePosi(T) p, int n){
	copyNode(p, n);
}
template <typename T> List<T>::List(List<T> const& L){
	copyNode(L.first(), L._size);
}
template <typename T> List<T>::List(List<T> const& L, Rank r, int n){
	ListNodePosi(T) p = L.first();
	while(r-- && p!= L.trailer) p = p->succ;
	copyNode(p, n);
}
//析构函数
template <typename T> void List<T>::clear(){
	int oldSize = _size;
	while( 0 < _size){
		remove(header->succ);
	}
	return oldSize;
}
template <typename T> List<T>::~List(){
	clear();
	delete header;
	delete trailer;
}

// ============================================================
// ===============    查找    ===================
// ============================================================
//public只读函数的实现
template <typename T> ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const {
	while (0 < n--)
		if(e == (p = p->pred)->data) return p;
	return NULL;
}
template <typename T> ListNodePosi(T) List<T>::find(T const& e) const {
	find(T const& e, _size, trailer);
}
//在有序列表内节点p的n个（真）前驱中，找到不大于e的最靠后者
template <typename T> 
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const{
	do{ p = p->pred; n--; }
	while((-1<n) && (e< p->data));
	return p;
}

// ============================================================
// ===============    插入    ===================
// ============================================================
//public可写函数的实现
template <typename T> ListNodePosi(T) List<T>::insertAsFirst(T const& e){
	ListNode(T) x = new listNode(e);
	x = header->succ->pred;
	x->succ = header->succ;
	header->succ = x;
	x->pred = header;
	_size++;
}
template <typename T> ListNodePosi(T) List<T>::insertAsLast(T const& e){
	ListNode(T) x = new listNode(e);
	x = tail->pred->succ;
	x->pred = tail->pred;
	tail->pred = x;
	x->succ = tail;
	_size++;
}

template <typename T> ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p,T const& e){
	_size ++;
	return p->insertAsPred(e);
}
template <typename T> ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p,T const& e){
	_size ++;
	return p->insertAsSucc(e);
}

template <typename T> ListNodePosi(T) List<T>::insert(T const e, ListNodePosi(T) p){
	_size++;
	return p->insertAsPred;
}

// ============================================================
// ===============    删除    ===================
// ============================================================
template <typename T> T List<T>::remove( ListNodePosi(T) p ){
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;
}


// ============================================================
// ===============    去重与唯一化    ===================
// ============================================================
//去重
template <typename T> int List<T>::deduplicate(){
	int oldSize = _size;
	ListNodePosi(T) p = first();
	for(Rank r = 0; p != trailer; p = p->succ){
		if(ListNodePosi(T) q = find(p->data, r, p)) remove(q);
		else r++;
	}
	return oldSize - _size;
}
//唯一化
template <typename T> int List<T>::uniquify(){
	if (_size < 2) return 0;
	int oldSize = _size ;
	ListNodePosi(T) p = first();
	ListNodePosi(T) q;
	while(trailer != (q = p->succ))
		if(p -> data != q -> data) p = q;
		else remove(q);
	return oldSize - _size;
}


//遍历
template <typename T> void List<T>::traverse(void (*visit) (T&)){
	ListNodePosi(T) p = header;
	while((p = p->succ) != trailer) 
		visit(p->data);
}