#include <iostream>

template <typename T>
class Stack {
    struct Node {
        T info;
        Node * next;
        Node() {
            next = nullptr;
        }
        Node(T data) {
            info = data;
            next = nullptr;
        }
        ~Node() {};
};

    Node * top;
   
    public:
        Stack() {
            top = nullptr;
        }
        void push(T info);
        void print();
        T pop();
        T peek();
        ~Stack() {
            while(top != nullptr) {
                Node * temp = top;
                top = top->next;
                delete temp;
            }
            delete top;
        }
};

template <typename T>
void Stack<T>::push(T info) {
    Node * newNode = new Node(info);
    if (top != nullptr) {
        newNode->next = top;
    }
    top = newNode;
}

template <typename T>
T Stack<T>::pop() {
    if(top == nullptr) {
        std::cerr << "stack is empty";
    }
    Node * temp = top;
    top = top->next;
    T tempData = temp->info;
    delete temp;
    return tempData;
}

template <typename T>
T Stack<T>::peek() {
    if(top == nullptr) {
        std::cerr << "stack is empty";
    }
    return top->info;
}

template <typename T>
void Stack<T>::print() {
    Node * temp = top;
    while(temp != nullptr) {
        std::cout << temp->info << '\n';
        temp = temp->next;
    }
}


int main() {
    Stack<int> stack;
    for (int i = 0; i < 10; i++) {
        stack.push(i);
    }
    int s = stack.pop();
    std::cout << s << "hi"<<"\n";
    stack.print();
    return 0;
}