#include <vector>
#include <unordered_map>

int mode(std::vector<int>& A){
    std::unordered_map<int,int> cnt;
    for (int i = 0; i < A.size(); ++i) {
        int x = A[i];
        cnt[x]++;
    }

    // 众数是什么，相应的次数是多少
    // 改成散列表的形式，桶的大小完全可以是最大的数字 - 最小的数字，不会有任何的冲突，而且满桶
    int mode = A[0], maxFreq = 0;
    for (auto it = cnt.begin(); it != cnt.end(); ++it) {
        if (it->second > maxFreq) {
            maxFreq = it->second;
            mode = it->first;
        }
    }
    return mode;
}