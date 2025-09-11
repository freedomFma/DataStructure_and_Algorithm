#include "C++/DSA/02_list/List.hpp"
#include "BinTree.hpp"
#include "BinNode.hpp"
#include "HuffChar.hpp"
#include "C++/DSA/00_bitmap/Bitmap.hpp"
#include "C++/DSA/08_PrimiryQueue/Hashtable.hpp"

#define HuffTree BinTree<HuffChar>
typedef List<HuffTree*> HuffForest;
typedef Hashtable<char, char*> HuffTable;

int main(int argc, char* argv[]){
    ;
}
//寻找最小权重的树
HuffTree * minHChar (HuffForest* forest){
	ListNode<HuffTree*>* p = forest->first();
	ListNode<HuffTree*>* minChar = p;
	int minWeight = p->data->root()->data.weight;
	while(forest->valid(p=p->succ))
		if(minWeight > p->data->root()->data.weight){
			minWeight = p->data->root()->data.weight;
			minChar = p;
		}
	return forest->remove(minChar);
}
//构造编码树
HuffTree* generateTree(HuffForest* forest){
	while(1 < forest->size()){
		HuffTree *T1 = minHChar(forest);
		HuffTree *T2 = minHChar(forest);
		HuffTree *S = new HuffTree();
		S->insertAsRoot(HuffChar('^',T1->root()->data.weight + T2->root()->data.weight));
		S->attachAsLC(S->root(),T1);
		S->attachAsRC(S->root(),T2);
		forest->insertAsLast(S);
	}
	return forest->first()->data;
}

//构造编码表
static void generateCT
	(Bitmap* code, int length, HuffTable* table, BinNodePosi(HuffChar) v){
	if(Isleaf(*v)){
		table->put(v->data.ch, code->bit2string(length));
		return;
	}
	if(IsLChild(*v)){
		code->clear(length);
		generateCT(code, length+1, table, v->lc);
	}
	if(IsRChild(*v)){
		code->set(length);
		generateCT(code, length+1, table, v->rc);
	}
}

