#include "./Dictionary.hpp"
#include "../02_list/List.hpp"
#include "./Quadlist.hpp"
#include "../05_BinSearchTree/Entry.hpp"
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

template <typename K , typename V> 
QNodePosi< Entry <K, V> > Skiplist<K, V>::search(K k){
	for( QNodePosi< Entry<K,V>> p = first()->data->head; ;){
		if( (p->succ->succ) && (p->succ->entry.key <= k) ) 
			p = p->succ;
		else if(p->below)
			p = p->below;
		else return p;
	}
}