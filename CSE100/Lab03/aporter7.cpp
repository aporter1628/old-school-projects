#include <iostream>

using namespace std;

int findMaxCrossingSubarray(int* list, int first, int mid, int last) {
    //The left sum is initialized to be the lowest possible number
    int ls = -2147483647;
    int sum = 0; 
    //Descend from the middle of the list to the beginning and keep updating the ls to be the largest sum between the arrays
    for (int i = mid; i >= first; i--){
        sum = sum + list[i];
        if (sum > ls) {
            ls = sum;
        }
    }
    
    int rs = -2147483647 ;
    sum = 0; 
    //Ascend from the one after the middle of the list to the last element and keep updating rs to be the largest sum between the arrays
    for(int i = mid+1; i <= last; i++) {
        sum = sum + list[i];
        if (sum > rs) {
            rs = sum;
        }
    }
    //The largest sum that crosses over must be the largest sum on the left plus the largest sum on the right, so return that
    return(ls+rs);
}

int findMaxSubarray(int* list, int first, int last) {
    //If there is only one element
    if(first == last) {
        return(first + last);
    }

    else {
    int mid = (first+last)/2;
    //Finds the max subarray on the left side, the right side, and the one that crosses over
    int leftSum = findMaxSubarray(list, first, mid);
    int rightSum = findMaxSubarray(list, mid+1, last);
    int crossSum = findMaxCrossingSubarray(list, first, mid, last);
    
    //Return the highest sum
    if(leftSum >= rightSum && leftSum >= crossSum) 
        return leftSum;
    else if(rightSum >= leftSum && rightSum >= crossSum) 
        return rightSum;
    else
        return crossSum;
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
    
    int answer = findMaxSubarray(nums, 0, arrSize-1);

    cout << answer;


}




            
            
