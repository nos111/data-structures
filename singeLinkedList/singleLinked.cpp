#include <iostream>

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
         Node<T> * findNode(std::string name);
        void addNode(T info, std::string name);
        void print();
        void deleteNode(std::string name);
        ~SingleLinkedList() {
            delete first;
        }
};

template <typename T>
void SingleLinkedList<T>::addNode(T info, std::string name) {
    Node<T> * newNode = new Node<T>();
    newNode->setInfo(info);
    newNode->setName(name);
    if (last != nullptr) {
        last->setNext(newNode);
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
    if(first->getName() == name) {
        return first;
    }
    Node<T> * temp = first;
    while(temp->getNext() != nullptr) {
        if(temp->getNext()->getName() == name) {
            return temp->getNext();
        } 
        temp = temp->getNext();
    }
    std::cerr << "Node not found";
    return nullptr;
}


template <typename T>
void SingleLinkedList<T>::deleteNode(std::string name) {
    if(first == nullptr) {
        std::cerr << "List is empty";
    }
    Node<T> * temp = first;
    if(first->getName() == name) {
        first = first->getNext();
        temp->setNext(nullptr);
        delete temp;
        return;
    }
    while(temp->getNext() != nullptr) {
        if(temp->getNext()->getName() == name) {
            //check if the element is the last element in the list
            if(temp->getNext()->getNext()!= nullptr) {
                Node<T> * temp2 = temp->getNext();
                temp->setNext(temp->getNext()->getNext());
                temp2->setNext(nullptr);
                delete temp2;
            } else {
                Node<T> * temp2 = temp->getNext();
                delete temp2;
                temp->setNext(nullptr);
            }
        } 
        if(temp->getNext() != nullptr) temp = temp->getNext();
        
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
    SLS.addNode(100, "nour");
    SLS.deleteNode("5");
    SLS.deleteNode("0");
    SLS.print();

    return 0;
}