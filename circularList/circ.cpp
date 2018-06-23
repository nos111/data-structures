#include <iostream>

template <typename T>
struct Node {
  T data;
  Node * next;
  Node * prev;
};

template <typename T>
class circularList {
  Node<T> * head;
  public:
    void addNode(Node<T> * newNode);
    void removeNode(T data);
    Node<T> * iterator();
    circularList();
};


int main() {
  std::cout << "hello me \n";
  return 0;
}