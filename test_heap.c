#include <stdio.h>
#include <stdlib.h>
#include "heap.h"



int main(){
	int tab[10] = {1,16,14,8,7,4,2,10,3,9};
	int i;
	printf("Tableau initial :\n");
	for(i = 0; i < 10; ++i){
		printf("%d, ",tab[i]);
	}
	printf("\n");
	
	heap* h = buildMaxHeap(tab, 10, 2);
   	printf("Tas maximal construit à partir du tableau\n");
	printHeap(h);	
	printf("Ajout de l'élément 13 dans le tas\n");
	insert(h, 13);
	printHeap(h);

	i = 3;
	printf("Élément à gauche de %d : %d\n",h->elements[3] , h->elements[hleft(3)]);
	printf("Élément à droite de %d : %d\n", h->elements[3], h->elements[hright(3)]);
	printf("Élément parent de %d : %d\n", h->elements[3], h->elements[hparent(3)]);
}
