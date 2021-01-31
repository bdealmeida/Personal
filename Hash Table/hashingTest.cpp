#include "hashing.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<chrono>

using namespace std;

int genArr(int n) {
    int res[n];

    return *res;
}

int main() {
    srand(time(NULL));

    int n = 10;

    Hash linHash(n);

    //cout << "Created object - node pointer at index 0 has a value of " << linHash[0] << endl;

    for(int i = 0; i < n; i++)
        linHash.linearInsert(rand() % n + 1);

    //cout << "Inserted 5 into hash - hash now has capacity of " << linHash.getCapacity() << endl;

    cout << "hash: " << linHash << endl;

    int toDel = rand() % n + 1;
    cout << "Key " << toDel << " is at index " << linHash.linearSearch(toDel) << endl;

    linHash.linearDelete(toDel);

    cout << "hash: " << linHash << endl;

    //cout << "(Deleted) key 16 is at index " << linHash.linearSearch(16) << endl;

    return 0;
}