#include <iostream>
#include <stdio.h>
#include <sys/time.h>
using namespace std;

int main() {
    int n, firstTerm = 1, secondTerm = 1, nextTerm;
    cout << "Enter number of terms: ";
    cin >> n;

    cout << "Fibonacci Series: " << firstTerm << " + " << secondTerm << " + ";
	
    struct timeval tv;
    gettimeofday(&tv, NULL);
    cout << "seconds: " << tv.tv_sec << "microseconds: " << tv.tv_usec << endl;

    //measure the execution time of the following loop
    for (int i = 1; i <= n-2; ++i) {
        nextTerm = firstTerm + secondTerm;
        cout << nextTerm << " + ";
        firstTerm = secondTerm;
        secondTerm = nextTerm;
    }

    gettimeofday(&tv, NULL);
    cout << "seconds: " << tv.tv_sec << "microseconds: " << tv.tv_usec << endl;
    return 0;
}
