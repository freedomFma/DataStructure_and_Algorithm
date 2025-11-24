#pragma once
#include "../Vector.hpp"

//-------  斐波那契数查找算法   -------
//----------------------------------
// [1]中点计算改为斐波那契数计算
// [2]区间的比较与二查找到第一个版本相同
//----------------------------------
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
template <typename T>  
Rank fibSearch (T* A, T const& e, Rank lo, Rank hi){
	Fib fib(hi-lo);
	while(lo < hi){
		Rank mi = lo +fib.prev()-1;
		if (e < A[mi]) hi = mi;
		else if (A[mi]< e) lo = mi+1;
		else return mi;
	}
	return -1;
}