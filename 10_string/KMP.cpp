#include <string>
#include <iostream>
#include <cstring>

//构建next表
int* buildNext(const char* P){
	int m = strlen(P), j = 0;
	int* next = new int[m];
	
	int t = next[0] = -1;
	while(j < m - 1){
		if(0 > t || P[t] == P[j]){
			++t; ++j;
			next[j] = t;
		}
		else{
			t = next[t];
		}
	}
	return next;
}

//KMP算法
int match(const char *P, const char* T){
	int* next  = buildNext(P);
	int n = (int) strlen(T), i = 0;
	int m = (int) strlen(P), j = 0;
	while( (j<m) && (i<n) ){
		if( 0 > j || T[i] == P[j]){
			i++;j++;
		}
		else{
			j = next[j];
		}
	}
	delete [] next;
	if(j == m) return i - j;//第一次匹配成功的第一个字母的地方
    return -1;
}

int main(){
    const char* P = "MASHUTING";
    const char* T = "TSINGHUA";
    int pos = match(P, T);
    if(pos >= 0)
        std::cout << "match at " << pos << ", first char of pattern: " << P[0] << '\n';
    else
        std::cout << "no match\n";
}