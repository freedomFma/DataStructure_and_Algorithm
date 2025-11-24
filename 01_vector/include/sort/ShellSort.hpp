#pragma once
#include "../Vector.hpp"

// ============================================================
// ========  希尔排序  ==========
// ============================================================
template <typename T> void shellSort(Rank lo, Rank hi){
	for (Rank d = (hi - lo) / 2; d > 0; d >>= 1) {
		for (Rank j = lo + d; j < hi; j++) {
			T x = _elem[j];
			Rank i = j;
			while (i >= lo + d && x < _elem[i - d]) {
				_elem[i] = _elem[i - d];
				i -= d;
			}
			_elem[i] = x;
		}
	}
}