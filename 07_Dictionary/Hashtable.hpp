#include "./Dictionary.hpp"
#include "../00_bitmap/Bitmap.hpp"
#include "../05_BinSearchTree/Entry.hpp"

template <typename K, typename V> 
class Hashtable: public Dictionary<K, V> {
private:
    Entry<K,V>** ht; //指向词条的指针的指针. 桶数组，存放词条指针
    Bitmap* removed;
    Rank M, N;//桶的总数M，词条的总数N。装填因子（N+L)/M \leq lambda_max
protected:
    Rank probe4Hit(const K& k);
    Rank probe4Free(const K& k);
    Rank probe4Hit_sqr(const K& k);
    Rank probe4Free_sqr(const K& k);
    Rank probe4Hit_2sqr(const K& k);
    Rank probe4Free_2sqr(const K& k);
    void rehash();
public:
    Hashtable(Rank c = 5);
    ~Hashtable();//❓这里不需要释放数组吗？
    Rank size() const {return N;}
    bool put(K,V);
    V* get(K k);
    bool remove(K k);
};

// ============================================================
// ======================  线性试探：两种试探  ===================
// [1]probe4Hit(k)  为了查找：寻找命中桶  =========================
// [2]probe4Free(k) 为了插入：寻找空闲桶  =========================
// ============================================================
//----------------------
// [1] 线性试探
//----------------------
template <typename K, typename V>
Rank Hashtable<K, V>::probe4Hit(const K& k){
	for(Rank r = hashCode(k) % M; ; r = (r+1)%M)//散列函数映射 + 线性试探
		if( ht[r] && (k == ht[r]->key) || !ht[r] && !removed->test(r))//命中，或者 失败(非懒惰删除的空桶).这使得删除后的桶不打乱线性试探链
			return r;//要么它就在这里，要么它查找失败
}
template <typename K, typename V>
Rank Hashtable<K, V>::probe4Free(const K& k){
	for(Rank r = hashCode(k) % M; ; r = (r+1)%M )//散列函数映射 + 线性试探
		if(!ht[r])//找到一个没有存放数据的桶（这里可以是懒惰删除的）
			return r;//直接返回这个秩
}
//----------------------
// [2] 单向平方试探
//----------------------
template <typename K, typename V>
Rank Hashtable<K, V>::probe4Hit_sqr(const K& k){
    Rank r = hashCode(k) % M;//首先确定其第一个位置
    for(Rank i = 1, cont = 0; cont <= M/2 + 1 ; i++, cont++){ // 最多探测M/2+1次(保证M为4k+3质数 且 装填因子小于等于0.5)
        if( ht[r] && (k == ht[r]->key) || !ht[r] && !removed->test(r))//命中，或者 失败(非懒惰删除的空桶).这使得删除后的桶不打乱线性试探链
            return r;//要么它就在这里，要么它查找失败
        r = (R + (i*i)) % M;//正向平方试探
    }
    //注意⚠️这里只要保证M为4k+3质数 且 装填因子小于等于0.5，就一定能找到空桶，
    //因为试探的数量M/2+1，这个数量总是大于半个散列表的大小，同时整个散列表的装填因子小于0.5，所以一定能够找到
    return -1; //查找失败
}

template <typename K, typename V>
Rank Hashtable<K, V>::probe4Free_sqr(const K& k){
	Rank r = hashCode(k) % M;//首先确定其第一个位置
    for(Rank i = 1, cont = 0; cont <= M/2 + 1 ; i++, cont++){ // 最多探测M/2+1次(保证M为4k+3质数 且 装填因子小于等于0.5)
        if( !ht[r])//找到一个没有存放数据的桶（这里可以是懒惰删除的）
            return r;
        r = (R + (i*i)) % M;//正向平方试探
    }
    return -1; //查找失败
}

//----------------------
// [3] 双向平方试探
//----------------------
template <typename K, typename V>
Rank Hashtable<K, V>::probe4Hit_2sqr(const K& k) {
    Rank r0 = hashCode(k) % M;  
    Rank r = r0;

    // 探测次数最多 M/2 + 1 （要求 M 是 4k+3 的质数 且 装载因子 <= 0.5）
    for (Rank i = 1, cnt = 0; cnt <= M / 2 + 1; cnt++) {

        // 命中，或失败（遇到真正空桶且非懒删除）
        if ( (ht[r] && (k == ht[r]->key)) || (!ht[r] && !removed->test(r)) )
            return r;

        // 计算偏移量
        Rank delta = i * i;

        if (cnt % 2 == 0) {
            // 偶数轮：正向偏移
            r = (r0 + delta) % M;
        } else {
            // 奇数轮：反向偏移，并结束这一对（正负）后 i++
            r = (r0 + M - (delta % M)) % M;
            i++;
        }
    }

    // 如果超过最大次数还没找到，宣告失败
    return -1;
}

template <typename K, typename V>
Rank Hashtable<K, V>::probe4Free_2sqr(const K& k) {
    Rank r0 = hashCode(k) % M;  
    Rank r = r0;

    // 探测次数最多 M/2 + 1 （要求 M 是 4k+3 的质数 且 装载因子 <= 0.5）
    for (Rank i = 1, cnt = 0; cnt <= M / 2 + 1; cnt++) {

        // 命中，或失败（遇到真正空桶且非懒删除）
        if (!ht[r])
            return r;

        // 计算偏移量
        Rank delta = i * i;

        if (cnt % 2 == 0) {
            // 偶数轮：正向偏移
            r = (r0 + delta) % M;
        } else {
            // 奇数轮：反向偏移，并结束这一对（正负）后 i++
            r = (r0 + M - (delta % M)) % M;
            i++;
        }
    }

    // 如果超过最大次数还没找到，宣告失败
    return -1;
}


// ============================================================
// ======================  删除和插入  ==========================
// ============================================================

//----------------------
// [1] remove(k) 删除算法
//----------------------
template <typename K, typename V> 
bool Hashtable<K, V>::remove(K k){
	Rank r = probe4Hit(k);//找到命中桶
	if(!ht[r]) return false;//如果命中桶为空,说明查找链找到了最后，没有相应关键码
	
	delete ht[r];
	ht[r] = NULL;
	--N;
	removed->set(r);
	
	return true;
}

template <typename K, typename V> 
bool Hashtable<K, V>::put(K k, V v){
	if( ht[probe4Hit(k)] ) return false;//如果存在元素相等的桶，失败
	Rank r = probe4Free(k);//找位置
	
	//新建词条
	ht[r] = new Entry<K, V>(k, v);
	++N;
	remove->clear(r);
	
	if( (N+removed->size())*2  > M)//存的数据+懒惰删除
		rehash();
	return true;
}


// ============================================================
// ======================  重散列（扩容）  ==========================
// =============================================================

template <typename K, typename V>
void Hashtable<K, V>::rehash(){
	Rank oldM = M;//桶数
	Entry<K, V>** oldHt = ht;//散列表数组
    //--------------------------------
    //创建新的散列表
	ht = new Entry<K, V>*[ M = primeNLT(4*N) ];
	N = 0;
	memset( ht, 0, sizeof( Entry<K, V>*) * M );
	
	delete removed;
	removed = new Bitmap(M);
	
	for(Rank i =0; i< oldM; i++){
		if(oldHt[i])
			put( oldHt[i]->key, oldHt[i]->value);//重新插入一遍！
	delete[] oldHt;
	}
}