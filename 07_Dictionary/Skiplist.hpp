#include "./Dictionary.hpp"
#include "../02_list/List.hpp"
#include "./Quadlist.hpp"
template <typename K, typename V> struct Skiplist:
public Dictionary<K, V>, public List<Quadlist<Entry<K,V>>*>{
    Skiplist() { insertFirst( new Quadlist < Entry<K, V> > ); }
	QNodePosi < Entry <K, V> > search( K );
	Rank size() { return empty()? 0 : last()->data->size(); }
	Rank height() {return List::size();}
	bool put( K, V );
	V* get( K );
	bool remove( K );
};