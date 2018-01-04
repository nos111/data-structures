#include <iostream>

template <typename T>
class Node {
        std::string name;
        T info;
        Node * next;
        Node * prev;
    public:
        Node() {
            next = nullptr;
            prev = nullptr;
            name = "";
        }
        Node(T data, std::string NewNodeName) {
            name = NewNodeName;
            info = data;
            next = nullptr;
            prev = nullptr;
        }
        void setNext(Node * newNode);
        void setPrev(Node * newNode);
        void setInfo(T data);
        void setName(std::string n);
        std::string getName();
        T getInfo();
        Node<T> * getNext();
        Node<T> * getPrev();
        ~Node() {
            delete next;
        };
};

template <typename T>
void Node<T>::setNext(Node * newNode) {
    next = newNode;
}

template <typename T>
void Node<T>::setPrev(Node * newNode) {
    prev = newNode;
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
Node<T> * Node<T>::getPrev() {
    return prev;
}


template <typename T>
class DoubleLinkedList {
    Node<T> * last;
    Node<T> * first;
   
    public:
        DoubleLinkedList() {
            first = nullptr;
            last = nullptr;
        }
        Node<T> * findNode(std::string name);
        void addNode(T info, std::string name);
        void print();
        void deleteNode(std::string name);
        void addAfterNode(std::string name, T data, std::string newNodeName);
        ~DoubleLinkedList() {
            delete first;
        }
};

template <typename T>
void DoubleLinkedList<T>::addNode(T info, std::string name) {
    Node<T> * newNode = new Node<T>(info, name);
    if (last != nullptr) {
        last->setNext(newNode);
        newNode->setPrev(last);
        last = last->getNext();
    } else {
        first = newNode;
        last = newNode;
    }
}

template <typename T>
Node<T> * DoubleLinkedList<T>::findNode(std::string name) {
    if(first == nullptr) {
        std::cerr << "List is empty";
        return nullptr;
    }
    Node<T> * temp = first;
    while(temp != nullptr) {
        if(temp->getName() == name) {
            return temp;
        } 
        temp = temp->getNext();
    }
    std::cerr << "Node not found";
    return nullptr;
}

template <typename T>
void DoubleLinkedList<T>::addAfterNode(std::string name, T data, std::string newNodeName) {
    Node<T> * newNode = new Node<T>(data, newNodeName);
    Node<T> * temp = findNode(name);
    newNode->setNext(temp->getNext());
    temp->setNext(newNode);
    newNode->setPrev(temp);
    newNode->getNext()->setPrev(newNode);
}

template <typename T>
void DoubleLinkedList<T>::deleteNode(std::string name) {
    if(first == nullptr) {
        std::cerr << "List is empty";
    }
    Node<T> * temp = nullptr;
    if(first->getName() == name) {
        temp = first;
        first = first->getNext();
        temp->setNext(nullptr);
        delete temp;
        return;
    }
    temp = findNode(name);
    if(temp->getNext() != nullptr) {
        temp->getNext()->setPrev(temp->getPrev());
        temp->getPrev()->setNext(temp->getNext());
        temp->setNext(nullptr);
        delete temp;
    } else {
        temp->getPrev()->setNext(nullptr);
        delete temp;
    }   
}

template <typename T>
void DoubleLinkedList<T>::print() {
    Node<T> * temp = first;
    while(temp != nullptr) {
        std::cout << temp->getInfo() << '\n';
        temp = temp->getNext();
    }
}

int main() {
    DoubleLinkedList<int> DLS;
    for (int i = 0; i < 10; i++) {
        DLS.addNode(i, std::to_string(i));
    }
    DLS.addAfterNode("5", 100, "nour");
    DLS.deleteNode("9");
    DLS.deleteNode("5");
    DLS.print();
    return 0;
}