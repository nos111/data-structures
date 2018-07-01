#include <iostream>

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
  Slot() {
    element = new Element();
    deleted = false;
  }
};

class Table {
  struct Slot * tableContent;
  int tableSize;
  int hash(int key, int trial, int tableSize);
  public:
    void insert(int key, int data);
    void deleteElement(int key);
    void find(int key);
    Table() {
      tableContent = new Slot[1024];
      tableSize = 1024;
    }
    Table(int size) {
      tableContent = new Slot[size];
      tableSize = size;
    }
};

void Table::insert(int key, int data) {
  return;
}

void Table::deleteElement(int key) {
  return;
}

void Table::find(int key) {
  return;
}

int Table::hash(int key, int trial, int tableSize) {
  return 0;
}

int main() {
  Table * t = new Table();

  std::cout << " HELLO ME \n";
  return 0;
}