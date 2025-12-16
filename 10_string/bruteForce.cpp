#include <string.h>

int match(char* P, char* T){
	int n = strlen(T), i = 0;
	int m = strlen(P), j = 0;
	
	while((j < m) && (i < n)){
		if (T[i] == P[j]) {i++;j++;}
		else {i -= j - 1; j = 0;}
	}
	
	return i - j;
}

int match(char* P, char* T){
	int n = strlen(T), i;
	int m = strlen(P), j;
	
	for(i = 0; i+m <= n; i++){
		for(j = 0; j < m ;j++)
			if(T[i+j] != P[j]) break;
		if(j >= m) break;
	}
	
	return i;
}