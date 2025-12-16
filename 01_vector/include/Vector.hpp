#include <cstdlib>
#include <ctime>
#include "Rank.hpp"
#include <algorithm>
#include <stdexcept>

#define DEFAULT_CAPACITY 3 //默认的初始容量（实际应用中可设置为更大） 

#ifndef VECTOR_H
#define VECTOR_H

template <typename T> class Vector { //向量模板类 
protected: 
	Rank _size; 
	Rank _capacity; 
	T* _elem; //规模、容量、数据区 

	void copyFrom ( T const* A, Rank lo, Rank hi ); //复制数组区间A[lo, hi) 
	void expand(); //空间不足时扩容 
	void shrink(); //装填因子过小时压缩 
    
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
	bool disordered() const;//判断向量是否已经排序
	T get(Rank r) const { return _elem[r]; }
	Rank find ( T const& e ) const { return find ( e, 0, _size ); } //无序向量整体查找 
	Rank find ( T const& e, Rank lo, Rank hi ) const; //无序向量区间查找 
	Rank select( Rank k ) { return quickSelect( _elem, _size, k ); } //从无序向量中找到第k大的元素 
	T max() const; //无序向量最大元素 
	T min() const; //无序向量最小元素 
	Rank maxIndex() const; //无序向量最大元素的秩 
	Rank minIndex() const; //无序向量最小元素的秩
	

// 可写访问接口 
	T& operator[] ( Rank r ){return _elem[r];} //重载下标操作符，可以类似于数组形式引用各元素 
	const T& operator[] ( Rank r ) const; //仅限于做右值的重载版本 
	Vector<T> & operator= ( Vector<T> const& V); //重载赋值操作符，以便直接克隆向量 
	T remove ( Rank r ); //删除秩为r的元素 
	Rank remove ( Rank lo, Rank hi ); //删除秩在区间[lo, hi)之内的元素 
	Rank insert ( Rank r, T const& e ); //插入元素 
	Rank insert ( T const& e ); //默认作为末元素插入 
	// void sort ( Rank lo, Rank hi ); //对[lo, hi)排序 
	// void sortAll() { sort ( 0, _size ); } //整体排序 
	void unsort ( Rank lo, Rank hi ); //对[lo, hi)置乱 
	void unsortAll() { unsort ( 0, _size ); } //整体置乱 
	Rank dedup(); //无序去重 
	Rank uniquify(); //有序去重 
	void swap(Rank i,Rank j);
	
// 遍历 
	void traverse ( void (*visit)(T&) ); //遍历（使用函数指针，只读或局部性修改） 
	template <typename VST> void traverse ( VST& visit ); //遍历（使用函数对象，可全局性修改） 
}; //Vector

template <typename T>
Rank quickSelect(Vector<T>& vec, Rank k);


template <typename T> 
const T& Vector<T>::operator[] ( Rank r ) const {//仅限于做右值的重载版本 
	return _elem[r];
} 

template <typename T> 
Vector<T> &  Vector<T>::operator= ( Vector<T> const& V){//重载赋值操作符，以便直接克隆向量 
	if (this != &V) {
        delete[] _elem;
        copyFrom(V._elem, 0, V._size);
    }
    return *this;
} 

//----------------------------------
// copyFrom 复制数组区间A[lo, hi)
//----------------------------------
template <typename T> void Vector<T>::copyFrom ( T const* A, Rank lo, Rank hi ){//复制数组区间A[lo, hi) 
    _elem = new T[_capacity=std::max((hi - lo),DEFAULT_CAPACITY)*2];
    _size = 0;
    while(lo < hi){
        _elem[_size++] = A[lo++];
    }
}

//----------------------------------
// 遍历
//----------------------------------
template <typename T> 
void Vector<T>::traverse(void (*visit)(T&)) {
    for (Rank i = 0; i < _size; i++) visit(_elem[i]);
} //遍历（使用函数指针，只读或局部性修改） 

template <typename T> template <typename VST> 
void Vector<T>::traverse( VST& visit) {
    for (Rank i = 0; i < _size; i++) visit(_elem[i]);
}




// ============================================================
// ====================  向量的扩容和压缩算法  ===================
// ============ 时间复杂度均摊为O(1)，空间复杂度为O(n) =============
// ============================================================
template <typename T> void Vector<T>::expand(){//空间不足时扩容 
    if(_size < _capacity) return;
    if(_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; i++){
        _elem[i] = oldElem[i];
    }
    delete[] oldElem;
}
template <typename T> void Vector<T>::shrink(){ //装填因子过小时压缩 //暂定25%
    if( _capacity < DEFAULT_CAPACITY<<1) return;
	if(_size<<2 > _capacity) return;
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];
	for(int i = 0; i < _size ;i++){
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;
}


// ============================================================
// =====================  有序与无序向量  =======================
// ============================================================

template <typename T> bool Vector<T>::disordered() const{
	for(Rank i = 1; i < _size; i++){
		if(_elem[i-1] > _elem[i]){
			return true;
		}
	}
	return false;
}

//无序向量区间查找 
template <typename T> Rank  Vector<T>::find ( T const& e, Rank lo, Rank hi ) const{
	for(  ; lo < hi; lo++){
		if(e == _elem[lo]){
			return lo;
		}
	}
	return -1;

} 


//----------------------------------
// 置乱：区间置乱与整体置乱
//----------------------------------
//对[lo, hi)置乱 
template <typename T> void  Vector<T>::unsort( Rank lo, Rank hi ){
	while( lo < hi-- ){
		swap(_elem[--hi], _elem[lo + std::rand() % (hi - lo)]);
	}
} 

