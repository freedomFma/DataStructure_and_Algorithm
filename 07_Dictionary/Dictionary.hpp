
template <typename K, typename V>
struct Dictionary{
    virtual Rank size() = 0;
    virtual bool put(K, v) = 0;
    virtual V* get(K) = 0;
    virtual bool remove(K) = 0;
};