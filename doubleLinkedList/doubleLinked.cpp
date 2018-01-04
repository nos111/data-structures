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
class SingleLinkedList {
    Node<T> * last;
    Node<T> * first;
   
    public:
        SingleLinkedList() {
            first = nullptr;
            last = nullptr;
        }
        Node<T> * findNode(std::string name);
        void addNode(T info, std::string name);
        void print();
        void deleteNode(std::string name);
        void addAfterNode(std::string name, T data, std::string newNodeName);
        ~SingleLinkedList() {
            delete first;
        }
};

template <typename T>
void SingleLinkedList<T>::addNode(T info, std::string name) {
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
Node<T> * SingleLinkedList<T>::findNode(std::string name) {
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
void SingleLinkedList<T>::addAfterNode(std::string name, T data, std::string newNodeName) {
    Node<T> * newNode = new Node<T>(data, newNodeName);
    Node<T> * temp = findNode(name);
    newNode->setNext(temp->getNext());
    temp->setNext(newNode);
    newNode->setPrev(temp);
    newNode->getNext()->setPrev(newNode);
    //std::cout << newNode->getPrev()->getName();
}

template <typename T>
void SingleLinkedList<T>::deleteNode(std::string name) {
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
        SLS.addNode(i, std::to_string(i));
    }
    SLS.addAfterNode("5", 100, "nour");
    SLS.deleteNode("9");
    SLS.deleteNode("5");
    SLS.print();
    return 0;
}