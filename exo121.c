#include <stdlib.h>
#include <stdio.h>
#include "graphaux.h"
#include "graphes.h"

#define USAGE "genere un graphe aleatoire et calcule son symetrique grace a la fonction Sym"

/* ====================================================================== */
/*! \fn graphe * Sym(graphe * g)
    \param g (entrée) : un graphe.
    \return un graphe.
    \brief construit et retourne le graphe g_1 symétrique du graphe g. 
    \warning seule la représentation 'gamma' est utilisée. 
*/
graphe * Sym(graphe * g)
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
} /* Sym() */

/* ====================================================================== */
int main(int argc, char **argv)
/* ====================================================================== */
{
  graphe *g, *g_1;
  int na, ns;     /* nombre d'arcs, nombre de sommets */

  if (argc != 3)
  {
    fprintf(stderr, "usage: %s <nombre sommets> <nombre arcs>\n%s\n", argv[0], USAGE);
    exit(0);
  }

  ns = atoi(argv[1]);
  na = atoi(argv[2]);

  g = GrapheAleatoire(ns, na);   /* genere un graphe aleatoire antisymetrique sans boucle */
  g_1 = Sym(g);                  /* traitement : calcule le symetrique de g */
  printf("graphe g :\n");
  AfficheSuccesseurs(g);         /* affiche les ensembles "successeurs" de g a l'ecran */
  printf("graphe g_1 :\n");
  AfficheSuccesseurs(g_1);       /* idem pour le graphe symetrique g_1 */

  TermineGraphe(g);
  TermineGraphe(g_1);

  return 0;
} /* main() */
