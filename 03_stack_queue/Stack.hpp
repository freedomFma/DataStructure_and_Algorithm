#include "C++/DSA/01_vector/Vector.hpp"
template <typename T> class Stack: public Vector<T>{
public://Vector里面的开放接口可以直接使用，比如size()\empty()
	void push(T const& e){inset(e);}
	T pop() {return remove(size() - 1);}
	T &top() {return (*this)[size() - 1];}
};