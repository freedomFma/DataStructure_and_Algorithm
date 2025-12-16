#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int maximumGap(vector<int>& nums) {
    int n = nums.size();
    if (n < 2) return 0;

    int mn = *min_element(nums.begin(), nums.end());
    int mx = *max_element(nums.begin(), nums.end());
    if (mn == mx) return 0;

    // 每个桶的大小（至少为1）
    int bucketSize = max(1, (mx - mn) / (n - 1));
    int bucketNum = (mx - mn) / bucketSize + 1;

    struct Bucket {
        int bmin = INT_MAX;
        int bmax = INT_MIN;
        bool used = false;
    };

    vector<Bucket> buckets(bucketNum);

    // 将每个数放入桶中
    for (int x : nums) {
        int idx = (x - mn) / bucketSize;
        buckets[idx].used = true;
        buckets[idx].bmin = min(buckets[idx].bmin, x);
        buckets[idx].bmax = max(buckets[idx].bmax, x);
    }

    // 扫描桶，计算最大 gap
    int prevMax = mn;
    int ans = 0;

    for (int i = 0; i < bucketNum; i++) {
        if (!buckets[i].used) continue; // 空桶跳过
        ans = max(ans, buckets[i].bmin - prevMax);
        prevMax = buckets[i].bmax;
    }

    return ans;
}