//整体置乱 
// template <typename T>  void Vector<T>::unsortAll() { 
// 	unsort ( 0, _size ); 
// } 

//----------------------------------
// 去重：无序去重与有序去重
//----------------------------------
//无序去重 ，复杂度为O(n^2)
template <typename T> 
Rank Vector<T>::dedup() {
    Rank oldSize = _size;
    for (Rank i = 0; i < _size; ++i) {
        Rank j = i + 1;                   // 必须初始化
        while ((j = find(_elem[i], j, _size)) != -1) { 
            remove(j);                    // 删除 j
        }
    }
    return oldSize - _size;
}

template <typename T>
Rank Vector<T>::uniquify() {
    if (_size < 2) return 0; // 空或只有一个元素

	Rank oldSize = _size;

    Rank i = 0; // 慢指针，指向最后一个不重复元素
    for (Rank j = 1; j < _size; j++) { // 快指针
        if (_elem[i] != _elem[j]) {
            _elem[++i] = _elem[j]; // 遇到新元素就移动到 i 后面
        }
    }
    
    _size = i + 1;
    return oldSize - _size; // 返回删除的元素个数
}


// ============================================================
// =====================  向量的插入、删除算法  ==================
// ============================================================

//----------------------------------
// [1]insert(r, e) 插入一个元素
// [2]insert(e) 默认作为末元素插入
//----------------------------------
template <typename T> Rank Vector<T>::insert ( Rank r, T const& e ){
	expand();
	for(int i = _size; i > r; i--){
		_elem[i] = _elem[i-1];
	}
	_elem[r] = e;
	_size++;
	return r;
}
template <typename T> Rank Vector<T>::insert ( T const& e ) { 
	return insert ( _size, e ); 
} 

//----------------------------------
// [1]remove(r) 删除一个元素
// [2]remove(lo, hi) 删除区间元素
//----------------------------------
//删除秩为r的元素 
template <typename T> T  Vector<T>::remove ( Rank r ){
	T e = _elem[r];
	for(int i = r; i < _size -1; i++){
		_elem[i] = _elem[i+1];
	}
	//记得更新容量
	_size--;
	shrink();
	return e;
} 

template <typename T> 
Rank Vector<T>::remove ( Rank lo, Rank hi ){//删除秩在区间[lo, hi)之内的元素 
	//边界检查------
	if (lo < 0) lo = 0;
    if (hi > _size) hi = _size;
    if (lo >= hi) return 0;
	//--------------
	Rank n = hi - lo;
	while(hi < _size){
		_elem[lo++] = _elem[hi++];
	}
	_size -= n;
	shrink();
	return n;
} 



template <typename T> 
T Vector<T>::max() const{ 
	//确保向量非空
	if(_size <= 0) throw std::runtime_error("Vector is empty");
	
	//寻找最大元素
	T maxElem = _elem[0];
	for(Rank i = 1; i < _size; i++){
		maxElem = (_elem[i] > maxElem) ?  _elem[i] : maxElem;
	}
	return maxElem;
};


template <typename T> //无序向量最小元素 
T Vector<T>::min() const{
	if(_size <= 0) throw std::runtime_error("Vector is empty");

	T minElem = _elem[0];
	for(Rank i = 1; i < _size; i++){
		minElem = (_elem[i] < minElem) ?  _elem[i] : minElem;
	}
	return minElem;

} 

template <typename T> //无序向量最大元素的秩 
Rank Vector<T>::maxIndex() const{
	//确保向量非空
	//if(_size < = 0) throw std::runtime_error("Vector is empty");
	if(_size <= 0) return -1;
	
	//寻找最大元素
	T maxElem = _elem[0];
	Rank maxIndex = 0;
	for(Rank i = 1; i < _size; i++){
		if(_elem[i] > maxElem){
			maxElem = _elem[i];
			maxIndex = i;
		}
	}
	return maxIndex;
} 

template <typename T> //无序向量最小元素的秩
Rank Vector<T>::minIndex() const{
	if(_size <= 0) return -1;
	
	//寻找最大元素
	T minElem = _elem[0];
	Rank minIndex = 0;
	for(Rank i = 1; i < _size; i++){
		if(_elem[i] > minElem){
			minElem = _elem[i];
			minIndex = i;
		}
	}
	return minIndex;
} 


template <typename T>
void Vector<T>::swap(Rank i, Rank j){
    int temp;

    temp = _elem[i];
    _elem[i] = _elem[j];
    _elem[j] = temp;
}

// ============================================================
// ====================    向量的排序算法     ===================
// == [1]起泡排序(bubble sort)    ==============================
// == [2]选择排序(select sort)    ==============================
// == [3]归并排序(merge sort)     ==============================
// == [4]堆排序(heap sort)        ==============================
// == [5]快速排序(quick sort)     ==============================
// == [6]希尔排序(shell sort)     ==============================
// ============================================================


template <typename T> 
void sort ( Rank lo, Rank hi ){ //对[lo, hi)排序 
    switch (std::rand() % 6) {
        case 1: bubbleSort_v1(lo, hi); break;
        case 2: selectionSort(lo, hi); break;
        case 3: mergeSort(lo, hi); break;
        case 4: heapSort(lo, hi); break;
        case 5: quickSort_v1(lo, hi); break;
        default: shellSort(lo, hi); break;
    }
}


#endif