#include <algorithm>
// 寻找一个数组中，连续的相同数字的和等于s的，最长子数组的长度。
// 比如 A = {1,1,2,1,1,1,2,1} s = 3，返回3

int seekMax(int s, int* A, int A_size){
    // 三个变量：记录最大的长度、相同的数字、相同数字和
    int length = 0;
    int num = A[0];
    int sum = 0;

    // 循环数组的长度次数，一遍过去，迭代n次
    for(int i = 0; i < A_size; i++){
        if(A[i] == num){
            sum += num;
            if(sum == s) 
                return length = std::max(length, sum / num);
        }
        else{
            num = A[i];
            sum = A[i];
        }
    }
    return length;
}