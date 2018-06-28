#include <iostream>

template <typename T>
struct Node {
  T data;
  Node * next;
  Node * prev;
  Node() {
    next = nullptr;
    prev = nullptr;
  }
};

template <typename T>
class circularList {
  Node<T> * tail;
  public:
    void addNode(T data);
    bool removeNode(T data);
    Node<T> * iterator();
    void printList();
    circularList() {tail = nullptr;};
};

template <typename T>
void circularList<T>::addNode(T data) {
  Node<T> * newNode = new Node<T>();
  newNode->data = data;
  if(tail != nullptr) {
    Node<T> * head = tail->next;
    tail->next = newNode;
    newNode->prev = tail;
    newNode->next = head;
    head->prev = newNode;
  } else {
    tail = newNode;
    newNode->next = newNode;
    newNode->prev = newNode;
  }
}

template <typename T>
bool circularList<T>::removeNode(T data) {
  if(tail == nullptr) return false;
  Node<T> * first = tail;
  Node<T> * temp = tail;
  while(temp->data != data) {
    temp = temp->next;
    if(temp == first) return false;
  }
  if(temp->next != temp) {
    temp->next->prev = temp->prev;
    temp->prev->next = temp->next;
    if(temp == tail) tail = temp->next;
    free(temp);
  } else {
    free(tail);
    tail = nullptr;
  }
}

template <typename T>
void circularList<T>::printList() {
  if(tail == nullptr) return;
  if(tail->next == tail) {
    std::cout << tail->data << "\n";
    return;
  }
  Node<T> * first = tail;
  Node<T> * temp = tail->next;
  while(temp != first) {
    std::cout << temp->data << " ";
    temp = temp->next;
  }
  std::cout << temp->data << " \n";
}

int main() {
  circularList<int> * cl = new circularList<int>();
  cl->printList();
  cl->addNode(10);
  cl->printList();
  cl->addNode(11);
  cl->addNode(12);
  cl->addNode(13);
  cl->printList();
  cl->removeNode(10);
  cl->printList();
  std::cout << "hello me \n";
  return 0;
}