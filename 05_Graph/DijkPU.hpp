
//最短路径Dijkstra算法的prioUpdater
template <typename Tv, typename Te> struct DijkPU{
    virtual void operator()(Graph<Tv, Tv>* G, int uk, int v){
        if(G->status(v) == UNDISCOVERED){
            if(G->priority(v) > G->priority(uk) + G->weight(uk, v))
                G->priority(v) = G->priority(uk) + G->weight(uk, v);
                G->parent(v) = uk;
        }
    }
};