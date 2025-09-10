#include "C++/DSA/02_list/List.hpp"
template <typename T> class Stack: public List<T>{
public://Vector里面的开放接口可以直接使用，比如size()\empty()
	void enqueue(T const& e){insetAsLast(e);}
	T dequeue() {return remove(first());}
	T& front() {return first()->data;}
};