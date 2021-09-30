#include <iostream>

using namespace std;

//p is the index of the first element in list, q is the index of the middle element, and r is the index of the last element
void merge(int* list, int p, int q, int r) {
    //Finds the distance between the first and middle element and then the middle and last element
    int n1 = q - p + 1;
    int n2 = r - q;

    //Initializes new arrays that are the sizes of the left and right halves of the list
    int* left = new int[n1+1];
    int* right = new int[n2+1];   
    
    //Fills an array with the elements in the left half of list
    for (int i = 0; i < n1; i++)
        left[i] = list[p+i];
    //Fills an array with the elements in the right half of list
    for (int i = 0; i < n2; i++)
        right[i] = list[q+i+1];  

    //Sets the last element in each array to the largest possible integer
    left[n1] = 2147483647;
    right[n2] = 2147483647;

    int i = 0; int j = 0;
    for (int k = p; k <= r; k++) {
        //If the first element in the left array is less add it to the list and then go to the next element in the left array
        if (left[i] <= right[j]) {
            list[k] = left[i];
            i++;
        }
        else {
            list[k] = right[j];
            j++;
        }
    }

}

void mergeSort(int* list, int first, int last) {
    if (first < last) { 
        int middle = (first+last)/2;
        mergeSort(list, first, middle);
        mergeSort(list, middle + 1, last);
    
        merge(list, first, middle, last);
    }
}

int main(int argc, char**argv) {
    //Initializes variable for the size of the array and then reads it in
    int arrSize = 0;
    cin >> arrSize;

    //Initializes an array for the list numbers and then reads it in
    int*nums = new int[arrSize];

    for(int i = 0; i < arrSize; i++)
        cin >> nums[i];

    //Sends the numbers of the first and last indices of nums to mergeSort
    int first = 0;
    int last = arrSize-1;
    mergeSort(nums, first, last); 

    //Prints the result   
    for (int i = 0; i < arrSize; i++) {
        cout << nums[i] << ";";
    }
}


