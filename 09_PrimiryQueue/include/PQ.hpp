//栈和队列是PQ的特例：优先级取决于元素插入的次序
//
template <typename T> struct PQ{
	virtual void insert(T) 0 ;
	virtual T delMax() = 0;
	virtual T& getMax() = 0;
};
