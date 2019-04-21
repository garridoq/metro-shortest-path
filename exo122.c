#include <stdlib.h>
#include <stdio.h>
#include "graphaux.h"
#include "graphes.h"

#define USAGE "idem main02, affichage en moins et mesure du temps de calcul en plus"

/* ====================================================================== */
/*! \fn graphe * Sym(graphe * g)
    \param g (entrée) : un graphe.
    \return un graphe.
    \brief construit et retourne le graphe g_1 symétrique du graphe g. 
    \warning seule la représentation 'gamma' est utilisée. 
*/
graphe * Sym2(graphe * g)
/* ====================================================================== */
{
  graphe *g_1;
  int nsom, narc, k, i, j;
  pcell p;

  nsom = g->nsom;
  narc = g->narc;
  g_1 = InitGraphe(nsom, narc);

  for (i=0; i < nsom; i++){ // Pour tout somme i de g
      for(p= g->gamma[i]; p != NULL; p = p->next){
          j = p->som; // j est un successeur de i dans g
		  if(EstSuccesseur(g, i, j))
		      AjouteArc(g_1, j, i);
      } 
  }
  return g_1;
} /* Sym() */

graphe * Sym1(graphe * g)
/* ====================================================================== */
{
  graphe *g_1;
  int nsom, narc, k, i, j;
  pcell p;

  nsom = g->nsom;
  narc = g->narc;
  g_1 = InitGraphe(nsom, narc);

  for (i = 0; i < nsom; i++) /* pour tout i sommet de g */
    for (j = 0; j < nsom; j++) /* pour tout j sommet de g */
      if (EstSuccesseur(g, i, j))
        AjouteArc(g_1, j, i);
  return g_1;
}
/* ====================================================================== */
int main(int argc, char **argv)
/* ====================================================================== */
{
  graphe *g, *g_1;
  int na, ns;     /* nombre d'arcs, nombre de sommets */
  chrono Chrono1; /* pour la mesure du temps */
  int temps;      /* idem */

  if (argc != 3)
  {
    fprintf(stderr, "usage: %s <nombre sommets> <nombre arcs>\n%s\n", argv[0], USAGE);
    exit(0);
  }

  ns = atoi(argv[1]);
  na = atoi(argv[2]);

  g = GrapheAleatoire(ns, na);   /* genere un graphe aleatoire antisymetrique sans boucle */
  start_chrono(&Chrono1);        /* top chrono : debut du traitement */
  g_1 = Sym1(g);                  /* traitement : calcule le symetrique de g */
  temps = read_chrono(&Chrono1); /* top chrono : fin du traitement */

  printf("temps de traitement Version 1: %d microsecondes\n", temps);

  start_chrono(&Chrono1);        /* top chrono : debut du traitement */
  g_1 = Sym2(g);                  /* traitement : calcule le symetrique de g */
  temps = read_chrono(&Chrono1); /* top chrono : fin du traitement */

  printf("temps de traitement Version 2: %d microsecondes\n", temps);

  TermineGraphe(g);
  TermineGraphe(g_1);
  
  return 0;
} /* main() */
