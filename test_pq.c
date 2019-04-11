#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"



int main(){
	int tab[10] = {1,16,14,8,7,4,2,10,3,9};
   	
	pqueue* p = pqueueInit(20);
	printf("Ajout d'éléments dans le tas\n");
	for(int i = 0; i < 10; i++){
		minInsert(p, i, tab[i]);
	}
	printPqueue(p);
	printf("Depilement de la file\n");
	for(int i = 0; i < 10; i++){
		int a = extractMin(p);
		printf("min : %d\n",a);	
	}
	printPqueue(p);
}
