using Rank = unsigned int; //秩 
#define DEFAULT_CAPACITY 3 //默认的初始容量（实际应用中可设置为更大） 

template <typename T> class Vector { //向量模板类 
protected: 
	Rank _size; 
	Rank _capacity; 
	T* _elem; //规模、容量、数据区 

	void copyFrom ( T const* A, Rank lo, Rank hi ); //复制数组区间A[lo, hi) 
	void expand(); //空间不足时扩容 
	void shrink(); //装填因子过小时压缩 
	bool bubble_v1 ( Rank lo, Rank hi ); //扫描交换 
	Rank bubble_v2 ( Rank lo, Rank hi ); //扫描交换 
	void bubbleSort ( Rank lo, Rank hi ); //起泡排序算法 
	Rank maxItem ( Rank lo, Rank hi ); //选取最大元素 
	void selectionSort ( Rank lo, Rank hi ); //选择排序算法 
	void merge ( Rank lo, Rank mi, Rank hi ); //归并算法 
	void mergeSort ( Rank lo, Rank hi ); //归并排序算法 
	void heapSort ( Rank lo, Rank hi ); //堆排序
	Rank partition ( Rank lo, Rank hi ); //轴点构造算法 
	void quickSort ( Rank lo, Rank hi ); //快速排序算法 
	void shellSort ( Rank lo, Rank hi ); //希尔排序算法 
    
public: 
// 构造方法 
	Vector ( Rank c = DEFAULT_CAPACITY ) //容量为c的空向量
		{ _elem = new T[_capacity = c]; _size = 0; } 
	Vector ( Rank c, Rank s, T v ) //容量为c、规模为s、所有元素初始为v；s<=c 
		{ _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); } 
	Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } //数组整体复制 
	Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } //区间 
	Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); } //向量整体复制 
	Vector ( Vector<T> const& V, Rank lo, Rank hi )
		{ copyFrom ( V._elem, lo, hi ); } //区间 
	
// 析构方法 
	~Vector() { delete [] _elem; } //释放内部空间 
	
// 只读访问接口 
	Rank size() const { return _size; } //规模 
	bool empty() const { return !_size; } //判空 
	int disordered() const;//判断向量是否已经排序
	T get(Rank r) const { return _size[r]; }
	Rank find ( T const& e ) const { return find ( e, 0, _size ); } //无序向量整体查找 
	Rank find ( T const& e, Rank lo, Rank hi ) const; //无序向量区间查找 
	Rank select( Rank k ) { return quickSelect( _elem, _size, k ); } //从无序向量中找到第k大的元素 
	Rank search( T const& e ) const //有序向量整体查找 
	{ return ( 0 >= _size ) ? -1 : search ( e, 0, _size ); } 
	Rank binSearch_v1 (T* A, T const& e, Rank lo, Rank hi ) const; //有序向量区间查找 
	Rank binSearch_v2 (T* A, T const& e, Rank lo, Rank hi ) const;
	Rank binSearch_v3 (T* A, T const& e, Rank lo, Rank hi ) const;
	

// 可写访问接口 
	T& operator[] ( Rank r ){return _elem[r];} //重载下标操作符，可以类似于数组形式引用各元素 
	const T& operator[] ( Rank r ) const{return _elem[r];} //仅限于做右值的重载版本 
	Vector<T> & operator= ( Vector<T> const& ); //重载赋值操作符，以便直接克隆向量 
	T remove ( Rank r ); //删除秩为r的元素 
	Rank remove ( Rank lo, Rank hi ); //删除秩在区间[lo, hi)之内的元素 
	Rank insert ( Rank r, T const& e ); //插入元素 
	Rank insert ( T const& e ) { return insert ( _size, e ); } //默认作为末元素插入 
	void sort ( Rank lo, Rank hi ); //对[lo, hi)排序 
	void sortAll() { sort ( 0, _size ); } //整体排序 
	void unsort ( Rank lo, Rank hi ); //对[lo, hi)置乱 
	void unsortAll() { unsort ( 0, _size ); } //整体置乱 
	Rank dedup(); //无序去重 
	Rank uniquify(); //有序去重 
	
// 遍历 
	void traverse ( void (* ) ( T& ) ); //遍历（使用函数指针，只读或局部性修改） 
	template <typename VST> void traverse ( VST& ); //遍历（使用函数对象，可全局性修改） 
}; //Vector**


