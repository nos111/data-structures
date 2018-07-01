#include <iostream>

struct Element {
  int key;
  int data;
  Element(int newKey, int newData) {
    key = newKey;
    data = newData;
  }
};

struct Slot {
  struct Element * element;
  bool deleted;
};

void insert(int key, int data) {

}

void deleteElement(int key) {

}

void find(int key) {

}

int hash(int key, int trial, int tableSize) {

}

int main() {
  std::cout << " HELLO ME \n";
  return 0;
}