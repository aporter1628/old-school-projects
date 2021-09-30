#include <iostream>

using namespace std;

//p is the index of the first element in list, q is the index of the middle element, and r is the index of the last element
int* merge(int left[], int right[]) {
    int size = sizeof(left) + sizeof(right)
    int* result = new int[size];

    int i = 0;
    int j = 0;
    for (int k = 0; k < size; k++) {
        if (left[i] < right[j]){
            result[k] = left[i];
            i++;
        }
        else{
            result[k] = right[j];
            j++;
        }
    }
    return result;
}

int* mergeSort(int list[]) {
    arrSize = sizeof(list);
    if (arrSize <= 1) 
        return list;

    int middle = (first+last)/2;

    int* l = new int[middle];
    int* r = new int[arrSize-middle];
    for(int i = 0; i < middle, i++) 
        l[i] = list[i]
    for(int i = 0; i < arrSize-middle; i++)
        r[i] = list[i + middle + 1]

    int* left = mergeSort(l);
    int* right = mergeSort(r);
    
     return merge(left, right);
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
    mergeSort(nums); 

    //Prints the result   
    for (int i = 0; i < arrSize; i++) {
        cout << nums[i] << ";";
    }
}
