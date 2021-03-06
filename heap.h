#ifndef HEAP_H
#define HEAP_H

typedef struct heap heap;
struct heap{
	int* elements;
	int max_size;
	int nb_elt;
};

void hswap(int* tab, int i,int j);
heap* heapInit(int max_size);
void deleteHeap(heap* h);
int hleft(int i);
int hright(int i);
int hparent(int i);
void maxHeapify(heap* h, int i);
void insert(heap* h, int elt);
//Factor is used to define empty space in our heap
heap* buildMaxHeap(int* A, int size, int factor);

void printHeap(heap* h);

#endif
