// implementation of the DLList class

#include <stdexcept>
#include "DLList.h"


// extend runtime_error from <stdexcept>
struct EmptyDLList : public std::runtime_error {
  explicit EmptyDLList(char const* msg=nullptr): runtime_error(msg) {}
};


// copy constructor
DLList::DLList(const DLList& dll) {
  if(header.next != nullptr && header.next != 0) {
    // Deallocate currently saved list
    while(!is_empty()) {
      remove_first();
    }

    header.next = &trailer;
    trailer.prev = &header;
  }
  
  if(dll.is_empty()) {
    header.next = &trailer;
    trailer.prev = &header;
  } else {
    // Use a pointer going to the old dll to advance progress of the deep copy
    DLListNode* tmpOld = dll.first_node();
    DLListNode* tmp = new DLListNode(dll.first(), &header, nullptr);
    header.next = tmp;

    while(tmpOld->next != dll.after_last_node()) {
      tmpOld = tmpOld->next;
      tmp = new DLListNode(tmpOld->obj, tmp, nullptr);
      tmp->prev->next = tmp;
    }
    tmp->next = &trailer;
    trailer.prev = tmp;
  }
}

// move constructor
DLList::DLList(DLList&& dll) {
  header = *dll.first_node()->prev;
  trailer = *dll.after_last_node();

  dll.removeOwnership();
}

// copy assignment operator
DLList& DLList::operator=(const DLList& dll) {
  if(header.next != nullptr && header.next != 0) {
    // Deallocate currently saved list
    while(!is_empty()) {
      remove_first();
    }

    header.next = &trailer;
    trailer.prev = &header;
  }
  
  if(dll.is_empty()) {
    header.next = &trailer;
    trailer.prev = &header;
  } else {
    // Use a pointer going to the old dll to advance progress of the deep copy
    DLListNode* tmpOld = dll.first_node();
    DLListNode* tmp = new DLListNode(dll.first(), &header, nullptr);
    header.next = tmp;

    while(tmpOld->next != dll.after_last_node()) {
      tmpOld = tmpOld->next;
      tmp = new DLListNode(tmpOld->obj, tmp, nullptr);
      tmp->prev->next = tmp;
    }
    tmp->next = &trailer;
    trailer.prev = tmp;
  }
  
  return *this;
}

// move assignment operator
DLList& DLList::operator=(DLList&& dll) {
  if(&dll == this)
    return *this;

  header = *dll.first_node()->prev;
  trailer = *dll.after_last_node();

  dll.removeOwnership();

  return *this;
}

// destructor
DLList::~DLList() {
  while(!is_empty())
    remove_first();
  header.next = nullptr;
  trailer.prev = nullptr;
}

// insert a new object as the first one
void DLList::insert_first(int obj) { 
  DLListNode* tmp = new DLListNode(obj, &header, header.next);
  header.next->prev = tmp;
  header.next = tmp;
}

// insert a new object as the last one
void DLList::insert_last(int obj) {
  DLListNode* tmp = new DLListNode(obj, trailer.prev, &trailer);
  trailer.prev->next = tmp;
  trailer.prev = tmp;
}

// remove the first node from the list
int DLList::remove_first() {
  //cout << "Removing first node... ";

  int tmp = first(); 

  //cout << "Delinking the first node... ";

  DLListNode* toRemove = header.next;
  header.next = toRemove->next;
  toRemove->next->prev = &header;

  //cout << "Deallocating removed first node." << endl;

  toRemove->obj = 0;
  toRemove->next = nullptr;
  toRemove->prev = nullptr;

  return tmp;
}

// remove the last node from the list
int DLList::remove_last() {
  int tmp = last(); 

  DLListNode* toRemove = trailer.prev;
  trailer.prev = toRemove->prev;
  toRemove->prev->next = &trailer;

  toRemove->obj = 0;
  toRemove->next = nullptr;
  toRemove->prev = nullptr;

  return tmp;
}

// return the first object (do not remove)
int DLList::first() const { 
  return header.next->obj;
}

// return the last object (do not remove)
int DLList::last() const {
  return trailer.prev->obj;
}

// insert a new node after the node p
void DLList::insert_after(DLListNode &p, int obj) {
  DLListNode* tmp = new DLListNode(obj, &p, p.next);
  p.next->prev = tmp;
  p.next = tmp;
}

// insert a new node before the node p
void DLList::insert_before(DLListNode &p, int obj) {
  DLListNode* tmp = new DLListNode(obj, p.prev, &p);
  p.prev->next = tmp;
  p.prev = tmp;
}

// remove the node after the node p
int DLList::remove_after(DLListNode &p) {
  DLListNode* toRemove = p.next;

  p.next = toRemove->next;
  toRemove->next->prev = &p;

  toRemove->obj = 0;
  toRemove->next = nullptr;
  toRemove->prev = nullptr;
}

// remove the node before the node p
int DLList::remove_before(DLListNode &p) {
  DLListNode* toRemove = p.prev;

  p.prev = toRemove->prev;
  toRemove->prev->next = &p;

  toRemove->obj = 0;
  toRemove->next = nullptr;
  toRemove->prev = nullptr;
}

// output operator
ostream& operator<<(ostream& out, const DLList& dll) {  
  if(!dll.is_empty()) {
    DLListNode* tmp = dll.first_node();
    //cout << "Trailer is at " << dll.after_last_node() << endl;

    //cout << "Found first node at " << tmp << endl << "The node after that is at " << tmp->next << endl << "and the trailer is at " << dll.after_last_node() << endl;
    out << "[";
    while(tmp->next != dll.after_last_node() && tmp->next != nullptr && tmp->next != 0) {
      //std::cout << "Adding " << tmp << " to out." << endl << "Tmp will now be " << tmp->next << endl;
      out << tmp->obj << ", ";

      tmp = tmp->next;
    }

    //cout << endl << "TEMP IS NOW " << tmp << endl << "TRAILER IS " << dll.after_last_node() << endl << "TEMP CONTAINS " << tmp->obj << endl << "TEMP>NEXT IS " << tmp->next << endl;

    if(tmp != dll.after_last_node())
      out << tmp->obj << "]";
    else
      out << "]";
  } else
    out << "[]";

  return out;
}
