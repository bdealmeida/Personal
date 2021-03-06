// test of the DLList class

#include <iostream>
#include <cstdlib>
#include "DLList.h"

using namespace std;

int main ()
{
  // Construct a linked list with header & trailer
  cout << "Create a new list" << endl;
  DLList dll;
  cout << "list: " << dll << endl << endl;
  
  cout << "Insert 10 nodes at back with value 10,20,30,..,100" << endl;
  for (int i=10; i <= 100; i+=10) {
    dll.insert_last(i);
  }
  cout << "list: " << dll << endl << endl;

  cout << "Insert 10 nodes at front with value 10,20,30,..,100" << endl;
  for (int i=10; i <= 100; i+=10) {
    dll.insert_first(i);
  }
  cout << "list: " << dll << endl << endl;
  
  cout << "Copy to a new list" << endl;
  DLList dll2(dll);
  cout << "list2: " << dll2 << endl << endl;
  
  cout << "Assign to another new list" << endl;
  DLList dll3;
  dll3 = dll;
  cout << "list3: " << dll3 << endl << endl;
  
  cout << "Delete the last 10 nodes" << endl;
  for (int i=0; i < 10; i++) {
    dll.remove_last();
  }
  cout << "list: " << dll << endl << endl;
  
  cout << "Delete the first 10 nodes" << endl;
  for (int i=0; i < 10; i++) {
    dll.remove_first();
  }
  cout << "list: " << dll << endl << endl;
  
  // Check the other two lists
  cout << "Make sure the other two lists are not affected." << endl;
  cout << "list2: " << dll2 << endl;
  cout << "list3: " << dll3 << endl << endl;

  // more testing...
  // add tests for insert_after, insert_before
  cout << "Insert 2022 after the first 100 in list2" << endl;
  dll2.insert_after(*dll2.first_node(), 2022);
  cout << "list2: " << dll2 << endl << endl;

  cout << "Insert 41 before the 2022 in list2" << endl;
  dll2.insert_before(*dll2.first_node()->next, 41);
  cout << "list2: " << dll2 << endl << endl;

  // add tests for remove_after, remove_before
  cout << "Remove 2022 from list2" << endl;
  dll2.remove_after(*dll2.first_node()->next);
  cout << "list2: " << dll2 << endl << endl;

  cout << "Remove 41 from list2" << endl;
  dll2.remove_before(*dll2.first_node()->next->next);
  cout << "list2: " << dll2 << endl << endl;

  return 0;
}
