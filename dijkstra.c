#include <stdlib.h>
#include <stdio.h>
#include "graphaux.h"
#include "graphes.h"

#define INF 2147483647
#define USAGE "lit un graphe dans le fichier <filename> et calcule le plus court chemin du début à la fin"
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

  for (i=0; i < nsom; i++){ // Pour tout somme i de g
      for(p= g->gamma[i]; p != NULL; p = p->next){
          j = p->som; // j est un successeur de i dans g
		  if(EstSuccesseur(g, i, j))
		      AjouteArc(g_1, j, i);
      } 
  }
  return g_1;
} /* Sym() */

/* ====================================================================== */
/*! \fn graphe * PCC(graphe * g, int d, int a)
    \param g (entrée) : un graphe valué (réseau). La longueur de chaque arc doit 
                        se trouver dans le champ v_arc de la structure cell .
    \param d (entrée) : un sommet (départ).
    \param a (entrée) : un sommet (arrivée).
    \return un plus court chemin de d vers a dans g , représenté par un graphe.
    \brief retourne un plus court chemin de d vers a dans g .
*/
/* ====================================================================== */
graphe* PCC(graphe* g, int d, int a){
	graphe *chemin = InitGraphe(g->nsom, g->nmaxarc);
	pcell p;
	int n = g->nsom;
	int i,y;
	int k = 1;
	int* x = (int*)malloc((n+1)*sizeof(int));
	x[1] = d;
	//pour l'extraction de sommet
	int min,x_min;
	//Pour le calcul du chemin
	int s, new_s, j;
	

	// On utilise un tableau pour représenter un ensemble de sommet
	// ainsi S = {1,3,6} sera représenté par
	// S = [0,1,0,1,0,0,1]
	int* S = (int*)malloc(n*sizeof(int));
	for(i=0; i < n; ++i){
		S[i] = 0;
	}
	S[d] = 1;

	int* pi = (int*)malloc(n*sizeof(int));
	for(i=0; i < n; ++i){
		pi[i] = INF;
	}
	pi[d]=0;
	
	while( k < n && pi[x[k]] < INF){
		for(p = g->gamma[x[k]]; p != NULL; p = p->next){
			y = p->som;
			if(S[y] == 1)
				continue;
			pi[y] = (pi[y] < pi[x[k]] + p->v_arc) ? pi[y] : pi[x[k]] + p->v_arc; 
		}
		
		min = INF; x_min = 0;
		for(i = 0; i < n; ++i){
			if(S[i] == 1)
				continue;
			if(pi[i] < min){
				min = pi[i];
				x_min = i;
			}
		}
		k++;
		x[k] = x_min;
		S[x[k]] = 1; // Union
		//S'arreter si on est arrivé à a
		if(x_min == a)
			break;

	}
	//Récupération du chemin
	//On calcule le symmétrique pour avoir les prédécesseurs
	graphe* g_sym = Sym(g);
	chemin = InitGraphe(n,n);
	s = a;
	
	while( s != d){
		new_s = -1;
		min = INF;
		for(p = g_sym->gamma[s]; p != NULL; p = p->next){
			y = p->som;
			if(pi[y] < min){
				min = pi[y];
				new_s = y;
			}
		}
		AjouteArc(chemin, s, new_s);
		s = new_s;
	}

	free(x);
	free(S);
	free(pi);
	return Sym(chemin);
}

void printChemin(graphe* g,int d, int a){
	int x = d;
	printf("Chemin le plus court de %d à %d:\n",d,a);
	while(x != a){
		printf("%d->",x);
		x = g->gamma[x]->som;
	}
	printf("%d\n",a);

}


int main(int argc, char **argv){
	graphe *g;
	graphe *chemin;
	char buf[256];

    if (argc != 4)
    {
      fprintf(stderr, "usage: %s <filename>\n%s\n", argv[0], USAGE);
      exit(0);
    }
	int d = atoi(argv[2]);
	int a = atoi(argv[3]);

    g = ReadGraphe(argv[1]);  /* lit le graphe a partir du fichier */
    chemin = PCC(g, d, a);
    
	printChemin(chemin, d, a);
	
	EPSGraphe(chemin,"out.eps", 3,0,60,0,0,0,0);
	
	
	TermineGraphe(g);
	TermineGraphe(chemin);

	return 0;
}
