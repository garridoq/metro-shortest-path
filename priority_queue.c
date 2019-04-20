#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "priority_queue.h"

void swap(pqueue* q, int i, int j){
	q->indices[q->elements[j]] = i;
	q->indices[q->elements[i]] = j;
	
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
	q->indices = (int *)malloc(max_size*sizeof(int));
	for(int i = 0; i < max_size; ++i){
		q->indices[i] = -1;
	}
	q->keys = (double *)malloc(max_size*sizeof(double));
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
	return (i-1) >> 1;
}


void minHeapify(pqueue* q, int i){
	int l = left(i);
	int r = right(i);
	//printf("l: %d, r: %d \n",l,r);
	int smallest;
	if(l <= q->nb_elt &&  q->keys[l] < q->keys[i])
		smallest = l;
	else
		smallest = i;
	if( r <= q->nb_elt && q->keys[r] < q->keys[smallest])
		smallest = r;
	if( smallest != i){
		swap(q, i, smallest);
		minHeapify(q, smallest);
	}
}

void decreaseKey(pqueue *q, int x ,double k){
	
	int i = x;
	if(k > q->keys[i]){
		printf("New key is bigger than current key\n");
		return;
	}
	q->keys[i] = k;
	while(i > 0 && q->keys[parent(i)] > q->keys[i]){
		swap(q, i, parent(i));
		i = parent(i);
	}

}

void minInsert(pqueue* q, int elt, double key){
	if(q->nb_elt == q->max_size){
		printf("Priority queue is full\n");
		return;
	}	
	q->elements[q->nb_elt] = elt;
	q->keys[q->nb_elt] = INF;
	q->indices[elt] = q->nb_elt;
	q->nb_elt++;

	decreaseKey(q, q->nb_elt - 1, key);
}

int getMin(pqueue* q){
	return q->elements[0];
}

int extractMin(pqueue* q){
	if(q->nb_elt < 1){
		printf("Underflow\n");
		return -1;
	}
	int max = q->elements[0];
	q->elements[0] = q->elements[q->nb_elt-1];
    q->keys[0] = q->keys[q->nb_elt-1];
	q->indices[max] = -1; //On enleve l'elt du tableau
	q->indices[q->elements[0]] = 0;
	q->nb_elt--;
	minHeapify(q, 0);
	return max;
}

void printPqueue(pqueue* q){
	int i;

	printf("====================================\n");
	printf("Elements : %d/%d\n",q->nb_elt, q->max_size);
	printf("Elements:\n[");
	for(i = 0; i < q->nb_elt; ++i){
		printf("%d, ",q->elements[i]);
	}	
	printf("]\n");
	
	printf("Keys:\n[");
	for(i = 0; i < q->nb_elt; ++i){
		printf("%f, ",q->keys[i]);
	}	
	printf("]\n");
/*	
	printf("Indices:\n[");
	for(i = 0; i < q->max_size; ++i){
		printf("%d, ",q->indices[i]);
	}	
	printf("]\n");
*/
}

