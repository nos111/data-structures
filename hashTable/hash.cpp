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

class Table {
  struct Slot * tableContent;
  int tableSize;
  int hash(int key, int trial);
  public:
    void insert(int key, int data);
    void deleteElement(int key);
    int find(int key);
    Table() {
      tableContent = new Slot [1024];
      tableSize = 1024;
    }
    Table(int size) {
      tableContent = new Slot [size];
      tableSize = size;
    }
    ~Table() {
      /*
      for(int i = 0; i < tableSize; i++) {
        struct Slot temp = tableContent[i];
        delete(temp.element);
      }*/
      delete [] tableContent;
    }
};

void Table::insert(int key, int data) {
  int trial = 1;
  int index = hash(key, trial);
  std::cout << "the new index is " << index << " \n";
  struct Slot * temp = &tableContent[index];
  std::cout << "the slot bool is  " << temp->empty << " \n";
  while(!temp->empty) {
    trial += 1;
    index = hash(key, trial);
    std::cout << "the new index is " << index << " \n";
    temp = &tableContent[index];
  }
  temp->element->key = key;
  temp->element->data = data;
  temp->empty = false;
  temp->deleted = false;
}

void Table::deleteElement(int key) {
  int trial = 1;
  int index = hash(key, trial);
  struct Slot * temp = &tableContent[index];
  while(temp->empty == false || temp->deleted == true) {
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
  int trial = 1;
  int index = hash(key, trial);
  struct Slot * slot = &tableContent[index];
  while(slot->empty == false || slot->deleted == true) {
    std::cout << "the slot empty is  " << slot->empty << " \n";
    std::cout << "the slot deleted is  " << slot->deleted << " \n";
    std::cout << "the slot key is  " << slot->element->key << " \n";
    if(slot->element->key == key) return slot->element->data;
    trial += 1;
    index = hash(key, trial);
    slot = &tableContent[index];
  }
  return 0;
}

//double hashing to avoid clustering
int Table::hash(int key, int trial) {
  int hash1 = ((3 * key + 4) % 17) % tableSize;
  int hash2 = ((11 * key + 19) % 17) % tableSize;
  hash2 = (hash1 + trial * hash2) % tableSize;
  std::cout << "the new hash is " << hash2 << "\n";
  return hash2;
}

int main() {
  Table * t = new Table();
  t->insert(10, 5);
  t->insert(20, 20);
  t->insert(20, 20);
  t->insert(500, 20);
  std::cout << " the value in key 500 is " << t->find(500) << " \n";
  t->deleteElement(500);
  std::cout << " the value in key 500 is " << t->find(500) << " \n";
  std::cout << " the value in key 10 is " << t->find(10) << " \n";
  std::cout << " HELLO ME \n";
  delete t;
  return 0;
}