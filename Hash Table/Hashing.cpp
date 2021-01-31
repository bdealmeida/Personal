#include "Hashing.h"
#include<vector>

void Hash::resize(int n) {
    list.resize(n);
}

int Hash::linearProbe(int i) {
    while(list[i] != nullptr)
        if(i + 1 < capacity)
            i++;
        else
            i = 0;
    
    //cout << "Found place at index " << i << endl;
    return i;
}

void Hash::removeNode(int i) {
    //cout << "Removing node at " << i << endl;
    list[i]->val = 0;
    if(list[i]->next != nullptr) {
        Node* temp = list[i]->next;
        list[i]->next = nullptr;
        list[i] = temp;
    } else
        list[i] = nullptr;
    
    size--;
}

void Hash::removeNode(int i, int n) {
    if(list[i]->val = n) {
        removeNode(i);
        return;
    }

    Node* back;
    Node* temp = list[i];

    while(temp->val != n && temp->next != nullptr) {
        back = temp;
        temp = temp->next;
    }
    
    if(temp->val == n) {
        temp->val = 0;
        back->next = temp->next;
        temp->next = nullptr;
    }
}

// Array constructor
Hash::Hash(int arr[], int n) {
    size = n;
    capacity = n;
    vector<Node*> list;

    for(int i = 0; i < n; i++)
        list.push_back(new Node(arr[i]));
}

Hash::Hash(int n) {
    list.resize(n);
    capacity = n;
    size = 0;

    for(int i = 0; i < capacity; i++)
        if(list[i] != nullptr)
            removeNode(i);
        else
            list[i] = nullptr;
}

// copy constructor
Hash::Hash(const Hash& other) {
    size = other.size;
    capacity = other.capacity;

    vector<Node*> list;

    for(Node* n : other.list)
        list.push_back(n == nullptr ? nullptr : new Node(n->val));
}

// move constructor
Hash::Hash(Hash&& other) {
    size = other.size;
    capacity = other.capacity;
    vector<Node*> list(other.list);

    other.size = 0;
    other.capacity = 0;
    other.list.clear();
}

// copy assignment
Hash& Hash::operator=(const Hash& other) {
    if(this == &other)
        return *this;
    
    if(size != 0)
        for(int i = 0; i < size; i++)
            list[i] = 0;

    size = other.size;
    capacity = other.capacity;

    vector<Node*> list(other.list);
}

// move assignment
Hash Hash::operator=(Hash&& other) {
    if(this == &other)
        return *this;
    
    if(size != 0)
        for(int i = 0; i < size; i++)
            list[i] = 0;
    
    size = other.size;
    capacity = other.capacity;
    vector<Node*> list(other.list);

    other.size = 0;
    other.capacity = 0;
    other.list.clear();
}

// Deconstructor
Hash::~Hash() {
    //cout << "Deconstructing" << endl;
    bool searching = true;

    while(searching) {
        searching = false;

        for(int i = 0; i < capacity; i++)
            if(list[i] != nullptr) {
                //cout << "Found node at " << i << "... removing top level of index." << endl;
                removeNode(i);
                searching = true;
            }
    }

    //cout << "Finished deconstructing!" << endl;
}

void Hash::linearInsert(int n) {
    //cout << "Inserting..." << endl;
    if(size == capacity) {
        list.push_back(nullptr);
        capacity++;
    }
    
    int i = n % capacity;
    /*cout << "Attemping to place " << n << " at index " << i << endl;
    //cout << "Is i clear? ";
    if(list[i] == nullptr)
        cout << "CLEAR" << endl;
    else
        cout << "NOT CLEAR" << endl;*/
    list[ (list[i] == nullptr) ? i : linearProbe(i)] = new Node(n);
    size++;
}

int Hash::linearSearch(int n) {
    int i = n % capacity;
    if(list[i] != nullptr && list[i]->val == n)
        return i;

    int temp = (i == capacity - 1) ? 0 : i + 1;

    // Go at least one circle around the hash to search for n
    while(temp != i) {
        //cout << "Temp = " << temp << ", i = " << i << ", capacity = " << capacity << endl;

        if(list[temp] != nullptr && list[temp]->val == n)
            return temp;
        
        //cout << "Search term n not found at index " << temp << endl;;

        temp++;
        if(temp == capacity)
            temp = 0;
    }

    return -1;
}

void Hash::linearDelete(int n) {
    int i = n % capacity;
    if(list[i] != nullptr && list[i]->val == n) {
        removeNode(i);
        return;
    }
    
    int temp = (i == capacity - 1) ? 0 : i + 1;

    // Go at least one circle around the hash to search for n
    while(temp != i) {
        if(list[temp] != nullptr && list[temp]->val == n) {
            removeNode(temp);
            return;
        }
        
        temp++;
        if(temp == capacity)
            temp = 0;
    }
}

ostream& operator<<(ostream& out, Hash& hash) {
    out << "[";

    for(int i = 0; i < hash.getCapacity() - 1; i++) {
        if(hash[i] == nullptr)
            out << "-";
        else
            out << hash[i]->val;
        
        out << ", ";
    }

    if(hash[hash.getCapacity()-1] == nullptr)
        out << "-]";
    else
        out << hash[hash.getCapacity()-1]->val << "]";

    return out;
}