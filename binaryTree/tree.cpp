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
        ~Node(){
        };
    };
    Node * root;
    public:
        BinaryTree() {
            root = nullptr;
        }
        void transplant(Node * target, Node * origin) {
            if(origin->father == nullptr) { 
                root = target;
            }
            else if(origin->father->left != nullptr) {
                if(origin->father->left->key == origin->key) origin->father->left = target;
            }
            else {
                origin->father->right = target;
            }
            target->father = origin->father;
        }
        void deleteElement(T data) {
            Node * temp = root;
            while(temp != nullptr) {
                if(temp->key == data) {
                    //Node with no childs
                    if(temp->left == nullptr && temp->right == nullptr) {
                        //find wether it was the left or right child
                        if(temp->father->left != nullptr) {
                            if(temp->father->left->key == temp->key) temp->father->left = nullptr;
                            else  { temp->father->right = nullptr; }
                        } else { temp->father->right = nullptr; }
                        return;
                    }
                    //Node with one child
                    if(temp->left == nullptr && temp->right != nullptr) {
                        temp->right->father = temp->father;
                        temp->father->right = temp->right;
                        return;
                    }
                    if(temp->left != nullptr && temp->right == nullptr) {
                        temp->left->father = temp->father;
                        temp->father->left = temp->left;
                        return;
                    }

                    //Node with two children
                    //find the node successor
                    Node * successor = findSuccessor(temp);
                    std::cout << "Key when returned from function is "<< successor->key << '\n';
                    //if successor has right child connect it to the father of successor
                    std::cout << "got here";
                    transplant(successor->right, successor);

                    transplant(successor, temp);
                    
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
        Node * treeMaximum(Node * element) {
            while(element->right != nullptr) {
                element = element->right;
            }
            return element;
        }
        Node * treeMinimum(Node * element) {
            while(element->left != nullptr) {
                element = element->left;
            }
            return element;
        }
        Node * findSuccessor(Node * element) {
            if(element->right != nullptr) {
                return treeMinimum(element->right);
            }
            Node * temp = element->father;
            while(temp != nullptr && element == temp->right ) {
                element = temp;
                temp = temp->father;
            }
            return temp;
        }
        Node * findPredecessor(Node * element) {
            if(element->left != nullptr) {
                return treeMaximum(element->left);
            }
            Node * temp = element->parent;
            while(temp != nullptr && element == temp->left ) {
                element = temp;
                temp = temp->father;
            }
            return temp;
        }
        void inorderTreeWalk(Node * x) {
            if(x != nullptr) {
                std::cout << x->key << "\n";
                inorderTreeWalk(x->left);
                inorderTreeWalk(x->right);
            }
        }
        void apply(void (*foo) (T)) {
            foo(root->right->right->left->key);
        }
        void printTree() {
            inorderTreeWalk(root);
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
    bt->addElement(400);
    bt->addElement(50);
    bt->addElement(25);
    bt->addElement(250);
    //int & a = bt->findElement(0);
    //a = 60;
    //std::cout << a << '\n';
    bt->deleteElement(200);
    bt->apply(&print);
    //bt->printTree();
    return 0;
}