//Insertion sort

#include <iostream>

using namespace std;
  
int main(int argc, char**argv) {
    int arrSize = 0;
    
    //Reads in the array size and then initializes a new array to store the other numbers
    cin >> arrSize;
    int* nums = new int[arrSize];
    
    //Reads in the other numbers and stores them in array nums
    for(int i = 0; i < arrSize; i++) {
        cin >> nums[i];
    }

    //Starts with the second number in the list, compares it to the first and switches it if needed; then it keeps going until it gets to the end of the list
    int j;
    for(int i = 1; i < arrSize; i++) {
        j = i;
        //Keep comparing the current item in the list until it isn't less then the number before it
        while(j > 0 && nums[j] < nums[j-1]) {
            int temp = nums[j-1];
            nums[j-1] = nums[j];
            nums[j] = temp;
            j--;
        }
        //Print the output
        for(int k = 0; k < (i+1); k++) {
            cout << nums[k] << ";"; 
        }
        cout << endl;
    }
    delete [] nums;
}

