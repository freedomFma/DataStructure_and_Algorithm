#include <iostream>
#include <vector>
#include <climits>  // INT_MAX

using namespace std;

class WinnerTree {
private:
    vector<int> leaves; // 存储元素
    vector<int> tree;   // 存储胜者索引
    int n;

    // 更新从叶子到根的胜者
    void adjust(int leaf) {
        int parent = (leaf + n) / 2;
        while (parent > 0) {
            int left = tree[parent * 2 - n];  // 左子节点索引
            int right = tree[parent * 2 + 1 - n]; // 右子节点索引
            tree[parent] = (leaves[left] <= leaves[right]) ? left : right;
            parent /= 2;
        }
    }

public:
    WinnerTree(const vector<int>& data) {
        n = data.size();
        leaves = data;
        tree.resize(n); // 非叶节点个数 = n - 1，但为了方便从1开始索引，直接用n
        build();
    }

    void build() {
        // 初始化叶子节点对应的索引
        for (int i = 0; i < n; i++) tree[i] = i;

        // 从最后一个叶子向上调整
        for (int i = n - 1; i > 0; i--) {
            adjust(i);
        }
    }

    // 获取当前最小值
    int getMin() {
        return leaves[tree[1]]; // 根节点索引
    }

    // 删除当前最小值并更新
    void deleteMin() {
        int minIndex = tree[1];
        leaves[minIndex] = INT_MAX; // 标记为无穷大
        adjust(minIndex);
    }

    void printLeaves() {
        for (int x : leaves) cout << x << " ";
        cout << endl;
    }
};

int main() {
    vector<int> data = {20, 15, 30, 5, 10};
    WinnerTree wt(data);

    cout << "初始叶节点: ";
    wt.printLeaves();

    cout << "最小值: " << wt.getMin() << endl;

    cout << "删除最小值后: " << endl;
    wt.deleteMin();
    wt.printLeaves();
    cout << "新最小值: " << wt.getMin() << endl;

    return 0;
}