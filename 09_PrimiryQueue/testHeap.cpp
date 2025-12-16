#include "PQ.hpp"

template <typename PQ, typename T>void testHeap(int n){
	T* A = new T[2*n/3];
	for(int i = 0; i < 2*n/3; i++)
		A[i] = dice((T) 3*n);
		
	PQ heap(A+n/6, n/3); delete [] A;
	
	while(heap.size() < n){
		if (dice (100) <70) 
			heap.insert( dice( (T) 3*n) );
		else if(! heap.empty())
			heap.delMax();
	}
	while (! heap.empty() ) heap.delMax();
}