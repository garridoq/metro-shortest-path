#include <stdlib.h>
#include <stdio.h>
#include "graphaux.h"
#include "graphes.h"

#define USAGE "lit un graphe dans le fichier <filename> et l'affiche a l'ecran"

/* ====================================================================== */
int main(int argc, char **argv)
/* ====================================================================== */
{
  graphe *g;
  char buf[256];

  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <filename>\n%s\n", argv[0], USAGE);
    exit(0);
  }

  g = ReadGraphe(argv[1]);  /* lit le graphe a partir du fichier */
  AfficheSuccesseurs(g);    /* affiche les ensembles "successeurs" a l'ecran */

  TermineGraphe(g);

  return 0;
} /* main() */
