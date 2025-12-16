#include "Vector.hpp"

template <typename T> void HeapSort(T* A, Rank lo, Rank hi){
	Rank n = hi -lo;
	heapify(A, n);
	
	while (0 < --n){
		swap(A[0], A[n]);
		percolateDown(A, n, 0);
	}
}

