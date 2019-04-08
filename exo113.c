#include <stdlib.h>
#include <stdio.h>
#include "graphaux.h"
#include "graphes.h"

#define USAGE "genere un graphe aleatoire et sa representation en PostScript dans tmp.eps"

/* ====================================================================== */
int main(int argc, char **argv)
/* ====================================================================== */
{
  graphe *g;
  int na, ns;     /* nombre d'arcs, nombre de sommets */

  if (argc != 3)
  {
    fprintf(stderr, "usage: %s <nombre sommets> <nombre arcs>\n%s\n", argv[0], USAGE);
    exit(0);
  }

  ns = atoi(argv[1]);
  na = atoi(argv[2]);

  g = GrapheAleatoire(ns, na);      /* genere un graphe aleatoire antisymetrique sans boucle */
  PlongementCirculaire(g, 150);     /* plonge le graphe dans le plan */
  PSGraphe(g, (char *)"tmp.eps", 5, 5, 60); /* genere une figure en PostScript */

  TermineGraphe(g);

  return 0;
} /* main() */
