#pragma once
#include "Vector.hpp"

// ============================================================
// =================  快速排序 quick sort =======================
// ============================================================
// 时间复杂度
// 最好:O(nlogn)
// 最差:O(n^2)——有序(正序或者逆序) + 简单选取左端元素作为轴点
// 平均:O(nlogn)
//-----------------
// 空间复杂度
// 递归平均空间O(nlogn)
// 最差:O(n)
// 迭代O(logn)
// ---------------
// 不稳定（稳定：相等的数字一开始在前的那个在排完序之后依然在前）
// 归位（除了最后一趟，之前的每一趟至少能够有一个元素在它最终所应该在的位置上）轴点归位
// 三者取中
// LUG DUP LGU
// ============================================================

//----------------------------------
// [1]快速排序的递归实现 
//----------------------------------
template <typename T> void quickSort_v1 ( Rank lo, Rank hi ){//快速排序算法
	if(hi - lo < 2 ) return;//递归基，子集只有一个元素
	Rank mi = partition(lo, hi);//选取轴点
	quickSort_v1(lo, mi);//递归实现
	quickSort_v1(mi+1, hi);//递归实现
}
//----------------------------------
// [2]快速排序的非递归实现
//----------------------------------
#define Put(K ,s, t) {if (1<(t) - (s)) {K.push(s); K.push(t)}}//t比s大：s先进，t后进，t在顶
#define Get(K ,s, t) {t = K.pop(); s = K.pop();} //t在顶先出，s在下后出
template <typename T> class Stack;//前向声明
template <typename T> void quickSort_v2(Rank lo, Rank hi){
	Stack<Rank> Task;//
	Put(Task, lo, hi);
	while(!Task.empty){
		Get(Task, lo, hi); //大在顶先出，先给hi赋值，再给lo赋值
		Rank mi = partition(lo, hi);
		if(mi - lo < hi -mi){
			Put(Task, mi+1, hi); //mi+1,hi 先进
			Put(Task ,lo, mi); //
		}
		else{
			Put(Task ,lo, mi);//大任务先进：左边大
			Put(Task, mi+1, hi);
		}//大任务先进栈，小任务先出栈
	}
}

//----------------------------------
// [1]轴点构造
//----------------------------------
template <typename T> Rank  partition ( Rank lo, Rank hi ){ 
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
//----------------------------------
// [2]轴点构造（随机版）
//----------------------------------
template <typename T> Rank partition(Rank lo, Rank hi){
	swap(_elem[lo], _elem[lo+std::rand()%(hi-lo)]);//随机抽取作为轴点
	T pivot = _elem[lo];//取出轴点作备份

	Rank mi = lo;
	for(Rank k = lo+1; k < hi; k++){
		if(_elem[k] < pivot){
			swap(_elem[++mi],_elem[k]);
		}
	}
	swap(_elem[lo], _elem[mi]);
	return mi;
}

