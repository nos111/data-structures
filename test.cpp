#include <iostream>
#include <memory>

template <typename T>
class Node {
    public:
        T info;
        Node * next = nullptr;
};

template <typename T>
class SingleLinkedList {
    Node<T> * last;
    Node<T>  * first;
    public:
        void append(Node<T>  * newNode);
        void print();
};

template <typename T>
void SingleLinkedList<T>::append(Node<T>  * newNode) {
    if (last != nullptr) {
        last->next = newNode;
        last = last->next;
    }
    if(first == nullptr) {
        first = newNode;
        last = newNode;
    }
}

template <typename T>
void SingleLinkedList<T>::print() {
    Node<T> * temp = first;
    while(temp != nullptr) {
        std::cout << temp->info << "\n";
        temp = temp->next;
    }
}

void addThings(SingleLinkedList<int> & SLS) {
    for (int i = 0; i < 10; i++) {
        Node<int> * a  = new Node<int>;
        a->info = i;
        SLS.append(a);
    }
}

int main() {
    SingleLinkedList<int> SLS;
    addThings(SLS);
    Node<int> * b  = new Node<int>;
    b->info = 6;
    SLS.append(b);
    SLS.print();
    std::cout << "Hello nour" << '\n';
    return 0;
}