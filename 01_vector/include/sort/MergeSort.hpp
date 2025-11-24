#pragma once
#include "../Vector.hpp"

// ============================================================
// ==============    归并排序 merge sort   ======================
// ============================================================

//----------------------------------
// [1]归并排序的递归实现
// [2]归并算法的实现
//----------------------------------
template <typename T> //向量归并排序
void mergeSort( Rank lo, Rank hi ) { // 0 <= lo < hi <= size
	if ( hi - lo < 2 ) return; //单元素区间自然有序，否则...
	Rank mi = ( lo + hi ) >> 1; //以中点为界
	mergeSort( lo, mi ); mergeSort( mi, hi ); //前缀、后缀分别排序
	merge( lo, mi, hi ); //归并
}

template <typename T> //对各自有序的[lo, mi)和[mi, hi)做归并
void merge( Rank lo, Rank mi, Rank hi ) { // lo < mi < hi 
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

