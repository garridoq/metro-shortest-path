#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "graphaux.h"
#include "graphes.h"
#include "dijkstra.h"
#include "priority_queue.h"

#define INF 2147483647
#define EXPLORE 1
#define ALL 0
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

/*======================================================================= *//*

Copie un graphe dans un autre

*//*======================================================================= */
void copyGrapheParams(graphe* dest, graphe* src){
	int i;
	int l;

	dest->x = (double*)malloc(src->nsom*sizeof(double));
	memcpy(dest->x, src->x, src->nsom*sizeof(double));	
	
	dest->y = (double*)malloc(src->nsom*sizeof(double));
	memcpy(dest->y, src->y, src->nsom*sizeof(double));	

	dest->v_arcs = (long int*)malloc(src->nmaxarc*sizeof(TYP_VARC));
	memcpy(dest->v_arcs, src->v_arcs, src->nmaxarc*sizeof(TYP_VARC));	

	dest->v_sommets = (long int*)malloc(src->nsom*sizeof(TYP_VSOM));
	memcpy(dest->v_sommets, src->v_sommets, src->nsom*sizeof(TYP_VSOM));	
	
	dest->nomsommet = (char **)malloc(src->nsom*sizeof(char*));
	for(i = 0; i < src->nsom; i++){
		l = strlen(src->nomsommet[i]);
		dest->nomsommet[i] = (char *)malloc((l+1)*sizeof(char));
		memcpy(dest->nomsommet[i], src->nomsommet[i], (l+1)*sizeof(char));
	}
}

/*======================================================================= *//*

Fonction utilisée pour notre heuristique

*//*======================================================================= */
double distance(graphe* g, int a, int b){
	return hypot(g->x[a] - g->x[b], g->y[a] - g->y[b])*25.7/10; 
}

/*======================================================================= *//*

Retourne le plus court chemin de d à a dans un graphe g.

*//*======================================================================= */
graphe* getChemin(graphe *g, int*S, int*pi, int d, int a, int mode){
	graphe* g_sym = Sym(g);
	int n = g->nsom;
	graphe* chemin = InitGraphe(n,n);
	int s = a;
	int new_s, y;
	pcell p;

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
	chemin = Sym(chemin);
	copyGrapheParams(chemin, g);
	printChemin(chemin,d,a);	
	
	if(mode == EXPLORE){
		chemin = exploredSommets(chemin, S, a);
	}

	return chemin;
}


/*======================================================================= *//*

Retourne un chemin avec uniquement les sommets explorés.

*//*======================================================================= */
graphe* exploredSommets(graphe *g, int *S, int a){
	int n_som = 0;
	int i = 0;
	pcell p;
	int y, j;

	//Calcul du nombre de sommets explorés
	for(i = 0; i < g->nsom; ++i){
		if(S[i] == 1){
			n_som++;
		}
	}
	printf("%d sommets parcourus\n",n_som);

	//Table de correspondance entre les sommets des graphes
	int* corresp = (int*)malloc(g->nsom*sizeof(int));
	j = 0;
	for(i = 0; i < g->nsom ; ++i){
		
		if(S[i] == 1){
			corresp[i] = j;
			j++;
		}
		else{
			corresp[i] = -1;
		}
	}


	graphe* g_expl = InitGraphe(n_som, n_som);
	g_expl->nomsommet = (char **)malloc(n_som*sizeof(char*));
	j = 0; //indice de nos sommet dans le nouveau graphe
	
	for(i = 0; i < g->nsom; ++i){
		//Si le sommet a été exploré
		if(S[i] == 1){
			g_expl->x[j] = g->x[i];
			g_expl->y[j] = g->y[i];
			//Nous savons que nous avons au plus un successeur dans un chemin donné
			if((p = g->gamma[i]) != NULL){ //Si nous avons un successeur
				y = p->som;
				AjouteArcValue(g_expl, j, corresp[y], p->v_arc );
				g_expl->nomsommet[j] = (char*)malloc((strlen(g->nomsommet[i])+1)*sizeof(char));
				memcpy(g_expl->nomsommet[j], g->nomsommet[i], (strlen(g->nomsommet[i])+1)*sizeof(char));
			}
			else{
				g_expl->nomsommet[j] = (char*)malloc(sizeof(char));
				g_expl->nomsommet[j][0] = '\0';
			}
			j++;
		}
	}
	//ajout du nom au point d'arrivée
	g_expl->nomsommet[corresp[a]] = (char*)malloc((strlen(g->nomsommet[a])+1)*sizeof(char));
	memcpy(g_expl->nomsommet[corresp[a]], g->nomsommet[a], (strlen(g->nomsommet[a])+1)*sizeof(char));
	return g_expl;
}

