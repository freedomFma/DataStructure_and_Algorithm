#include "Vector.hpp"
#include "PQ.hpp"

#define Parent(i) (((i) - 1) >> 1) //PQ[i]的父节点（floor((i-1)/2)，i无论正负）
#define LChild(i) (1+ ((i) << 1)) //PQ[i]的左孩子
#define RChild(i) ((1+(i)) << 1) //PQ[i]的右孩子
#define  InHeap(n, i)      ( ( ( -1 ) != ( i ) ) && ( ( i ) < ( n ) ) ) //判断PQ[i]是否合法
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //判断PQ[i]是否有一个（左）孩子
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //判断PQ[i]是否有两个孩子
#define  Bigger(PQ, i, j)  ( ( PQ[i] < PQ[j] ) ? j : i ) //取大者（等时前者优先）
#define  ProperParent(PQ, n, i) /*父子（至多）三者中的大者*/ \
             ( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
             ( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
             ) \
             ) //相等时父节点优先，如此可避免不必要的交换

template <typename T> struct PQ_ComplHeap : public PQ<T>, public Vector<T>{
	PQ_ComplHeap(T* A, Rank n){
		copyFrom(A, 0, n);
		heapify(_elem, n);
	}
	void insert(T);
	T delMax();
	T& getMax();
};

template <typename T> Rank percolateDown(T* A, Rank n, Rank i);//上滤和下滤的参数为什么不一样？
template <typename T> Rank peicolateUp(T* A, Rank i);

template <typename T> void heapify;

//-------------------
// getMax()返回最大值
//-------------------
template <typename T> T& PQ_ComplHeap<T>::getMax(){
	return _elem[0];
}

//-------------------
// [1]插入数据insert(e)
// [2]实施上滤
//-------------------
template <typename T> void PQ_ComplHeap<T>::insert(T e){
	Vector<T>::insert(e);
	percolateUp(_elem, _size-1);//针对节点_size-1也就是最后一个节点进行上滤
}

template <typename T> Rank percolateUp(T*A , Rank i){
	while(0 < i){
		Rank j = Parent(i);
		if( !(A[j] < A[i]) ) break;//父节点大于等于这个节点
		swap(A[i] ,A[j]);
		i = j;//父亲节点成为新的待上滤节点
	}
	return i;//返回最终抵达的秩
}

//-------------------
// [1]删除最大值delMax()
// [2]实施下滤
//-------------------
template <typename T> T PQ_ComplHeap<T>::delMax(){
	swap(_elem[0], _elem[--_size] );
	percolateDown(_elem, _size, 0);//针对新的堆顶位置数据实施下滤
	return _elem[_size];//返回删除的那个节点（原来的堆顶）
}

// template <typename T>
// Rank ProperParent(T* A, Rank n, Rank i){
// 	if( _elem[i] >= _elem[2*i+1] ){
// 		if(_elem[i] >= _elem[2 i+2]) return i;
// 		else return 2*i+2;
// 	}
// 	else{
// 		if (_elem[2*i+1] >= _elem[2*i+2]) return  retrun 2*i+1;
// 		else return 2*i+2;
// 	}
// }

template <typename T> Rank percolateDown(T* A, Rank n, Rank i){
	Rank j;
	while( i!= (j = ProperParent(A, n, i)))//
		swap(A[i], A[j]); i=j;
	return i;
}


//-------------------
// [1]建堆：自上而下的上滤：O(nlogn)
// [2]建堆：自下而上的下滤floyd O(n)
//-------------------
template <typename T> void heapify_up(T* A, const Rank n){
	for( int i = 1; i<n ;i++ ){
		percolateUp(A, i);
	}
}
template <typename T> //Robert Floyd
void heapify(T* A, Rank n){
	for(Rank i = n/2-1; -1 != i; i--){
		percolateDown(A, n, i);
	}
}