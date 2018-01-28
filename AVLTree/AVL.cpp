#include <iostream>

template <typename T>
class AVLTree {
  struct Node {
    Node() {
        left, right, father = nullptr;
        leftWeight, rightWeight = 0;
    }
    Node * left;
    Node * right;
    Node * father;
    T key;
    int leftWeight;
    int rightWeight;
    ~Node(){
    };
  };
  struct BinaryTree {
    Node * root;
      BinaryTree() {
          root = nullptr;
    }
    void transplant(Node * target, Node * origin) {
        if(origin->father == nullptr) { 
            root = target;
        }
        else if(origin->father->left != nullptr) {
            if(origin->father->left->key == origin->key) origin->father->left = target;
            else {
            origin->father->right = target;
            }
        }
        if(target != nullptr) {
            target->father = origin->father;
        } 
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
                if(temp->left != nullptr && temp->right != nullptr) {
                    //find the node successor
                    Node * successor = findSuccessor(temp);
                    //make the right tree of the successor the child of the successor father
                    transplant(successor->right, successor);
                    //make the successor the child of the temp father
                    transplant(successor, temp);
                    //give the successor the connections of the deleted element
                    successor->left = temp->left;
                    successor->right = temp->right;
                    return;
                }
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
        if(element == nullptr) return nullptr;
        if(element->right != nullptr) {
            return treeMinimum(element->right);
        }
        Node * temp = element->father;
        while(temp != nullptr && element->key == temp->right->key ) {
            element = temp;
            temp = temp->father;
            if(temp->right == nullptr) return temp;
        }
        return temp;
    }
    Node * findPredecessor(Node * element) {
        if(element->left != nullptr) {
            return treeMaximum(element->left);
        }
        Node * temp = element->parent;
        while(temp != nullptr && element->key == temp->left->key ) {
            element = temp;
            temp = temp->father;
        }
        return temp;
    }
    void inorderTreeWalk(Node * x) {
        if(x != nullptr) {
            std::cout << x->key << "My left is ";
            inorderTreeWalk(x->left);
            std::cout << "My right is ";
            inorderTreeWalk(x->right);
            std::cout << "\n";
        }
    }
    void apply(void (*foo) (T)) {
        foo(root->right->right->left->key);
    }
    void printTree() {
        inorderTreeWalk(root);
    }
  };

  void fixInsert(Node * fixMe) {

  }

  void rotateLeft(Node * rotateMe) {
    Node * temp = rotateMe->right;
    //move the right tree of the child to be the left tree of parent
    rotateMe->right = temp->left;
    //change the fathers
    temp->father = rotateMe->father;
    //rotate the nodes
    rotateMe->father = temp;
    temp->left = rotateMe;
    //check to which side the father belong
    std::cout << "rotate me father right key is " << rotateMe->father->right->key;
    if(temp->father->right != nullptr) {
      if(temp->father->right->key == rotateMe->key) {
        std::cout << "rotate me key is " << rotateMe->key;
        temp->father->right = temp;
      } else {
        temp->father->left = temp;
      }
    } else {
      temp->father->left = temp;
    }
  }
  void rotateRight(Node * rotateMe) {
    
  }
  BinaryTree bt;

  public:
  AVLTree() {
  }

  void insert(T key) {
    bt.addElement(key);
  }
  void deleteKey(T key) {

  }
  T findKey(T key) {
    return findElement(key);
  }
  void test() {
    bt.inorderTreeWalk(bt.root);
    rotateLeft(bt.root->right);
    std::cout << "Node 200 was rotated \n";
    bt.inorderTreeWalk(bt.root);
  }
};

void print(int i) {
    std::cout << i << '\n';
}

int main() {
  AVLTree<int> * Atree = new AVLTree<int>();
  Atree->insert(100);
  Atree->insert(100);
  Atree->insert(200);
  Atree->insert(180);
  Atree->insert(300);
  Atree->insert(400);
  Atree->insert(50);
  Atree->insert(25);
  Atree->insert(250);
  Atree->test();

  return 0;
}