#include "./ListNode.hpp"
template <typename T> class List{
private:
	int _size;
	ListNodePosi(T) header;
	ListNodePosi(T) trailer;
protected: 
//初始化
	void init();
	void List<T>::copyNode(ListNodePosi(T) p, int n);
	
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
	ListNodePosi(T) search(T const& e) const;	
	int disordered() const;
	bool valid(ListNodePosi(T) p) {return p->data != NULL;}
	
//可写接口
	ListNodePosi(T) insertAsFirst(T const& e);
	ListNodePosi(T) insertAsLast(T const& e);
	ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e);
	ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);
	T remove( ListNodePosi(T) p );
	void sort();
	int deduplicate();
	int uniquify();

//遍历
	traverse();
//运算器
	T operator[](Rank r);
};


template <typename T> void List<T>::init(){
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer; header->pred = NULL;
	trailer->pred = header; trailer->succ = NULL;
	_size = 0;
}
template <typename T> T List<T>::operator[](Rank r){
		listNodePosi<T> p = first();
		while(0 < r--){
			p = p->succ;
		}
		return p->data;
	}



template <typename T> ListNodePosi(T) List<T>::insertAsFirst(T const& e){
	ListNode(T) x = new listNode(e);
	x = header->succ->pred;
	x->succ = header->succ;
	header->succ = x;
	x->pred = header;
	_size++;
}
template <typename T> T List<T>::remove( ListNodePosi(T) p ){
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;
}
