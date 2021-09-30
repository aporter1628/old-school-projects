#include<iostream>
#include<vector>
#include <stdlib.h>
#include <string>
using namespace std;
/*
struct Link {
    int data;
    Link* next;
};

void add(Link* head, int value){
    // Create the new link and store value in it
    Link* newItem = new Link;
    newItem->data = value;
    newItem->next = NULL;
    
    // Find the end of the linked list
    Link* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newItem;
}*/

/*void bucketSort(vector<vector int> > v, int arrSize, int key) {
    vector<int> B[arrSize]; //Makes the bucket, which is a vector
    //The vectors can already hold seperate lists so the next step of the pseudocode isn't needed

    //Put the elements of A into the right buckets
    for(int i=0; i < 9, i++) {
        B[floor(arrSize*v[i][key])].push_back(v[i]);
    }

    //Concatenate all the lists
    for(i = 0; k < 10; k++) {
       v[i] = B[i];
    } 
    //return v;
}*/

/*void bucketSort(int* A, int arrSize, int key) {
    Link ** bucket = new Link[arrSize];
    for(int i = 0; i < arrSize; i++) 
        bucket[i] = new Link;

    //Put the elements of A into the right buckets
    for(int i=0; i < arrSize-1, i++) {
        bucket[floor(arrSize*A[i])].add(A[i]);
    }

    i = 0;
    //Concatenate all the lists
    for(int k = 0; k < arrSize; k++) {
        for(int j = 0; j < bucket[i].size(); j++) {
            A[i] = bucket[i][j];
            i++;
        }
    }
}*/

void bucketSort(int** A, int arrSize, int key) {
    //Create a 2D vector that contains the buckets
    //We know that every value is between 0 and 3 so we only need 4 buckets, and every bucket can't have more than arrSize*10 elements
    vector <vector<int*> > buckets(4, vector<int*> (arrSize*10));

    //We don't need the next step of the pseudocode because every bucket already contains an empty vector

    //Looks at the key index's value of every array and places the address of that array into bucket 0-3 depending on the value of the key index's value
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < arrSize; j++) {
            buckets[A[j][key]].push_back(&(A[j][0]));
        }
    }

    //Puts all the arrays back into A, depending on their placement in the bucket
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < arrSize; j++) {
            A[j][0] = *(buckets[i][j]);
        }
    }    
}

void radixSort(int** arr1, int arrSize) {
    for(int i = 0; i < 10; i++) {
        bucketSort(arr1, arrSize, i);
    }
}

int main() {
    int arrSize;
    cin >> arrSize;

    //Initializes the 2D array, which has arrSize columns and 10 rows
    int** arr1 = new int*[arrSize];
    for(int i = 0; i < 10; i++) {
        arr1[i] = new int[i];
    }

    //Fills the 2D array with the input values
    for(int i = 0; i < arrSize; i++) {
        for(int j = 0; j < 10; j++) {
            cin >> arr1[i][j];
        }
    }
    //Calls radixSort on the double array
    radixSort(arr1, arrSize);

    for(int i = 0; i < arrSize; i++) {
        for(int j = 0; j < 10; j++) {
            cout << arr1[i][j] << ";";
        }
        cout << endl;
    }
}
    
/* FOR VECTORS
void radixSort(vector<vector int> > v1, int arrSize) {
    for(int i = 0; i < 10; i++) {
        bucketSort(v1, arrSize, i);
    }
    //return v1;
    
}

int main() {
    int arrSize;
    cin >> arrSize;
    //Creates a double vector, with arrSize number of vectors, each with size 10
    vector <vector<int> > v1(arrSize, vector<int> (10));
    
    for(int i = 0; i < arrSize; i++) {
        for(int j = 0; j < 10; j++) {
            cin >> v1[i][j];
        }
    }
    
    radixSort(v1, arrSize);

    for(i = 0; i < arrSize, i++) {
        for(j = 0; j < 10; j++) {
            cout << v1[i][j] << ";";
        }
        cout << endl;
    }
}*/
