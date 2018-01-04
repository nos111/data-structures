#include <iostream>
#include <sstream>

template <typename T>
class Node {
        std::string name;
        T info;
        Node * next;
    public:
        Node() {
            next = nullptr;
            name = "";
        }
        void setNext(Node * newNode);
        void setInfo(T data);
        void setName(std::string n);
        std::string getName();
        T getInfo();
        Node<T> * getNext();
        ~Node() {
            delete next;
        };
};

template <typename T>
void Node<T>::setNext(Node * newNode) {
    next = newNode;
}

template <typename T>
void Node<T>::setInfo(T data) {
    info = data;
}

template <typename T>
void Node<T>::setName(std::string n) {
    name = n;
}


template <typename T>
std::string Node<T>::getName() {
    return name;
}


template <typename T>
T Node<T>::getInfo() {
    return info;
}

template <typename T>
Node<T> * Node<T>::getNext() {
    return next;
}


template <typename T>
class SingleLinkedList {
    Node<T> * last;
    Node<T> * first;
    public:
        SingleLinkedList() {
            first = nullptr;
            last = nullptr;
        }
        void addNode(T info);
        void print();
        ~SingleLinkedList() {
            delete first;
        }
};

template <typename T>
void SingleLinkedList<T>::addNode(T info) {
    Node<T> * newNode = new Node<T>();
    newNode->setInfo(info);
    if (last != nullptr) {
        last->setNext(newNode);
        last = last->getNext();
    } else {
        first = newNode;
        last = newNode;
    }
}

template <typename T>
void SingleLinkedList<T>::print() {
    Node<T> * temp = first;
    while(temp != nullptr) {
        std::cout << temp->getInfo() << '\n';
        temp = temp->getNext();
    }
}

int main() {
    SingleLinkedList<int> SLS;
    
    for (int i = 0; i < 10; i++) {
        SLS.addNode(i);
    }
   // Node<int> * b  = new Node<int>;
    //b->info = 6;
    //SLS.append(b);
    SLS.addNode(100);
    SLS.print();
    return 0;
}