#include "./BTNode.hpp"

template <typename T> class BTree{
protected:
	Rank _size, _m;//关键总数和阶次
	BTNodePosi<T> _root, _hot;//根、search()最后访问的非空节点

	void solveOverflow(BTNodePosi<T>);
	void solveUnderflow(BTNodePosi<T>);

public:
//构造函数
    BTree(int m = 3): _size(0), _m(m) {_root = new BTNode<T>;}
    ~BTree(){if(_root) release(_root);}

//常用的可读接口
    int const order(){return m;}
    int const size(){return _size;}
    bool empty() const {return !_root || !_root->key.size();}
    BTNodePosi<T>& root(){return _root;}

//主要的算法接口
	BTNodePosi<T> search(const T& e);
	bool insert (const T& e);
	bool remove(const T& e);
};

// ============================================================
// ========  B树的主要算法：查找、插入（上溢）、删除（下溢）  =========
// ============================================================

//----------------------------------
// search(e) 查找算法
//----------------------------------
template <typename T> 
BTNodePosi<T> BTree<T>::search(const T& e){
	_hot = NULL;
	for (BTNodePosi<T> v = _root ; v;){
		Rank r = v->key.search(e);//r要么是命中的关键码，要么是
		if( (v != -1) && ( v->key[r] == e))
			return v;
		else{
			_hot = v;
			v = v->child[r+1];
		}
	}
	return NULL;
}

//----------------------------------
// [1] insert(e) 插入算法
// [2] solveOverflow(v) 上溢操作
//----------------------------------
template <typename T> bool BTree<T>::insert(const T& e){
	BTNodePosi<T> v = search(e);
	if(v) return false;
	
	Rank r = _hot->key.search(e);
	_hot->key.insert(r+1, e);
	_hot->child.insert(r+2, NULL);
	_size++;
	
	solveOverflow(_hot);
	return true;
}

template <typename T> 
void BTree<T>::solveOverflow(BTNodePosi<T> v){
	while(_m <= v->key.size()){

		Rank s = _m/2;//选择轴点，这个点将加入父节点

		//----------------------
		//把一个节点分裂成两个节点
		BTNodePosi<T> u = new BTNode<T>();
		for(Rank j = 0; j < _m -s -1; j++){//右兄弟节点的关键码_m-s-1个
			u->child.insert(j, v->child.remove(s+1) );//注意这里用的remove操作，需要删除的点一直都是s+1
			u->key.insert(j , v->key.remove(s+1) );//同理
		}
		u->child[_m-s-1] = v->child.remove(s+1);//孩子向量要多一个元素
		//-----------------------
		//完善工作，更新新节点与孩子的父子关系
		if(u->chile[0])
			for(Rank j = 0; j < _m-s;j++)//孩子指针_m-s个
				u->child[j]->parent = u;

		//-----------------------
		//将轴点上溢：
		BTNodePosi<T> p = v->parent;//找到分裂节点的父节点
		if(!p){//如果分裂的父节点不存在，那么就新建，+更新p与v的父子关系
			_root = new BTNode<T>();
			p->child[0] = v;
			v->parent = p;
		}
		//当前一定存在v的父节点p
		Rank r = 1 + p->key.search(v->key[0]);//找到上溢节点将要插入的位置
		p->key.insert(r , v->key.remove(s));//成功插入p且v将其删除
		p->child.insert(r+1 , u);u->parent = p;//更新且维护u p之间的父子关系

		//-----------------------
		//检查上溢后的父节点是否上溢。最多一共需要 h(树高) 次循环
		v = p;
	}
}



//----------------------------------
// [1] remove(e) 插入算法
// [2] solveUnderflow(v) 下溢操作
//----------------------------------
template <typename T> 
bool BTree<T>::remove(const T& e){
	BTNodePosi<T> v = search(e);
	if(!v) return false;//如果不存在直接返回失败
	Rank r = v->key.search(e);//确定e在v中的秩
	
	if(v->child[0]){//如果v不是叶子节点
		BTNodePosi<T> u = v->child[ r+1 ];//比u大的最小值
		while (u->child[0]) u = u->child[0];//此时的u是叶子
		v->key[r] = u->key[0];
		v = u; r = 0;//重新定位将需要删除的节点
	}
	
	v->key.remove(r); v->child.remove(r+1);_size--;
	solveUnderflow(v);
	return true;
}

template <typename T> void BTree<T>::solveUnderflow(BTNodePosi<T> v){
	while( (_m+1)/2 > v->child.size(0) ){
		BTNodePosi<T> p = v->parent;
		if(!p){ // 已经到达根节点
			return;
		}
		//检查v是p节点的第几个孩子
		Rank r = 0;
		while(p->child[r] != v) r++;//r是孩子向量的秩
		//------------------------------
		//如果v的左兄弟存在，而且足够可以借给v
		// 旋转操作
		if ( 0 < r ){
			BTNodePosi<T> ls = p->child[r - 1];
			if( (_m+1)/2 < ls->child.size() ){
				v->key.insert(0, p->key[r-1]);
				p->key[r-1] = ls->key.remove( ls->key.size() - 1);
				v->child.insert(0, ls->child.remove(ls->child.size() - 1) );
				//更新过继孩子与继父的父子关系
				if(v->child[0])
					v->child[0]->parent = v;
				return;
			}
		}
		//------------------------------
		//如果v的右兄弟存在，而且足够可以借给v
		// 旋转操作
		if(p->child.size() -1 > r){
			BTNodePosi<T> rs = p->child[r+1];
			v->key.insert(v->key.size(), p->key[r]);
			//v->key.insert( p->key[r]); 向量实现了插入到最后的接口
			p->key[r] = rs->key.remove(0);
			v->child.insert(v->child.size(), rs->child.remove(0));
			if(v->child[v->child.size() - 1])
				v->child[v->child.size() - 1]->parent = v;
			return;
		}
		//------------------------------
		//如果v的兄弟都不足够借给v，优先跟左兄弟合并，如果没有左兄弟，就跟右兄弟合并
		if( 0 < r ){//与左兄弟合并
			BTNodePosi<T> ls = p->child[r-1];
			ls->key.insert(ls->key.size(), p->key.remove(r-1) );
			p->child.remove(r);
			ls->child.insert(ls->child.size(), v->child.remove(0) );
			if ( ls->child[ls->child.size() - 1])
				ls->child[ls->child.size() - 1]->parent = ls;
				
			while( !v->key.empty() ){
				ls->key.insert(ls->key.size(), v->key.remove(0) );
				ls-> child.inset(ls->child.size(), v->child.remove(0) );
				if (ls-> child[ls->child.size() - 1] )
					ls->child[ls->child.seze()-1]->parent = ls;
			}
			delete v;
			
		}
		else{//与右兄弟合并
			BTNodePosi<T> rs = p->child[r+1];
			rs->key.insert(0, p->key.remove(r));
			p->child.remove(r);
			rs->child.insert(0, v->child.remove(v->child.size() - 1));
			if(rs->child[0])
				rs->child[0]->parent = rs;
			
			while( !v->key.empty() ){
				rs->key.insert(0, v->key.remove(v->key.size() - 1) )
				rs->child.insert(0, v->child.remove(v->child.size() - 1));
				if(rs->child[0])
					rs->child[0]->parent = rs;
			}
			delete v;
		}
		
		//由于合并过程需要父节点的关键码作为粘合剂，所以需要检查父节点是否下溢
		//上升一层检查是否父节点是否下溢。
		v = p;
	}
}