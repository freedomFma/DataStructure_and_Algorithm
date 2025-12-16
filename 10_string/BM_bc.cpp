#include <string>
#include <iostream>
#include <cstring>
#include <algorithm>

// 创建bc表：时间复杂度是O(m+256)
int* buildBC(char* P){
	int* bc = new int[256];
	for(size_t j = 0; j<256;j++)
		bc[j] = -1;
	
	for(size_t m = strlen(P), j = 0; j < m; j++){
		bc[ P[j] ] = j;
	}
	return bc;
}

// bc坏字符匹配策略
int match(char* P, char* T){
	int* bc = buildBC(P);
	int n = strlen(T) , i;
	int m = strlen(P) , j;
	
    //j - bc[ T[i+j] ] 得到的是P要往后拽的距离，也就是i需要前进的距离
	for (i = 0; i + m <= n; i += std::max(1, j - bc[ T[i+j] ])){
		for (j = m - 1; (0 <= j) && (P[j] == T[i+j]); j--);
		if(j < 0) break;//匹配完成
	}
	
	delete[] bc;
	return i;
}
//时间复杂度最好的情况下是O(n/m+m)
//最差的情况下可能达到O(nm)