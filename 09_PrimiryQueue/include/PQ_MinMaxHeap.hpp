#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class MinMaxHeap {
private:
    vector<int> H; // 0-based

    // 偶数层为小堆层，奇数层为大堆层
    // 判断是否为 min level（层号从 0 开始）
    bool isMinLevel(int i) {
        return ((int)log2(i + 1)) % 2 == 0;
    }

    // 交换并返回索引
    inline void swapNode(int i, int j) {
        std::swap(H[i], H[j]);
    }

    // 上滤（min level）
    void bubbleUpMin(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            int gp = (p - 1) / 2;
            if (i > 2 && H[i] < H[gp]) {
                swapNode(i, gp);
                i = gp;
            } else break;
        }
    }

    // 上滤（max level）
    void bubbleUpMax(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            int gp = (p - 1) / 2;
            if (i > 2 && H[i] > H[gp]) {
                swapNode(i, gp);
                i = gp;
            } else break;
        }
    }

    // 插入后的上滤
    void bubbleUp(int i) {
        if (i == 0) return;
        int p = (i - 1) / 2;

        if (isMinLevel(i)) {
            if (H[i] > H[p]) {
                swapNode(i, p);
                bubbleUpMax(p);
            } else {
                bubbleUpMin(i);
            }
        } else {
            if (H[i] < H[p]) {
                swapNode(i, p);
                bubbleUpMin(p);
            } else {
                bubbleUpMax(i);
            }
        }
    }

    // 下滤（min level）
    void trickleDownMin(int i) {
        while (true) {
            int m = -1;
            int n = H.size();
            int l = 2*i+1, r = 2*i+2;

            // 寻找孩子 + 孙子中的最小者
            vector<int> cand;

            if (l < n) cand.push_back(l);
            if (r < n) cand.push_back(r);

            int ll = 2*l+1, lr = 2*l+2;
            int rl = 2*r+1, rr = 2*r+2;

            if (ll < n) cand.push_back(ll);
            if (lr < n) cand.push_back(lr);
            if (rl < n) cand.push_back(rl);
            if (rr < n) cand.push_back(rr);

            if (cand.empty()) return;

            m = cand[0];
            for (int c : cand) if (H[c] < H[m]) m = c;

            // 如果 m 是孙子
            if (m >= 4*i+3) {
                if (H[m] < H[i]) {
                    swapNode(m, i);
                    int p = (m - 1) / 2;
                    if (H[m] > H[p]) swapNode(m, p);
                    i = m;
                } else return;
            } else { // m 是孩子
                if (H[m] < H[i]) swapNode(m, i);
                return;
            }
        }
    }

    // 下滤（max level）
    void trickleDownMax(int i) {
        while (true) {
            int m = -1;
            int n = H.size();
            int l = 2*i+1, r = 2*i+2;

            vector<int> cand;

            if (l < n) cand.push_back(l);
            if (r < n) cand.push_back(r);

            int ll = 2*l+1, lr = 2*l+2;
            int rl = 2*r+1, rr = 2*r+2;

            if (ll < n) cand.push_back(ll);
            if (lr < n) cand.push_back(lr);
            if (rl < n) cand.push_back(rl);
            if (rr < n) cand.push_back(rr);

            if (cand.empty()) return;

            m = cand[0];
            for (int c : cand) if (H[c] > H[m]) m = c;

            // 孙子
            if (m >= 4*i+3) {
                if (H[m] > H[i]) {
                    swapNode(m, i);
                    int p = (m - 1) / 2;
                    if (H[m] < H[p]) swapNode(m, p);
                    i = m;
                } else return;
            } else { // 孩子
                if (H[m] > H[i]) swapNode(m, i);
                return;
            }
        }
    }

    void trickleDown(int i) {
        if (isMinLevel(i)) trickleDownMin(i);
        else trickleDownMax(i);
    }

public:
    MinMaxHeap() {}

    bool empty() const { return H.empty(); }
    int size() const { return H.size(); }

    int top_min() { return H[0]; }

    int top_max() {
        if (H.size() == 1) return H[0];
        if (H.size() == 2) return H[1];
        return max(H[1], H[2]);
    }

    void push(int x) {
        H.push_back(x);
        bubbleUp(H.size() - 1);
    }

    void pop_min() {
        if (H.size() <= 1) { H.pop_back(); return; }
        H[0] = H.back();
        H.pop_back();
        trickleDown(0);
    }

    void pop_max() {
        if (H.size() <= 1) { H.pop_back(); return; }
        int m = (H.size() == 2 || H[1] > H[2]) ? 1 : 2;
        H[m] = H.back();
        H.pop_back();
        trickleDown(m);
    }
};