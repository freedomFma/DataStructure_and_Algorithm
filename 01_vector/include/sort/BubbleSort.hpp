#pragma once
#include "../Vector.hpp"

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


// ============================================================
// ===============    起泡排序 bubble sort    ===================
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











