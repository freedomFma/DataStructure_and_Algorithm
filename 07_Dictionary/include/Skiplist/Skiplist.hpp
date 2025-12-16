#include "./Dictionary.hpp"
#include "../02_list/List.hpp"
#include "./Quadlist.hpp"
#include "../05_BinSearchTree/Entry.hpp"

//列表的列表
template <typename K, typename V> struct Skiplist:
public Dictionary<K, V>, public List<Quadlist<Entry<K,V>>*>{
    Skiplist() { insertFirst( new Quadlist < Entry<K, V> > ); }//first()塔顶，last()塔底
	QNodePosi < Entry <K, V> > search( K );
	//底层QuadList的规模
	Rank size() { return empty()? 0 : last()->data->size(); }//这里的empty()使用了父类list中的函数
	Rank height() {return List::size();}//Dictionary和List中同时有size()，要明确是哪个父类中的size
	bool put( K, V );
	V* get( K k);
	bool remove( K );
};


template <typename K , typename V> 
QNodePosi< Entry <K, V> > Skiplist<K, V>::search(K k){
	for( QNodePosi< Entry<K,V> > p = first()->data->head; ;){
		if( (p->succ->succ) && (p->succ->entry.key <= k) ) 
			p = p->succ;
		else if(p->below)
			p = p->below;
		else return p;
	}
}

template <typename K , typename V> 
V* Skiplist<K, V>::get( K k ){
	if( empty() ) return NULL;

	QNodePosi< Entry <K, V> > p = search( k);
	if (!p) return nullptr;
	return &(p->data.value); 
}


template <typename K, typename V>
bool Skiplist<K, V>::put(K k, V v){
	Entry<K , V> e = Entry<K, V>(k,v);
	QNodePosi< Entry<K, V> > p = search(k);//p是基底不大于k的最大词条
	//if (p->entry.key == k) {     // key 已存在
	//    p->entry.value = v;      // 更新值
	//    return false;            // 不插入新节点
	//}
	ListNodePosi< Quadlist<Entry<K, V>>* > qlist = last();//塔底
	QNodePosi <Entry<K, V>> b = qlist->data->insert(e, p);//创建新的基座(一定要创建新的词条吗？万一p就是需要插入的词条呢？一定要把p当作前驱吗？)
	
	while(rand() & 1){//置硬币
		while ( p->pred && !p->above ) p = p->pred; //找到最近的顶层词条
		if( !p->pred && !p->above){ //前驱是head并且是顶层
			insertFirst( new Quadlist<Entry<K, V> > );
			first()->data->head->below = qlist->data->head;
			qlist->data->head->above = first()->data->head;
		}
		p = p->above;
		qlist = qlist->pred;
		b = qlist->data->insert(e, p ,b);
	}
	return true;
}


template <typename K ,typename V>
bool Skiplist<K, V>::remove(K k){
	//查找关键码为k的节点：
	QNodePosi< Entry<K, V> > p = search(k);
	if( !p->pred || (k != p->entry.key)) //确保p不是head节点，或者根本没有关键码为k的节点
		return false;
	//有关键码为k 的节点，找到这一词条的塔顶
	ListNodePosi< Quadlist<Entry<K, V> >* > qlist = last();//塔底四联表
	while (p->above) {
		qlist = qlist->pred;
		p = p->above;
	}
	
	//拆塔
	do{ 
		QNodePosi<Entry<K, V>> lower = p->below;
		qlist->data->remove(p);//使用四联表的删除
		p = lower;
		qlist = qlist->succ;//下一层
	}while(qlist->succ);//下一层非底层，如果达到塔底就不会再进行删除了
	
	//删除空表
	while ( (1<height()) && (first()->data->_size < 1) ){
		List::remove(first());
		first()->data->head->above = NULL;
		first()->data->tail->above = NULL;
	}
	return true;
}