// protected: 
template <typename T> void Vector<T>::copyFrom ( T const* A, Rank lo, Rank hi ){//复制数组区间A[lo, hi) 
    _elem = new T[_capasity=max((hi - lo),DEFAULT_CAPACITY)*2];
    _size = 0;
    while(lo < hi){
        _elem[_size++] = A[lo++];
    }
}
template <typename T> void Vector<T>::expand(){//空间不足时扩容 
    if(_size < _capasity) return;
    if(_capasity < DEFAULT_CAPACITY) _capasity = DEFAULT_CAPACITY;
    T* oldElem = _elem;
    T* _elem = new T[_capasity <<= 1];
    for (int i = 0; i < _size; i++){
        _elem[i] = oldElem[i];
    }
    delete[] oldElem;
}
template <typename T> void Vector<T>::shrink(){ //装填因子过小时压缩 //暂定25%
    if( _capasity < DEFAULT_CAPACITY<<1) return;
	if(_size<<2 > _capasity) return;
	T* oldElem = _elem;
	_elem = new T[_capasity >>= 1];
	for(int i = 0; i < _size ;i++){
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;
}

template <typename T> 
bool Vector<T>::bubble_v1(Rank lo, Rank hi){//如果一开始就是
	bool sorted = true;
	while(++lo < hi){
		if(_elem[lo - 1] > _elem[lo]){
			swap(_elme[lo-1],_elem[lo]);
			sorted = false;
		}
	}
	return sorted;
}

template <typename T> 
void Vector<T>::bubbleSort(Rank lo, Rank hi){
	while(!bubble(lo,hi--));
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi){
	while(lo < (hi = bubble(lo, hi))-1);
}

template <typename T> 
Rank Vector<T>::bubble_v2(Rank lo, Rank hi){
	Rank last = lo;
	while(++lo < hi){
		if(_elem[lo - 1] > _elem[lo]){
			swap(_elem[lo-1],_elem[lo]);
			last = lo;
		}
	}
	return last;
}


template <typename T> void Vector<T>::selectionSort ( Rank lo, Rank hi ){ //选择排序算法 

}
template <typename T> //对各自有序的[lo, mi)和[mi, hi)做归并
void Vector<T>::merge( Rank lo, Rank mi, Rank hi ) { // lo < mi < hi 
	Rank i = 0; T* A = _elem + lo; //合并后的有序向量A[0, hi - lo) = _elem[lo, hi)
	Rank j = 0, lb = mi - lo; T* B = new T[lb]; //前子向量B[0, lb) <-- _elem[lo, mi)
	for ( Rank i = 0; i < lb; i++ ) B[i] = A[i]; //复制出A的前缀
	Rank k = 0, lc = hi - mi; T* C = _elem + mi; //后缀C[0, lc) = _elem[mi, hi)就地
	while ( ( j < lb ) && ( k < lc ) ) //反复地比较B、C的首元素
		A[i++] = ( B[j] <= C[k] ) ? B[j++] : C[k++]; //将更小者归入A中 
	while ( j < lb ) //若C先耗尽，则 
		A[i++] = B[j++]; //将B残余的后缀归入A中——若B先耗尽呢？
	delete[] B; //释放临时空间：mergeSort()过程中，如何避免此类反复的new/delete？ 
}
template <typename T> //向量归并排序
void Vector<T>::mergeSort( Rank lo, Rank hi ) { // 0 <= lo < hi <= size
	if ( hi - lo < 2 ) return; //单元素区间自然有序，否则...
	Rank mi = ( lo + hi ) >> 2; //以中点为界
	mergeSort( lo, mi ); mergeSort( mi, hi ); //前缀、后缀分别排序
	merge( lo, mi, hi ); //归并
}


template <typename T> Rank Vector<T>:: partition ( Rank lo, Rank hi ){ //轴点构造算法 
	swap(_elem[lo], _elem[lo+(rank()%(hi - lo))]); //随机抽取作为轴点
	T pivot = _elem[lo]; //取出轴点作备份
	while(lo < hi){
		do hi--;
		while((lo<hi) && (pivot <= _elem[hi])); //增大G的区域. 勤于拓展，懒于交换
		//while((lo<hi) && (pivot < _elem[hi]));//勤于交换，懒于拓展. 当大量重复元素时能够使得轴点的位置更靠中，达到减少递归深度的目的
		if(lo<hi) _elem[lo] = _elem[hi]; //传给lo
		do lo++;
		while((lo<hi) && (pivot >= _elem[lo]));//增大L的区域
		//while((lo<hi) && (pivot > _elem[lo])); 勤于交换，懒于拓展. 大量重复元素时轴点靠中
		if(lo<hi) _elem[hi] = _elem[lo];//传给hi
	}
	_elem[hi] = pivot;//最终lo = hi，将备份轴点赋给轴点“应该在的位置”
	return hi;
}
template <typename T> Rank Vector<T>::partition(Rank lo, Rank hi){
	swap(_elem[lo], _elem[lo+rand()%(hi-lo)]);
	T pivot = _elem[lo];
	Rank mi = lo;
	for(Rank k = lo+1; k < hi; k++){
		if(_elem[k] < pivot){
			swap(_elem[++mi],_elem[k]);
		}
	}
	swap(_elem[lo], _elem[mi]);
	return mi;
}

template <typename T> void Vector<T>::quickSort ( Rank lo, Rank hi ){//快速排序算法
	if(hi - lo < 2 ) return;//递归基，子集只有一个元素
	Rank mi = partition(lo, hi);//选取轴点
	quickSort(lo, mi);//递归实现
	quickSort(mi+1, hi);//递归实现
}

#define Put(K ,s, t) {if (1<(t) - (s)) {K.push(s); K.push(t)}}//s先进，t后进，t在顶
#define get(K ,s, t) {t = K.pop(); s = K.pop();} //t在顶，
template <typename T> void Vector<T>::quickSort(Rank lo, Rank hi){
	Stack<Rank> Task;//
	Put(Task, lo, hi);
	while(!Task.empty){
		Get(Task, lo, hi); //小任务在顶先出
		Rank mi = partition(lo, hi);
		if(mi - lo < hi -mi){
			Put(Task, mi+1, hi);//大任务先进：右边大
			Put(Task ,lo, mi); 
		}
		else{
			Put(Task ,lo, mi);//大任务先进：左边大
			Put(Task, mi+1, hi);
		}//大任务先进栈，小任务先出栈
	}
}

template <typename T> void Vector<T>::shellSort(Rank lo, Rank hi){
	for (Rank d = (hi - lo) / 2; d > 0; d >>= 1) {
		for (Rank j = lo + d; j < hi; j++) {
			T x = _elem[j];
			Rank i = j;
			while (i >= lo + d && x < _elem[i - d]) {
				_elem[i] = _elem[i - d];
				i -= d;
			}
			_elem[i] = x;
		}
	}
}


// public:
// 只读访问接口 
template <typename T> int  Vector<T>::disordered() const{//判断向量是否已经排序

}

template <typename T> Rank  Vector<T>::find ( T const& e, Rank lo, Rank hi ) const{

} //无序向量区间查找 

template <typename T>
Rank Vector<T>::binSearch_v1(T* A, T const& e, Rank lo, Rank hi) const {
	while(lo < hi){
		Rank mid = (lo + hi) >> 1;
		if(e < A[mid]) {hi = mid;}
		else if (A[mid] < e){lo = mid+1;}
		else return mid;
	}
	return -1;
}

template <typename T>
Rank Vector<T>::binSearch_v2(T* A, T const& e, Rank lo, Rank hi) const{
	while(1 < hi - lo){
		Rank mid = (lo + hi )>>1;
		(e < A[mid])? hi = mid :lo = mid;
	}
	return e == A[lo ]? lo : -1 ;
}

template <typename T>
Rank Vector<T>::binSearch_v3(T* A, T const& e, Rank lo, Rank hi) const {
	while(lo < hi){
		Rank mid = (lo + hi) >> 1;
		(e< A[mid])? hi = mid : lo = mid+1;
	}
	return lo-1;
}

// #include "./Fib.hpp"
// template <typename T> static Rank fibSearch (T* A, T const& e, Rank lo, Rank hi){
// 	Fib fib(hi-lo);
// 	while(lo < hi){
// 		while(hi-lo < fib.get()) fib.prev();
// 		Rank mi = lo +fib.get()-1;
// 		if (e < A[mi]) hi = mi;
// 		else if (A[mi]< e) lo = mi+1;
// 		else return mi;
// 	}
// }

template <typename T> static Rank fibSearch (T* A, T const& e, Rank lo, Rank hi){
	Fib fib(hi-lo);
	while(lo < hi){
		Rank mi = lo +fib.prev()-1;
		if (e < A[mi]) hi = mi;
		else if (A[mi]< e) lo = mi+1;
		else return mi;
	}
}

// 可写访问接口 

template <typename T> 
Vector<T> &  Vector<T>::operator= ( Vector<T> const& ){

} //重载赋值操作符，以便直接克隆向量 
template <typename T> T  Vector<T>::remove ( Rank r ){

} //删除秩为r的元素 
template <typename T> 
Rank Vector<T>::remove ( Rank lo, Rank hi ){} //删除秩在区间[lo, hi)之内的元素 
template <typename T> 
Rank Vector<T>::insert ( Rank r, T const& e ){} //插入元素 
//Rank insert ( T const& e ) { return insert ( _size, e ); } //默认作为末元素插入 
template <typename T> 
void  Vector<T>::sort ( Rank lo, Rank hi ){//对[lo, hi)排序 
	switch (rand() % 5){
		case 1: bubblesort(lo, hi); break;
		case 2: selectionSort(lo, hi); break;
		case 3: mergeSort(lo, hi); break;
		case 4: heapSort(lo, hi); break;
		default: quickSort(lo, hi); break;
	}
} 
// void sort() { sort ( 0, _size ); } //整体排序 
template <typename T> void  Vector<T>::unsort( Rank lo, Rank hi ){
	
} //对[lo, hi)置乱 

//void unsort() { unsort ( 0, _size ); } //整体置乱 
template <typename T> 
Rank  Vector<T>::dedup(){} //无序去重 
template <typename T> 
Rank  Vector<T>::uniquify(){} //有序去重 
	
// 遍历 
template <typename T> 
void  Vector<T>::traverse ( void (* ) ( T& ) ){} //遍历（使用函数指针，只读或局部性修改） 

template <typename T> template <typename VST> 
void  Vector<T>::traverse ( VST& ){} //遍历（使用函数对象，可全局性修改） 