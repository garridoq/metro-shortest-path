#include <stdlib.h>
#include <stdio.h>
#include "graphaux.h"
#include "graphes.h"
#include "dijkstra.h"

#define USAGE "lit un graphe dans le fichier <filename> et calcule le plus court chemin du début à la fin"

int main(int argc, char **argv){
	graphe *g;
	graphe *chemin;
	char buf[256];
    chrono Chrono1; /* pour la mesure du temps */
    
	if (argc != 4){
      fprintf(stderr, "usage: %s <filename>\n%s\n", argv[0], USAGE);
      exit(0);
    }
	int d = atoi(argv[2]);
	int a = atoi(argv[3]);

    g = ReadGraphe(argv[1]);  /* lit le graphe a partir du fichier */
    
	start_chrono(&Chrono1);
	chemin = PCC(g, d, a, 1);
	printf("Temps écoulé :%d us\n",read_chrono(&Chrono1));

    sprintf(buf, "%s_%s_%s_out.eps", argv[1], argv[2], argv[3]);     /* construit le nom du fichier PostScript */
	EPSGraphe(chemin, buf, 3,0,60,1,0,0,0);
	
	start_chrono(&Chrono1);
	chemin = PCC_pq(g, d, a, 1);
	printf("Temps écoulé :%d us\n",read_chrono(&Chrono1));

    sprintf(buf, "%s_%s_%s_out_pq.eps", argv[1], argv[2], argv[3]);     /* construit le nom du fichier PostScript */
	EPSGraphe(chemin, buf, 3,0,60,1,0,0,0);
	
	TermineGraphe(g);
	TermineGraphe(chemin);

	return 0;
}
