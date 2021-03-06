#include <iostream>
#include "hash.hpp"

struct Element {
  int key;
  int data;
  Element(int newKey, int newData) {
    key = newKey;
    data = newData;
  }
  Element() { key = 0; data = 0;};
};

struct Slot {
  struct Element * element;
  bool deleted;
  bool empty;
  Slot() {
    element = new Element();
    deleted = false;
    empty = true;
  }
  ~Slot() {
    delete element;
  }
};


Table::Table() {
  tableContent = new Slot [1024];
  tableSize = 1024;
}

Table::Table(int size) {
  tableContent = new Slot [size];
  tableSize = size;
}

Table::~Table() {
  delete [] tableContent;
}

void Table::insert(int key, int data) {
  int trial = 0;
  int index = hash(key, trial);
  struct Slot * temp = &tableContent[index];
  //std::cout << "the slot bool is  " << temp->empty << " \n";
  while(!temp->empty) {
    trial += 1;
    index = hash(key, trial);
    //std::cout << "the key  is " << key << " \n";
    //std::cout << "the new index is " << index << " \n";
    temp = &tableContent[index];
  }
  temp->element->key = key;
  temp->element->data = data;
  temp->empty = false;
  temp->deleted = false;
}

void Table::deleteElement(int key) {
  int trial = 0;
  int index = hash(key, trial);
  //std::cout << "the key  is " << key << " \n";
  //std::cout << "the index is " << index << " \n";
  struct Slot * temp = &tableContent[index];
  while(temp->empty == false || temp->deleted == true) {
    //std::cout << " LOOPING \n";
    if(temp->element->key == key) {
      delete temp->element;
      temp->element = new Element();
      temp->deleted = true;
      return;
    }
    trial += 1;
    index = hash(key, trial);
    temp = &tableContent[index];
  }
}

int Table::find(int key) {
  int trial = 0;
  int index = hash(key, trial);
  struct Slot * slot = &tableContent[index];
  while(slot->empty == false || slot->deleted == true) {
    //std::cout << "the slot empty is  " << slot->empty << " \n";
    //std::cout << "the slot deleted is  " << slot->deleted << " \n";
    //std::cout << "the slot key is  " << slot->element->key << " \n";
    if(slot->element->key == key) return slot->element->data;
    trial += 1;
    index = hash(key, trial);
    if(index > tableSize || index < 0) {
      std::cout << "index error in finding \n";
      return 0;
    }
    slot = &tableContent[index];
    //if(trial == 15 ) throw ("too many trials");
  }
  return 0;
}

//double hashing to avoid clustering
int Table::hash(int key, int trial) {
  int hash1 = key % tableSize;
  int hash2 = 1 + (key % (tableSize - 1));
  hash2 = (hash1 + trial * hash2) % tableSize;
  //std::cout << "the new hash is " << hash2 << "\n";
  return hash2;
}
