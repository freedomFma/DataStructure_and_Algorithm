#pragma once
#include "../Vector.hpp"

//---------  二分查找算法  -----------
//----------------------------------
// [1]二分查找：最后返回中间点
// [2]二分查找：返回lo
// [3]二分查找：返回hi-1
//  主要的差别在于区间的选择。都是先比较左边，再比较右边。
//----------------------------------
template <typename T>
Rank binSearch_v1(T* A, T const& e, Rank lo, Rank hi)  {
	while(lo < hi){
		Rank mid = (lo + hi) >> 1;
		if(e < A[mid]) {hi = mid;}
		else if (A[mid] < e){lo = mid+1;}
		else return mid;
	}
	return -1;
}
template <typename T>
Rank binSearch_v2(T* A, T const& e, Rank lo, Rank hi) {
	while(1 < hi - lo){
		Rank mid = (lo + hi )>>1;
		(e < A[mid])? hi = mid :lo = mid;
	}
	return e == A[lo ]? lo : -1 ;
}

template <typename T>
Rank binSearch_v3(T* A, T const& e, Rank lo, Rank hi){
	while(lo < hi){
		Rank mid = (lo + hi) >> 1;
		(e< A[mid])? hi = mid : lo = mid+1;
	}
	return lo-1;
}


