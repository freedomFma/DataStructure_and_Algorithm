#include "./Dictionary.hpp"
#include "../00_bitmap/Bitmap.hpp"
#include "../05_BinSearchTree/Entry.hpp"

template <typename K, typename V> 
class Hashtable: public Dictionary<K, V> {
private:
    Entry<K,V>** ht; //指向词条的指针的指针. 桶数组，存放词条指针
    Bitmap* removed;
    Rank M, N;//桶的总数M，词条的总数N。（N+L)/M \leq lambda_max
protected:
    Rank probe4Hit(const K& k);
    Rank proe4Free(const K& k);
    void rehash();
public:
    Hashtable(Rank c = 5);
    ~Hashtable();//❓这里不需要释放数组吗？
    Rank size() const {return N;}
    bool put(K,V);
    V* get(K k);
    bool remove(K k);
};