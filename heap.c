#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "heap.h"

void hswap(int* tab, int i, int j){
	int temp = tab[j];
	tab[j] = tab[i];
	tab[i] = temp;
}

heap* heapInit(int max_size){
	heap* h = (heap *)malloc(sizeof(heap));
	h->max_size = max_size;
	h->nb_elt = 0;
	h->elements = (int *)malloc(max_size*sizeof(int));
	return h;
}

void deleteHeap(heap* h){
	free(h->elements);
	free(h);
}

int hleft(int i){
	return (i << 1) + 1;
}


int hright(int i){
	return (i << 1) + 2;
}

int hparent(int i){
	return (i-1) >> 1;
}


void maxHeapify(heap* h, int i){
	int l = hleft(i);
	int r = hright(i);
	//printf("l: %d, r: %d \n",l,r);
	int largest;
	if(l <= h->nb_elt &&  h->elements[l] > h->elements[i])
		largest = l;
	else
		largest = i;
	if( r <= h->nb_elt && h->elements[r] > h->elements[largest])
		largest = r;
	if( largest != i){
		hswap(h->elements, i, largest);
		maxHeapify(h, largest);
	}
}


heap* buildMaxHeap(int* A, int size, int factor){
	int i;
	heap *h = heapInit(size*factor);
	h->nb_elt = size;
	memcpy(h->elements, A, size*sizeof(int));
	for(i = (h->nb_elt >> 1); i >= 0; i = i - 1){
		maxHeapify(h, i);
	}	
	return h;
}

void insert(heap* h, int elt){
	int i;
	if(h->nb_elt == h->max_size){
		printf("Heap is full");
		return;
	}
	h->elements[h->nb_elt] = elt;
	h->nb_elt++;
	i = h->nb_elt - 1;
	while(i > 0 && h->elements[hparent(i)] < h->elements[i]){
		hswap(h->elements, i, hparent(i));
		i = hparent(i);
	}
}

void printHeap(heap* h){
	int i;
	printf("[");
	for(i = 0; i < h->nb_elt; ++i){
		printf("%d, ",h->elements[i]);
	}	
	printf("]\n");
}
