#include <cstddef>
#include <cstring>
#define M 97
#define R 10
#define DIGIT(S, i) ((S)[i] - '0')//十进制串S的第i位的数字值
typedef long long HashCode;


bool check1by1(char* P, char* T, size_t i);
HashCode prepareDm(size_t m);
void updateHash(HashCode& hashT, char* T, size_t m, size_t k, HashCode Dm);

int match(char *P, char *T){
    size_t m = strlen(P), n = strlen(T);
    HashCode Dm = prepareDm(m), hashP = 0, hashT = 0;
    for(size_t i = 0; i<m;i++){
        hashP = ( hashP * R + DIGIT(P,i) ) % M;//P这个字符串对应一个指纹
        hashT = ( hashT * R + DIGIT(T,i) ) % M;//计算文本串的散列值
    }
    for(size_t k = 0; ; ){
        if(hashT == hashP)
            if (check1by1(P, T, k)) return k;
        if(++k > n-m) return k;//表示无匹配？？
        else updateHash(hashT, T, m,k, Dm);
    }
}

bool check1by1(char* P, char* T, size_t i){
    for(size_t m = strlen(P),j=0; j < m; j++,i++)
        if(P[j] != T[i]) return false;
    return true;
}

void updateHash(HashCode& hashT, char* T, size_t m, size_t k, HashCode Dm ){
    hashT = (hashT - DIGIT(T, k-1)* Dm) % M;
    hashT = (hashT* R+ DIGIT(T, k+m-1)) % M;
    if (0 > hashT) hashT += M;
}

HashCode prepareDm(size_t m){
    HashCode Dm = 1;
    for(size_t i = 1; i < m;i++){
        Dm = (R*Dm) % M;
    }
    return Dm; //这里得到的是R^{m-1} % 7 的值
}