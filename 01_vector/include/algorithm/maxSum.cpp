// 一个整数类型的向量A[0 , n)中最大的连续子序列的和

int maxSubSum(int A[],int n){
    int gsum = A[0];
    int sum = 0;

    for( int i = n - 1 , j = n; 0 <= i; i--){//子序列为[i ,j)
        sum += A[i];
        if(gsum < sum) gsum = sum;
        if(sum <= 0){
            sum = 0;
            j = i;
        }
    }
    return gsum;
}