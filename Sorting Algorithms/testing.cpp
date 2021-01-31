#include "functions.h"
#include<cstdlib>
#include<ctime>

using namespace std;

int main() {
    srand(time(nullptr)); // Init randomizer with current time

    int n = 1000;

    // Populate list with n random #s, 0 <= # <= 100
    int arr[n];
    for(int i = 0; i < n; i++)
        arr[i] = rand() % 100 + 1;
    
    cout << "Unsorted list: ";
    PrintItems(arr, n);

    InsertionSort(arr, n);
    swapInd(arr, 0, n-1);
    cout << "Sorted list:   ";
    PrintItems(arr, n);

    //delete arr;

    return 0;
}