#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "priority_queue.h"

void swap(pqueue* q, int i, int j){
	int temp = q->elements[j];
	q->elements[j] = q->elements[i];
	q->elements[i] = temp;

	temp = q->keys[j];
	q->keys[j] = q->keys[i];
	q->keys[i] = temp;
}

pqueue* pqueueInit(int max_size){
	pqueue* q = (pqueue *)malloc(sizeof(pqueue));
	q->max_size = max_size;
	q->nb_elt = 0;
	q->elements = (int *)malloc(max_size*sizeof(int));
	q->keys = (int *)malloc(max_size*sizeof(int));
	return q;
}

void deletePqueue(pqueue* q){
	free(q->elements);
	free(q->keys);
	free(q);
}

int left(int i){
	return (i << 1) + 1;
}


int right(int i){
	return (i << 1) + 2;
}

int parent(int i){
	return i >> 1;
}


void maxHeapify(pqueue* q, int i){
	int l = left(i);
	int r = right(i);
	//printf("l: %d, r: %d \n",l,r);
	int largest;
	if(l <= q->nb_elt &&  q->keys[l] > q->keys[i])
		largest = l;
	else
		largest = i;
	if( r <= q->nb_elt && q->keys[r] > q->keys[largest])
		largest = r;
	if( largest != i){
		swap(q, i, largest);
		maxHeapify(q, largest);
	}
}

void increaseKey(pqueue *q, int x ,int k){
	int i = x;
	if(k < q->keys[i]){
		printf("New key is smaller than current key\n");
		return;
	}
	q->keys[i] = k;
	while(i > 0 && q->keys[parent(i)] < q->keys[i]){
		swap(q, i, parent(i));
		i = parent(i);
	}

}

void maxInsert(pqueue* q, int elt, int key){
	if(q->nb_elt == q->max_size){
		printf("Priority queue is full\n");
		return;
	}	
	q->elements[q->nb_elt] = elt;
	q->keys[q->nb_elt] = -1;
	q->nb_elt++;

	increaseKey(q, q->nb_elt - 1, key);
}

int getMax(pqueue* q){
	return q->elements[0];
}

int extractMax(pqueue* q){
	if(q->nb_elt < 1){
		printf("Underflow\n");
		return -1;
	}
	int max = q->elements[0];
	q->elements[0] = q->elements[q->nb_elt-1];
    q->keys[0] = q->keys[q->nb_elt-1];
	q->nb_elt--;
	maxHeapify(q, 0);
	return max;
}

void printPqueue(pqueue* q){
	int i;
	printf("Elements:\n[");
	for(i = 0; i < q->nb_elt; ++i){
		printf("%d, ",q->elements[i]);
	}	
	printf("]\n");
	
	printf("Keys:\n[");
	for(i = 0; i < q->nb_elt; ++i){
		printf("%d, ",q->keys[i]);
	}	
	printf("]\n");
}