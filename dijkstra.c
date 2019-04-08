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
		      AjouteArcValue(g_1, j, i,p->v_arc);
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
	graphe *chemin;
	pcell p;
	int n = g->nsom;
	int i,y;
	int k = 1;
	int xk = d;
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
	
	while( k < n && pi[xk] < INF){
		for(p = g->gamma[xk]; p != NULL; p = p->next){
			y = p->som;
			if(S[y] == 1)
				continue;
			pi[y] = (pi[y] < pi[xk] + p->v_arc) ? pi[y] : pi[xk] + p->v_arc; 
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
		xk = x_min;
		S[xk] = 1; // Union
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
		for(p = g_sym->gamma[s]; p != NULL; p = p->next){
			y = p->som;
			if(pi[s]-pi[y] == p->v_arc)
				new_s = y;
		}
		AjouteArc(chemin, s, new_s);
		s = new_s;
	}

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

void copyGrapheParams(graphe* dest, graphe* src){

	dest->x = (double*)malloc(src->nsom*sizeof(double));
	memcpy(dest->x, src->x, src->nsom*sizeof(double));	
	
	dest->y = (double*)malloc(src->nsom*sizeof(double));
	memcpy(dest->y, src->y, src->nsom*sizeof(double));	

	dest->v_arcs = (long int*)malloc(src->nmaxarc*sizeof(TYP_VARC));
	memcpy(dest->v_arcs, src->v_arcs, src->nmaxarc*sizeof(TYP_VARC));	

	dest->v_sommets = (long int*)malloc(src->nsom*sizeof(TYP_VSOM));
	memcpy(dest->v_sommets, src->v_sommets, src->nsom*sizeof(TYP_VSOM));	

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

	copyGrapheParams(chemin, g);
	//chemin->x = g->x;
	//chemin->y = g->y ;	
//	chemin->v_arcs = g->v_arcs ;	
//	chemin->v_sommets = g->v_sommets ;
	
    sprintf(buf, "%s_out.eps", argv[1]);     /* construit le nom du fichier PostScript */
	EPSGraphe(chemin, buf, 3,0,60,0,0,0,0);
	
	
	TermineGraphe(g);
	TermineGraphe(chemin);

	return 0;
}
