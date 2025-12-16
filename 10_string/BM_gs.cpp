#include <string>
#include <iostream>
#include <cstring>
#include <algorithm>

int* buildSS(char* P){
	int m = strlen(P);//待匹配的字符串的长度
	int* ss = new int[m]; //构造长度为m的ss表
	
	ss[m-1] = m;//最后一个字符与之匹配的最长后缀就是整个P串
	
	for(int lo = m-1, hi = m - 1,j = lo - 1; j >=0 ;j--){
		if( (lo<j) && (ss[m-hi+j-1] <= j - lo) )
			ss[j] = ss[m - hi + j - 1];
		else{
			hi = j;
			lo = std::min(lo ,hi);
			while((0 <= lo) && (P[lo] == P[m-hi+lo-1]) )
				lo--;
			ss[j] = hi -lo;
		}
	}
	return ss;
}

int* buildGS(char* P){
	int* ss = buildSS(P);
	size_t m = strlen(P); int* gs = new int[m];
	for(size_t j = 0; j < m; j++){
		gs[j] = m;
	}
	for(size_t i = 0,j = m-1; j< UINT_MAX; j--){
		if(j+1 == ss[j]){
			while (i < m - j - 1)
				gs[i++] = m-j-1;
		}
	}
	for( size_t j = 0; j<m-1;j++){
		gs[m - ss[j] -1] = m-j -1;
	}
    delete [] ss;
    return gs;
}