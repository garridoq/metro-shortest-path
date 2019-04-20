#ifndef DIJKSTRA_H
#define DIJKSTRA_H

graphe * Sym(graphe * g);
void copyGrapheParams(graphe* dest, graphe* src);
graphe* exploredSommets(graphe *g, int *S, int a);
graphe* PCC(graphe* g, int d, int a, int mode);
graphe* PCC_d(graphe* g, int d, int a, int mode);
graphe* PCC_pq(graphe* g, int d, int a, int mode);
void printChemin(graphe* g,int d, int a);
double distance(graphe* g, int a, int b);

#endif
