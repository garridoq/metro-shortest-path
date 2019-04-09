#ifndef DIJKSTRA_H
#define DIJKSTRA_H

graphe * Sym(graphe * g);
void copyGrapheParams(graphe* dest, graphe* src);
graphe* exploredSommets(graphe *g, int *S);
graphe* PCC(graphe* g, int d, int a, int mode);
void printChemin(graphe* g,int d, int a);

#endif
