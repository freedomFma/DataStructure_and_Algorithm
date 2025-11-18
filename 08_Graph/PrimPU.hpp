
//最小支撑树Prim算法的prioUpdater
template <typename Tv, typename Te> struct PrimPU{
    virtual void operator()(Graph<Tv, Tv>* G, int uk, int v){
        if(G->status(v) == UNDISCOVERED){//如果v还没有被发现
            if(G->priority(v) > G->weight(uk, v))
                G->priority(v) = G->weight(uk, v);
                G->parent(v) = uk;
        }
    }
};