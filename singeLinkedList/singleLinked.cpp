#include <iostream>

template <typename T>
class SingleLinkedList {
    struct Node {
        T info;
        Node * next;
            Node() {
                next = nullptr;
            }
            Node(const T data) {
                info = data;
                next = nullptr;
            }
            ~Node() {};
    };
    Node * last;
    Node * first;
    Node * iterator;
    public:
        SingleLinkedList() {
            first = nullptr;
            last = nullptr;
        }
        T & findNode(const T info);
        T * iteratorBegin();
        T * iteratorNext();
        void addNode(const T info);
        void deleteNode(const T info);
        void addAfterNode(const T info,const T data);
        void apply( void (*tempFunc) (T));
        ~SingleLinkedList() {
            while(first != nullptr) {
                Node * temp = first;
                first = first->next;
                delete temp;
            }
            delete first;
        }
};

template <typename T>
void SingleLinkedList<T>::addNode(const T info) {
    Node * newNode = new Node(info);
    if (last != nullptr) {
        last->next = newNode;
        last = last->next;
    } else {
        first = newNode;
        last = newNode;
    }
}

template <typename T>
T * SingleLinkedList<T>::iteratorBegin() {
    iterator = first;
    return &first->info;
}

template <typename T>
T * SingleLinkedList<T>::iteratorNext() {
    iterator = iterator->next;
    return &iterator->info;
}



template <typename T>
T & SingleLinkedList<T>::findNode(const T info) {
    if(first->info == info) {
        return first->info;
    }
    Node * temp = first;
    while(temp->next != nullptr) {
        if(temp->next->info == info) {
            return temp->next->info;
        } 
        temp = temp->next;
    }
    std::cerr << "Node not found";
}


template <typename T>
void SingleLinkedList<T>::addAfterNode(const T info, const T data) {
    Node * newNode = new Node(data);
    if(first == nullptr) {
        std::cerr << "List is empty";
        return;
    }
    if(first->info == info) {
        Node * temp2 = first->next;
        first->next = newNode;
        newNode->next = temp2;
        return;
    }
    Node * temp = first;
    while(temp->next != nullptr) {
        if(temp->next->info == info) {
            Node * temp2 = temp->next->next;
            temp->next->next = newNode;
            newNode->next = temp2;
            return;
        } 
        temp = temp->next;
    }
    std::cerr << "Node not found";
    return;
}

template <typename T>
void SingleLinkedList<T>::deleteNode(const T info) {
    if(first == nullptr) {
        std::cerr << "List is empty";
    }
    Node * temp = first;
    if(first->info == info) {
        first = first->next;
        temp->next = nullptr;
        delete temp;
        return;
    }
    while(temp->next != nullptr) {
        if(temp->next->info == info) {
            //check if the element is the last element in the list
            if(temp->next->next != nullptr) {
                Node * temp2 = temp->next;
                temp->next = temp->next->next;
                temp2->next = nullptr;
                delete temp2;
            } else {
                Node * temp2 = temp->next;
                delete temp2;
                temp->next = nullptr;
            }
        } 
        if(temp->next != nullptr) temp = temp->next;
        
    }
}

template <typename T>
void SingleLinkedList<T>::apply(void (*tempFunc) (T)) {
    Node * temp = first;
    while(temp != nullptr) {
        tempFunc(temp->info);
        temp = temp->next;
    }
}


void print(int i) {
    std::cout << i << "\n";
} 

int main() {
    SingleLinkedList<int> SLS;
    for (int i = 0; i < 10; i++) {
        SLS.addNode(i);
    }
    SLS.addAfterNode(4, 100);
    int & a = SLS.findNode(3);
    a = 99;
    SLS.deleteNode(5);
    SLS.deleteNode(0);
    SLS.apply(&print);
    int * i = SLS.iteratorBegin();
    i = SLS.iteratorNext();
    std::cout << *i << "\n";
    return 0;
}