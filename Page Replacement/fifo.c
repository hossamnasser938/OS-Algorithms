/*
Given memory capacity (as number of pages it can hold)
and a string representing pages to be referred,
write a function to find number of page faults
*/

#include <stdio.h>
#include <stdlib.h>
//Defining boolean type
typedef int bool;
#define true 1
#define false 0

struct Queue {
	int front;
	int rear;
	unsigned capacity;
	int size;
	int *items;
};

struct Queue* createQueue(unsigned capacity);
bool isEmpty(struct Queue* queue);
bool isFull(struct Queue* queue);
void enqueue(struct Queue* queue, int item);
int dequeue(struct Queue* queue);
bool contains(struct Queue* queue, int item);

int calculatePageFaults(int pages[], int n, int capacity);

int main(void) {

	int pages[] = { 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2 };
	int n = sizeof(pages) / sizeof(pages[0]);
	int capacity = 4;
	printf("%d\n", calculatePageFaults(pages, n, capacity));

	return 0;
}

int calculatePageFaults(int pages[], int n, int capacity) {

	int pageFaults = 0;        //Initialte number of page faults

	struct Queue* queue = createQueue(capacity);

	int i;
	for (i = 0; i < n; i++) {
		if (!contains(queue, pages[i])) {     //frame does not exist in the physical memory 
			pageFaults++;       //page fault occurs
								//if queue is not full enqueue directly
			if (!isFull(queue)) {
				enqueue(queue, pages[i]);
			}
			//if queue is full dequeue and then enqueue
			else {
				dequeue(queue);
				enqueue(queue, pages[i]);
			}
		}
	}

	return pageFaults;

}

struct Queue* createQueue(unsigned capacity) {
	struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
	queue->capacity = capacity;
	queue->size = 0;
	queue->rear = capacity - 1;
	queue->front = capacity;
	queue->items = (int*)malloc(capacity * sizeof(int));
	return queue;
}

bool isEmpty(struct Queue* queue) {
	return (queue->size == 0);
}

bool isFull(struct Queue* queue) {
	return (queue->size == queue->capacity);
}

void enqueue(struct Queue* queue, int item) {
	queue->items[queue->rear] = item;
	queue->rear = (queue->rear - 1) % queue->capacity;
	queue->size = queue->size + 1;
}

int dequeue(struct Queue* queue) {
	int item = queue->items[queue->front];
	queue->front = (queue->front - 1) % queue->capacity;
	queue->size = queue->size - 1;
	return item;
}

bool contains(struct Queue* queue, int item) {
	int i = 0;
	int j = queue->rear + 1;
	while (i < (queue->size)) {
		if (queue->items[j] == item) {
			return true;
		}
		j = (j + 1) % queue->capacity;
		i++;
	}
	return false;
}
