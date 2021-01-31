#ifndef HASHING_H
#define HASHING_H

#include<iostream>
#include<vector>

using namespace std;

struct Node {
    int val;
    Node* next;

    Node(int val = 0, Node* next = nullptr): val(val), next(next) {}
};

class Hash {
    private:
        int size, capacity;
        vector<Node*> list;

        void resize(int n);
        int linearProbe(int i);
        void removeNode(int i);
        void removeNode(int i, int n);
    public:
        // constructors
        Hash(): size(0), capacity(0) {}
        Hash(int arr[], int n);
        Hash(int n);
        Hash(const Hash& other);
        // move constructor
        Hash(Hash&& other);
        // copy assignment
        Hash& operator=(const Hash& other);
        // move assignment
        Hash operator=(Hash&& other);
        ~Hash();

        const Node* operator[](int i) const {
            return list[i];
        }

        void linearInsert(int n);
        int linearSearch(int n);
        void linearDelete(int n);

        int getCapacity() {
            return capacity;
        }
};

ostream& operator<<(ostream& out, Hash& hash);

#endif