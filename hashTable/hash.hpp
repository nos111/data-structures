#ifndef __HASH_HPP_INCLUDED__   
#define __HASH_HPP_INCLUDED__  

class Table {
  struct Slot * tableContent;
  int tableSize;
  int hash(int key, int trial);
  public:
    void insert(int key, int data);
    void deleteElement(int key);
    int find(int key);
    Table();
    Table(int size);
    ~Table();
};

#endif 
