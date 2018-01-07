#include <iostream>

template <typename T>
class Node {
        T info;
        Node * next;
    public:
        Node() {
            next = nullptr;
        }
        Node(T data) {
            info = data;
            next = nullptr;
        }
        void setNext(Node * newNode);
        void setInfo(T data);
        T getInfo();
        Node<T> * getNext();
        ~Node() {};
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
T Node<T>::getInfo() {
    return info;
}

template <typename T>
Node<T> * Node<T>::getNext() {
    return next;
}


template <typename T>
class Stack {
    Node<T> * top;
   
    public:
        Stack() {
            top = nullptr;
        }
        void push(T info);
        void print();
        Node<T> * pop();
        Node<T> * peek();
        ~Stack() {
            while(top != nullptr) {
                Node<T> * temp = top;
                top = top->getNext();
                delete temp;
            }
            delete top;
        }
};

template <typename T>
void Stack<T>::push(T info) {
    Node<T> * newNode = new Node<T>(info);
    if (top != nullptr) {
        newNode->setNext(top);
    }
    top = newNode;
}

template <typename T>
Node<T> * Stack<T>::pop() {
    if(top == nullptr) {
        std::cerr << "stack is empty";
    }
    Node<T> * temp = top;
    top = top->getNext();
    //temp->setNext(nullptr);
    return temp;
}

template <typename T>
Node<T> * Stack<T>::peek() {
    if(top == nullptr) {
        std::cerr << "stack is empty";
    }
    return top;
}

template <typename T>
void Stack<T>::print() {
    Node<T> * temp = top;
    while(temp != nullptr) {
        std::cout << temp->getInfo() << '\n';
        temp = temp->getNext();
    }
}


int main() {
    Stack<int> stack;
    for (int i = 0; i < 10; i++) {
        stack.push(i);
    }
    stack.print();
    return 0;
}