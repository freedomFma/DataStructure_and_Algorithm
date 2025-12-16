#include <vector>
#include <numeric>


struct QuickFindUF {
    std::vector<int> id;
    QuickFindUF(int n) : id(n) { std::iota(id.begin(), id.end(), 0); }

    int find(int x) const { return id[x]; }
    bool connected(int a, int b) const { return id[a] == id[b]; }
    // O(n)
    void unite(int a, int b) {
        int pa = id[a], pb = id[b];
        if (pa == pb) return;
        for (int i = 0; i < (int)id.size(); ++i)
            if (id[i] == pb) id[i] = pa;
    }
};

struct UnionFind {
    std::vector<int> parent, sz;
    UnionFind(int n) : parent(n), sz(n, 1) { std::iota(parent.begin(), parent.end(), 0); }
  
    int find(int x) {      // 路径压缩（递归版）
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int a, int b){ // 按大小合并
        int ra = find(a), rb = find(b);
        if (ra == rb) return false;
        if (sz[ra] < sz[rb]) std::swap(ra, rb);
        parent[rb] = ra;
        sz[ra] += sz[rb];
        return true;
    }
    bool connected(int a, int b) { return find(a) == find(b); }
};