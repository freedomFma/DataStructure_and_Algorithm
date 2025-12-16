#pragma once
#include "Vector.hpp"
// ============================================================
// ===============    起泡排序 bubble sort    ===================
// ============================================================
// 时间复杂度
// 最好:O(n)
// 最差:O(n^2)
// 平均:O(n^2)
//-----------------
// 空间复杂度
// O(1)就地算法
// ---------------
// 不稳定（相等的数字一开始在前的那个在排完序之后依然在前）
// 归位（除了最后一趟，之前的每一趟至少能够有一个元素在它最终所应该在的位置上）最大泡归位
// ============================================================

template <typename T> 
bool bubble_v1(Rank lo, Rank hi){//如果一开始就是
	bool sorted = true;
	while(++lo < hi){
		if(_elem[lo - 1] > _elem[lo]){
			swap(_elem[lo-1],_elem[lo]);
			sorted = false;
		}
	}
	return sorted;
}

template <typename T> 
void bubbleSort_v1(Rank lo, Rank hi){
	while(!bubble_v1(lo,hi--));
}



template <typename T>
void bubbleSort_v2(Rank lo, Rank hi){
	while(lo < (hi = bubble_v2(lo, hi))-1);
}
template <typename T> 
Rank bubble_v2(Rank lo, Rank hi){
	Rank last = lo;
	while(++lo < hi){
		if(_elem[lo - 1] > _elem[lo]){
			swap(_elem[lo-1],_elem[lo]);
			last = lo;
		}
	}
	return last;
}











