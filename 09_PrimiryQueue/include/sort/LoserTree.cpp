#include <iostream>
#include <vector>
#include <climits> // INT_MAX

using namespace std;

// K 路败者树
class LoserTree {
private:
    vector<int> tree;      // 败者树数组，保存败者下标
    vector<int> leaves;    // 叶子节点数组（各路的当前值）
    int k;                 // 路数

    // 比较两条路径的元素大小
    int cmp(int i, int j) {
        return leaves[i] < leaves[j] ? i : j;
    }

public:
    LoserTree(const vector<int>& input) {
        k = input.size();
        leaves = input;
        tree.resize(k, -1); // 初始化败者树
        build();
    }

    // 建树
    void build() {
        for (int i = 0; i < k; ++i)
            adjust(i);
    }

    // 调整叶子节点 i
    void adjust(int s) {
        int t = (s + k) / 2;  // 父节点位置（树结构用数组实现）
        int parent = (s + k) / 2;

        int winner = s;
        int idx = parent;
        while (idx > 0) {
            if (tree[idx] == -1) {
                tree[idx] = winner;
                break;
            }
            int temp = tree[idx];
            tree[idx] = cmp(winner, tree[idx]);
            winner = temp;
            idx /= 2;
        }
        tree[0] = winner; // 根节点保存最终胜者
    }

    // 获取当前最小元素的下标
    int getWinner() const {
        return tree[0];
    }

    // 更新某路的值（如归并时取下一元素）
    void update(int idx, int value) {
        leaves[idx] = value;
        adjust(idx);
    }

    // 获取叶子节点的值
    int getValue(int idx) const {
        return leaves[idx];
    }
};

int main() {
    // 测试：三路归并
    vector<int> arr = {4, 7, 2};
    LoserTree lt(arr);

    cout << "初始败者树胜者下标: " << lt.getWinner() << endl;

    // 模拟归并过程
    for (int i = 0; i < 5; ++i) {
        int w = lt.getWinner();
        cout << "当前最小值: " << lt.getValue(w) << endl;
        // 取下一元素，用 INT_MAX 表示结束
        lt.update(w, INT_MAX);
    }

    return 0;
}