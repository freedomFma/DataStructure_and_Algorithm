#include "Vector.hpp"
#include <cstdlib>
#include <iostream>


//简单的互异整数的情况：n<m
template <typename T>
void bucketSort(Vector<T> &A){
    //建立向量表
    Rank n = A.size();
    Rank m = n+1; //桶的数量，装填因子0.5

    //初始化哈希表，全部初始化为0
    Vector<T> B;
    for(Rank i = 0; i < m; i++){
        B.insert(i , 0);
    }
    //将元素放入对应的桶中
    for (Rank i = 0; i < n; i++){
        Rank index = A[i] % m;
        B[index] = 1;
    }

    //遍历桶，回写排序结果
    for(Rank i = 0; i < m; i++){
        if(B[i]) std::cout << i << " ";
    }
}

int main(){
    Vector<int> A;
    A.insert(0,29);
    A.insert(1,25);
    A.insert(2,3);
    A.insert(3,49);
    A.insert(4,9);
    A.insert(5,37);
    A.insert(6,21);
    A.insert(7,43);
    A.insert(8,11);
    A.insert(9,15);

    bucketSort(A);
}