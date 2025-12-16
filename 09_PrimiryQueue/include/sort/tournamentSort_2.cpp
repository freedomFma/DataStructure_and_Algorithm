// tournament_sort.cppm
// gcc15.1.0编译通过
// export module tournament_sort;

#include <vector>
#include <iostream>
#include <limits>
#include <utility>

// 胜者树节点结构
struct Node {
    int value;   // 存储的值
    int index;   // 在原始数组中的位置（用于保持稳定性）
};

// 选择胜者（较小的节点，值相等时选择索引小的）
Node selectWinner(const Node& left, const Node& right) {
    if (left.value < right.value) {
        return left;
    } else if (left.value > right.value) {
        return right;
    } else {
        // 值相等时，选择原始位置靠前的（保持稳定性）
        return (left.index < right.index) ? left : right;
    }
}


// 锦标赛排序实现
//export
void tournamentSort(std::vector<int>& arr) {
    const int n {static_cast<int>(arr.size())} ;
    if (n < 2) return;
    std::vector<Node> tree(2 * n - 1);
    
    // 初始化叶子节点
    for (int i {0} ; i < n; i++) {
        tree[n - 1 + i] = {arr[i], i};
    }
    
    // 构建初始胜者树
    for (int i {n - 2} ; i >= 0; i--) {
        auto [left, right] = std::pair(2 * i + 1, 2 * i + 2);
        tree[i] = selectWinner(tree[left], tree[right]);
    }
    
    // 排序阶段
    for (int i {0} ; i < n; i++) {
        arr[i] = tree[0].value;  // 当前最小值
        
        // 定位到对应的叶子节点并标记为"淘汰"
        int node {tree[0].index + n - 1} ;
        tree[node].value = std::numeric_limits<int>::max();
        
        // 向上调整胜者树
        while (node > 0) {
            node = (node - 1) / 2;
            auto [left, right] = std::pair(2 * node + 1, 2 * node + 2);
            tree[node] = selectWinner(tree[left], tree[right]);
        }
    }
}