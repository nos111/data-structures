#include <iostream>

template <typename T>
class BinaryTree {
    struct Node {
        Node() {
            left, right, father = nullptr;
        }
        Node * left;
        Node * right;
        Node * father;
        T key;
        ~Node(){};
    };
    Node * root;
    public:
        BinaryTree() {
            root = nullptr;
        }
        void deleteElement(T data) {
            Node * temp = root;
            while(temp != nullptr) {
                if(temp->key == data) {
                    temp->right->father = temp->father;
                    delete temp;
                    return;
                }
                if (data > temp->key) {
                    temp = temp->right;
                } else {
                    temp = temp->left;
                }
            }

        }
        T & findElement(T data) {
            Node * temp = root;
            while(temp != nullptr) {
                if(temp->key == data) return temp->key;
                if (data > temp->key) {
                    temp = temp->right;
                } else {
                    temp = temp->left;
                }
            }
            std::cerr << "Element not found \n";
        }
        void addElement (T data) {
            Node * newNode = new Node();
            newNode->key = data;
            if (root == nullptr) {
                root = newNode;
                return;
            }
            Node * temp = root;
            while(newNode->father == nullptr) {
                if(data == temp->key) break;
                if (data < temp->key) {
                    if(temp->left == nullptr) {
                        temp->left = newNode;
                        newNode->father = temp;
                    } else {
                        temp = temp->left;
                    }
                }
                if (data > temp->key) {
                    if(temp->right == nullptr) {
                        temp->right = newNode;
                        newNode->father = temp;
                    } else {
                        temp = temp->right;
                    }
                }
            }
        }

        void apply(void (*foo) (T)) {
            foo(root->right->left->key);
        }

};

void print(int i) {
    std::cout << i << '\n';
}

int main() {
    BinaryTree<int> * bt = new BinaryTree<int>();
    bt->addElement(100);
    bt->addElement(100);
    bt->addElement(200);
    bt->addElement(180);
    bt->addElement(300);
    bt->addElement(50);
    bt->addElement(25);
    //int & a = bt->findElement(0);
    //a = 60;
    //std::cout << a << '\n';
    bt->deleteElement(200);
    bt->apply(&print);
    return 0;
}