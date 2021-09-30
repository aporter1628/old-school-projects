//Insertion sort

#include <iostream>


using namespace std;
  
int main(int argc, char**argv) {
    int arrSize = 0;
    
    cin >> arrSize;
    int* arr = new int[arrSize];

    for(int i = 0; i < arrSize; i++) {
        cin >> arr[i];
    }

    for(int i = 1; i < arrSize; i++) {
        for(int j = i; j > 0; j--) {
            if (arr[j] < arr[j-1]) {
               temp = arr[j-1];
               arr[j-1] = arr[j];
               arr[j] = temp;
            }
        }
        for(int k = 0; k < i; k++) {
            cout << arr[k] + ";"; 
        }
        cout << endl;
    }
    delete [] arr;
}

