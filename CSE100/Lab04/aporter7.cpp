#include <iostream>
#include<math.h>

using namespace std;

void maxHeapify(int* A, int i, int arrSize) {
    int largest;
    //Sets left and right to be the left and right parents of A[i]
    int left = 2*i;
    int right = 2*i + 1;

    //If we are not at the end of the heap and the left child is bigger than the parent make the left child the largest element
    if (left <= arrSize && A[left] > A[i]) {
        largest = left;
    }
    //Otherwise the parent is larger
    else 
        largest = i;

    //Find out whether the right child is bigger than the largest element we already found
    if(right <= arrSize && A[right] > A[largest]) {
        largest = right;
    }
    //If the largest element isn't already the one we're looking at (i) exchange the two and then call max-heapify on the next element
    if(largest != i) {
        int temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        maxHeapify(A, largest, arrSize);
    }
}

void buildMaxHeap(int *A, int arrSize) {
    //Call maxHeapify on every element in the array
    for(int i = floor(arrSize/2); i >= 0; i--) {
        maxHeapify(A, i, arrSize);
    }
}

void heapSort(int *A, int arrSize) {
    //Makes sure the left and right subtrees are max heaps
    buildMaxHeap(A, arrSize);

    int temp;
    //Exchange the top and bottom elements and then put the top element in its correct place in the maxHeap by calling maxHeapify on it
    for(int i = arrSize; i >= 1; i--) {
        temp = A[0];
        A[0] = A[i];
        A[i] = temp;
        arrSize--; //The last element is in the right place so it doesn't need to be sorted anymore
        maxHeapify(A, 0, arrSize);
    }
}

int main(int argc, char** argv) {
    int arrSize = 0;
    cin >> arrSize;

    int* nums = new int[arrSize];
    for(int i = 0; i < arrSize; i++) {
        cin >> nums[i];
    }

    heapSort(nums, arrSize-1);
    
    for(int i = 0; i < arrSize; i++) {
        cout << nums[i] << ";";
    }
}
