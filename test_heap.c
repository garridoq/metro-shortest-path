#include <stdio.h>
#include <stdlib.h>
#include "heap.h"



int main(){
	int tab[10] = {1,16,14,8,7,4,2,10,3,9};
	heap* h = buildMaxHeap(tab, 10, 2);
   	printHeap(h);	
}
