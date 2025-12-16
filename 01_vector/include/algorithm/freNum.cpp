//有序向量的频繁数

int freNum(int* A, int A_size){
	int freNum = A[0];
	int num = A[0];
	int count = 1;
	int gcount = 0;
	
	for(int i = 1; i < A_size; i++){
		if(A[i] == num) {
			count++;
		}
		else{
			num = A[i];
			count = 1;
		}
		if(gcount < count){
				gcount = count;
				freNum = num;
		}
	}
	return freNum;
}