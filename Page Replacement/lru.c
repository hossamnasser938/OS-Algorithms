/*
Given memory capacity (as number of pages it can hold)
and a string representing pages to be referred,
write a function to find number of page faults.
*/

#include <stdio.h>
//Defining boolean type
typedef int bool;
#define true 1
#define false 0

int calculatePageFaults(int pages[], int n, int capacity);
int getElementIndex(int frames[], int capacity, int element);     //returns frame index if exists and -1 if page fault occurs 
int getPositionOfLeastCounter(int frames[], int capacity);       //returns index of least recently refrenced frame
bool addElement(int frames[], int capacity, int element);       //adds frame if it does not exist and there is empty space in physical memory
bool isThereSpace(int frames[], int capacity);                 //returns true if there is empty space in physical memory and false otherwise

int main(void) {
	int pages[] = { 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2 };
	int n = sizeof(pages) / sizeof(pages[0]);       //number of elements in pages array
	int capacity = 4;
	printf("%d\n", calculatePageFaults(pages, n, capacity));
	return 0;
}

int calculatePageFaults(int pages[], int n, int capacity) {

	int i, frames[capacity], framesTimes[capacity];
	//Initiate all frames with -1 value
	for (i = 0; i < capacity; i++) {
		frames[i] = -1;
	}

	int pageFaults = 0;        //Initialte number of page faults  

	int counter = 0;       //specifies the last time a frame is refrenced
	int currentFrame = 0;
	int leastPosition = 0;

	for (i = 0; i < n; i++) {
		counter++;
		currentFrame = getElementIndex(frames, capacity, pages[i]);
		if (currentFrame != -1) {    //frame exists in physical memory
			framesTimes[currentFrame] = counter;     //update its counter
		}
		else {    //frame does not exist in physical memory
			pageFaults++;    //page fault occurs as frame does not exist in physical memory
			if (isThereSpace(frames, capacity)) {      //There is empty space in physical memory
													   //Add frame and update its counter
				addElement(frames, capacity, pages[i]);
				currentFrame = getElementIndex(frames, capacity, pages[i]);
				framesTimes[currentFrame] = counter;
			}
			else {      //Physical memory is full
						//Replace frame with least recently refrenced one and update counter
				leastPosition = getPositionOfLeastCounter(framesTimes, capacity);
				frames[leastPosition] = pages[i];
				framesTimes[leastPosition] = counter;
			}
		}
	}

	return pageFaults;

}

bool isThereSpace(int frames[], int capacity) {
	int i;
	for (i = 0; i < capacity; i++) {
		if (frames[i] == -1) {
			return true;
		}
	}
	return false;
}

int getElementIndex(int frames[], int capacity, int element) {
	int i;
	for (i = 0; i < capacity; i++) {
		if (frames[i] == element) {
			return i;
		}
	}
	return -1;
}

bool addElement(int frames[], int capacity, int element) {
	int i;
	for (i = 0; i < capacity; i++) {
		if (frames[i] == -1) {
			frames[i] = element;
			return true;
		}
	}
	return false;
}

int getPositionOfLeastCounter(int framesTimes[], int capacity) {
	int i, leastCounterPosition = 0, leastCounter = framesTimes[0];
	for (i = 1; i < capacity; i++) {
		if (framesTimes[i] < leastCounter) {
			leastCounter = framesTimes[i];
			leastCounterPosition = i;
		}
	}
	return leastCounterPosition;
}
