#include <iostream>
#include <cstdlib>
using namespace std;

int partition(int* nums, int first, int last) {
    //Chooses a random index to be the pivot
    int pivot = first + rand() % (last-first);
    //Switches the pivot element with the last element
    int temp = nums[last];
    nums[last] = nums[pivot];
    nums[pivot] = temp;

    int x = nums[last];
    int i = first-1;
    for (int j = first; j <= last-1; j++) {
        if (nums[j] <= x) {
            i++;
            temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }
    }
    temp = nums[i+1];
    nums[i+1] = nums[last];
    nums[last] = temp;
    return i+1;
    
}

void quicksort(int* nums, int first, int last) {
    if(first < last) {
        //Rearranges the array around the pivot and returns the index of the pivot
        int newSize = partition(nums, first, last);
        //Returns the left and right "halves" of the array
        quicksort(nums, first, newSize-1);
        quicksort(nums, newSize+1, last);
    }
    

    
}

int main(int argc, char** argv) {
    int arrSize = 0;
    cin >> arrSize;

    int* nums = new int[arrSize];
    for(int i = 0; i < arrSize; i++) {
        cin >> nums[i];
    }

    quicksort(nums, 0, arrSize-1);

    for(int i = 0; i < arrSize; i++) {
        cout << nums[i] << ";";
    }
}
