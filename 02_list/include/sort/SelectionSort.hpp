#pragma once
#include "List.hpp"

// ============================================================
// ===============    选择排序 select sort    ===================
// ============================================================
// 时间复杂度
// 最好:O(n^2)
// 最差:O(n^2)
// 平均:O(n^2)
//-----------------
// 空间复杂度
// O(1)就地算法
// ---------------
// 不稳定（相等的数字一开始在前的那个在排完序之后处于最后：从左到右查找最大的数字）
// 归位（除了最后一趟，之前的每一趟至少能够有一个元素在它最终所应该在的位置上）最大数字归位
// ============================================================

template <typename T> void List<T>::selectSort( ListNodePosi(T) p, Rank n){
	ListNodePosi(T) h = p->pred;//h是head
	ListNodePosi(T) t = p;
	for(Rank i = 0; i < n; i++) 
		t = t->succ;//循环结束的时候t是Rank n的后一个
	while(1 < n) {//迭代n-1次
		insert( remove(selectMax(h->succ , n)), t )//在t之前插入
		t = t->pred; n--;
	}
}

template <typename T>//从起始于p的n个元素中选取最大者
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, Rank n){
	LisiNodePosi(T) max = p;
	for( ListNodePosi(T) cur = p; 1 < n; n-- )//迭代n-1次
		if( !( (cur = cur->succ)->data < max->data) )
			max = cur;
	return max;
}
