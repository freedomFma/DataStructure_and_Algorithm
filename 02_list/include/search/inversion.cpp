#include <vector>
// 借助归并排序统计逆序对


int inversion_merge(std::vector<int>& nums, int left, int mid, int right){
    int inv_count = 0;
    int i = left, j = mid+1;
    std::vector<int> temp;

    while(i <= mid && j <= right){
        if(nums[i] <= nums[j])
            temp.push_back(nums[i++]);
        else{
            temp.push_back(nums[j++]);
            inv_count += (mid - i);//这里就统计完了
        }
    }
    while(i < mid) temp.push_back(nums[i++]);
    while(j < right) temp.push_back(nums[j++]);
    for(int k = left; k<= right; k++)
        nums[k] = temp[k - left];
    return inv_count;
}