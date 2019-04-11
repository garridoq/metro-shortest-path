#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

typedef struct pqueue pqueue;
struct pqueue{
	int* elements;
	int* keys;
	int max_size;
	int nb_elt;
};

//heap and general operations
void swap(pqueue* q, int i,int j);
pqueue* pqueueInit(int max_size);
void deletePqueue(pqueue* q);
int left(int i);
int right(int i);
int parent(int i);
void maxHeapify(pqueue* q, int i);
void printPqueue(pqueue* q);

//priority queue operations
void maxInsert(pqueue* q, int elt, int key);
int getMax(pqueue* q);
int extractMax(pqueue* q);
void increaseKey(pqueue* q, int x, int k);





#endif
