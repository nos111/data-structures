#include <iostream>
#include "hash.hpp"


void fillTable(Table * table, int tableSize) {
  for(int i = 0; i < tableSize; i++) {
    table->insert(i, i * 2);
  }
}

bool checkTableContent(Table * table, int tableSize) {
  for(int i = 0; i < tableSize; i++) {
    int data = table->find(i);
    if(data != i * 2) {
      std::cerr << "found error on index " << i << " \n";
      return false;
    }
  }
  return true;
}

bool checkDeletion(Table * table, int tableSize) {
  for(int i = 0; i < tableSize; i++) {
    std::cout << " LOOPING \n";
    table->deleteElement(i);
    std::cout << " finished deletiong \n";
    int data = table->find(i);
    if(data != 0) {
      std::cerr << "found error on index " << i << " \n";
      return false;
    }
  }
  return true;
}
int main() {
  int tableSize = 128;
  Table * t = new Table(tableSize * 2);
  fillTable(t, tableSize);
  if(checkTableContent(t, tableSize)) std::cout << "No errors were encountered in filling and finding \n" ;
  //if(checkDeletion(t, tableSize)) std::cout << "No errors were encountered in deletion \n" ;
  return 0;
}