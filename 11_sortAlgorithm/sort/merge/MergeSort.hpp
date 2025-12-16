#pragma once
#include "Vector.hpp"
#include "List.hpp"

// ============================================================
// ==============    归并排序 merge sort   ======================
// ============================================================
// 时间复杂度
// 最好:O(nlogn)
// 最差:O(nlogn)
// 平均:O(nlogn)
//-----------------
// 向量空间复杂度
// 向量O(n). 虽然在每一层递归中，较大的那一层只申请了 n/2，但是：
//•	第 0 层：申请 n/2
//•	第 1 层：两个子区间，各申请 n/4
//•	第 2 层：四个子区间，各申请 n/8 ....
//•	最底层：很多区间申请小空间
//-----------------
// 列表空间复杂度
// 列表O(logn)
// 递归调用栈的深度，每一层递归只保存局部的变量
// ---------------
// 稳定 A[i++] = ( B[j] <= C[k] ) ? B[j++] : C[k++];
// 不归位
// ============================================================


//----------------------------------
// [1]向量的归并排序
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
	//合并之后的有序向量
	Rank i = 0; T* A = _elem + lo; //合并后的有序向量A[0, hi - lo) = _elem[lo, hi)
	
	//前半段子向量
	Rank j = 0, lb = mi - lo; 
	T* B = new T[lb]; //前子向量B[0, lb) <-- _elem[lo, mi)
	for ( Rank i = 0; i < lb; i++ ) 
		B[i] = A[i]; //复制出A的前缀

	//后半段子向量
	Rank k = 0, lc = hi - mi; 
	T* C = _elem + mi; //后缀C[0, lc) = _elem[mi, hi)就地

	while ( ( j < lb ) && ( k < lc ) ) //反复地比较B、C的首元素
		A[i++] = ( B[j] <= C[k] ) ? B[j++] : C[k++]; //将更小者归入A中 （相等的数字左边的优先被选择）
	while ( j < lb ) //若C先耗尽，则 
		A[i++] = B[j++]; //将B残余的后缀归入A中
	//——若B先耗尽:C原本就位于A之中，故已经排好序
	delete[] B; //释放临时空间：mergeSort()过程中，如何避免此类反复的new/delete？ 
}
//空间复杂度，


//----------------------------------
// [2]列表的归并排序
//----------------------------------
template <typename T> 
void List<T>::mergeSort(ListNodePosi(T)&p, Rank n){
	if(n < 2) return;//只有一个节点的时候返回
	ListNodePosi(T) q = p; 
	Rank m = n >> 1;//找到中点位置，这个位置是列表靠右的一个位置
	
	for(Rank i = 0; i < m; i++) q = q->succ;//此时的q就是“秩”为m的那个节点
	mergeSort(p , m); mergeSort(q, n-m);//递归的对子序列进行排序
	p = merge(p, m, *this, q, n-m);// 归并
}

template <typename T> ListNodePosi(T)
List<T>::merge(ListNodePosi(T) p, Rank n, List<T>& L, ListNodePosi(T) q, Rank m){
	ListNodePosi(T) pp = p->pred;//归并之后p或许不再指向head，所以需要先记忆，便于返回前更新
	while ( (0 < m) && (q != p) ){//总长度非空，而且左段第一个节点不等于右段第一个节点（p第一个节点，q中间节点。
		if((0 < n) && (p->data <= q->data)){//左段非空，左边的“当前数据”小于右边的“当前数据”，左边的指针往右移
			p = p->succ;
			n--;
		}
		else{//右段的当前数据更小，那么就在p指针为之前插入右段的首节点数据
			insert( L.remove((q = q->succ)->pred), p);
		}
	}
	return pp->succ;//返回第一个节点的位置
}