/*======================================================================= *//*

Calcule un plus court chemin avec A* sans file de priorité.

*//*======================================================================= */
/* ====================================================================== */
/*! \fn graphe * PCC(graphe * g, int d, int a)
    \param g (entrée) : un graphe valué (réseau). La longueur de chaque arc doit 
                        se trouver dans le champ v_arc de la structure cell .
    \param d (entrée) : un sommet (départ).
    \param a (entrée) : un sommet (arrivée).
    \param mode (entrée) : mode d'éxécution pour le chemin retourné (EXPLORE ou ALL)
	\return un plus court chemin de d vers a dans g , représenté par un graphe.
    \brief retourne un plus court chemin de d vers a dans g .
*/
/* ====================================================================== */
graphe* PCC(graphe* g, int d, int a, int mode){
	graphe *chemin;
	pcell p;
	int n = g->nsom;
	int i,y;
	int k = 1;
	int xk = d;
	//pour l'extraction de sommet
	int min,x_min; 
	double heuristique;
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
			heuristique = (pi[i] < INF) ? pi[i] + distance(g, i, a) : pi[i] ;
			if(heuristique  < min){ //heuristique
				min = heuristique;
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
	chemin = getChemin(g, S, pi, d, a, mode);	
	free(pi);
	free(S);
	return chemin;
}

/*======================================================================= *//*

Calcule un plus court chemin avec Dijkstra sans file de priorité.

*//*======================================================================= */
graphe* PCC_d(graphe* g, int d, int a, int mode){
	graphe *chemin;
	pcell p;
	int n = g->nsom;
	int i,y;
	int k = 1;
	int xk = d;
	//pour l'extraction de sommet
	int min,x_min; 
	double heuristique;
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
			heuristique = pi[i]; 
			if(heuristique  < min){ //heuristique
				min = heuristique;
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
	
	chemin = getChemin(g, S, pi, d, a, mode);
	
	free(pi);
	free(S);
	return chemin;
}



/*======================================================================= *//*

Calcule un plus court chemin avec A* avec file de priorité.

*//*======================================================================= */
graphe* PCC_pq(graphe* g, int d, int a, int mode){
	graphe *chemin;
	pcell p;
	int n = g->nsom;
	int i,y;
	int k = 1;
	int xk = d;
	//pour l'extraction de sommet
	int min,x_min;
	double heuristique;
	pqueue* pq = pqueueInit(n);
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
			if(S[y] == 1)//Si y déjà retiré de la file
				continue;
			
			pi[y] = (pi[y] < pi[xk] + p->v_arc) ? pi[y] : pi[xk] + p->v_arc; 
			heuristique = (pi[y] < INF) ? pi[y] + distance(g, y, a) : pi[y] ;
			if(pq->indices[y] == -1){// si y pas dans la file
				minInsert(pq, y, heuristique);
			}
			else if(heuristique < pq->keys[pq->indices[y]]){
				decreaseKey(pq, pq->indices[y], heuristique);
			}				
		}
		x_min = extractMin(pq);
		k++;
		xk = x_min;
		S[xk] = 1; // Union
		//S'arreter si on est arrivé à a
		if(x_min == a)
			break;

	}

	chemin = getChemin(g, S, pi, d, a, mode);

	free(pi);
	free(S);
	deletePqueue(pq);
	return chemin;
}


/*======================================================================= *//*

Affiche un chemin.

*//*======================================================================= */
void printChemin(graphe* g,int d, int a){
	int x = d;
	printf("Chemin le plus court de %d à %d:\n",d,a);
	while(x != a){
		printf("%s->",g->nomsommet[x]);
		x = g->gamma[x]->som;
	}
	printf("%s\n",g->nomsommet[a]);
}
