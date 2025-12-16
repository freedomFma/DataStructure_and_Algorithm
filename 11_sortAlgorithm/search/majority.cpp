#include "Vector.hpp"
// ===================================================
// 选取众数(具有一半以上数量的元素被称作是一组数的众数)
// ---------------------------------------------------
// Boyer–Moore Majority Vote Algorithm（摩尔投票算法）。
// 它的正确性来自一个非常优美的「抵消」思想：
// 如果某个元素在数组中出现次数大于一半（多数元素），那么即使你不断用不同元素与它“配对并互相抵消”，
// 这个多数元素最终仍然会存活下来。
// ===================================================
template <typename T > T  majCandidate(Vector<T> A){
	T maj;
	
	for(Rank c = 0, i = 0; i < A.size(); i++){
		if(0 == c){
			maj = A[i];c=1;
		}
		else
			maj == A[i] ? c++ : c--;
	}

    return maj;
}


template <typename T> bool majority( Vector<T> A, T& maj ) { //众数查找算法：T可比较可判等
	maj = majCandidate( A ); //必要性：选出候选者maj
	return majCheck( A, maj ); //充分性：验证maj是否的确当选
}
template <typename T> T majCandidate( Vector<T> A ) { //选出具备必要条件的众数候选者
	T maj; //众数候选者
	// 线性扫描：借助计数器c，记录maj与其它元素的数量差额
	for ( Rank c = 0, i = 0; i < A.size(); i++ )
		if ( 0 == c ) { //每当c归零，都意味着此时的前缀P可以剪除
			maj = A[i]; c = 1; //众数候选者改为新的当前元素
		} else //否则
			maj == A[i] ? c++ : c--; //相应地更新差额计数器
	return maj; //至此，原向量的众数若存在，则只能是maj —— 尽管反之不然
}
template <typename T> bool majCheck ( Vector<T> A, T maj ) { //验证候选者是否确为众数
	Rank occurrence = 0; //maj在A[]中出现的次数
	for ( Rank i = 0; i < A.size(); i++ ) //逐一遍历A[]的各个元素
		if ( A[i] == maj ) occurrence++; //每遇到一次maj，均更新计数器
	return 2 * occurrence > A.size(); //根据最终的计数值，即可判断是否的确当选
}