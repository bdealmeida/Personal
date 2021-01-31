#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

void swapInd(int* arr, int i1, int i2) {
    int t = arr[i1];
    arr[i1] = arr[i2];
    arr[i2] = t;
}

// Compares each adjacent index and swaps
// if needed; passes through some number
// of times until nothing needed to be swaped
// Number of comparisons is
// O(n^2), list needs to be iterated for every element
// Ω(n), when list is already sorted
void BubbleSort(int* arr, int n) {
    bool d;
    int c = 0;
    do {
        d = true;
        for(int i = 0; i < n-1; i++) {
            if(arr[i] > arr[i+1]) {
                swapInd(arr, i, i+1);
                d = false;
            }
            c++;
        }
    } while(!d);
    cout << "Comparisons = " << c << endl;
}

// Finds the smallest number for each pass,
// moves it to the front. The number of comparisons
// is N*(N - 1)/2 in O(n^2)
// θ(n^2), cannot exit early so both for loops must complete
void SelectionSort(int* arr, int n) {
    int i, j, m, c;  
  
    for (i = 0; i < n-1; i++) {
        m = i;  
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[m])  
                m = j;  
            c++;
        }
        swapInd(arr, m, i);
    }
    cout << "Comparisons = " << c << endl;
}

// Grows a seperate 'sorted list' by moving items from the
// unsorted list into it's place in the sorted one. Is one
// of the fastest algorithms for n <= 10
// O(n^2), when the list is sorted in reverse order all elements will need to be comp'd with rest of list
// Ω(n), when list is already sorted
void InsertionSort(int* arr, int n) {
    int c = 0;

    for(int i = 1; i < n; i++) {
        for(int j = i; j > 0; j--) {
            if(arr[j-1] > arr[j])
                swapInd(arr, j, j-1);
            c++;
        }
    }
    cout << "Comparisons = " << c << endl;
}

// Divides arr until each element is its own array, adj. arrays
// are then combined and sorted until arr is built back up
// O(n*log(n))
void Merge(int* arr, int s, int m, int e) { // Builds array back up, takes O(n) time
    int p = s, q = m+1, k = 0;

    int Arr[e-s+1]; // Array of n current objects being 'merged'

    for(int i = s; i <= e; i++) { // For every int in unmerged lists
        if(p > m)
            Arr[k++] = arr[q++];
        else if(q > e)
            Arr[k++] = arr[p++];
        else if(arr[p] < arr[q])
            Arr[k++] = arr[p++];
        else
            Arr[k++] = arr[q++];
    }
    for(int p = 0; p < k; p++)
        arr[s++] = Arr[p];
}
void MergeSort(int* arr, int s, int e) { // Breaks array down recursively, takes O(log(n)) time
    if( s < e) {
       int m = (s + e) / 2;
       MergeSort(arr, s, m);
       MergeSort(arr, m+1, e); 

       Merge(arr, s, m, e);
    }
}
void MergeSort(int* arr, int n) { MergeSort(arr, 0, n-1); } // Init for easy starting call

void partition(int* arr, int s, int e) {
    
}
void QuickSort(int* arr, int s, int e) {
    srand(time(NULL)); // Make sure rand is initialized


}
void QuickSort(int* arr, int n) { QuickSort(arr, 0, n-1); } // Init for easy starting call

void PrintItems(int* arr, int len) {
    std::cout << "[";
    for(int i = 0; i < len-1; i++)
        std::cout << arr[i] << ", ";
    std::cout << arr[len-1] << "]" << std::endl;
}