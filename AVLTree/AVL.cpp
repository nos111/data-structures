#include <iostream>

template <typename T>
class AVLTree {
  struct Node {
    Node() {
        left, right, father = nullptr;
    }
    Node * left;
    Node * right;
    Node * father;
    T key;
    int height;
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
        } else {
            origin->father->right = target;
        }
        if(target != nullptr) {
            target->father = origin->father;
        } 
    }
    Node * deleteElement(T data) {
        Node * temp = root;
        while(temp != nullptr) {
            if(temp->key == data) {
                //Node with no children
                if(temp->left == nullptr && temp->right == nullptr) {
                    //find wether it was the left or right child
                    if(temp->father->left != nullptr) {
                        if(temp->father->left->key == temp->key) temp->father->left = nullptr;
                        else  { temp->father->right = nullptr; }
                    } else { temp->father->right = nullptr; }
                    return temp->father;
                }
                //Node with one child
                if(temp->left == nullptr && temp->right != nullptr) {
                    temp->right->father = temp->father;
                    temp->father->right = temp->right;
                    return temp->father;
                }
                if(temp->left != nullptr && temp->right == nullptr) {
                    temp->left->father = temp->father;
                    temp->father->left = temp->left;
                    return temp->father;
                }

                //Node with two children
                if(temp->left != nullptr && temp->right != nullptr) {
                    //find the node successor
                    Node * successor = findSuccessor(temp);
                    std::cout << "My successor is " << successor->key;
                    Node * parentSuccessor = successor->father;
                    //make the right tree of the successor the child of the successor father
                    transplant(successor->right, successor);
                    //make the successor the child of the temp father
                    transplant(successor, temp);
                    //give the successor the connections of the deleted element
                    successor->left = temp->left;
                    successor->right = temp->right;
                    if(successor->left != nullptr) {
                      successor->left->father = successor;
                    }
                    if(successor->right != nullptr) {
                      successor->right->father = successor;
                    }
                    return successor;
                }
            }
            if (data > temp->key) {
                temp = temp->right;
            } else {
                temp = temp->left;
            }
        }

    }
    Node * findElement(T data) {
        Node * temp = root;
        while(temp != nullptr) {
            if(temp->key == data) return temp;
            if (data > temp->key) {
                temp = temp->right;
            } else {
                temp = temp->left;
            }
        }
        std::cerr << "Element not found \n";
    }
    Node * addElement (T data) {
        Node * newNode = new Node();
        newNode->key = data;
        if (root == nullptr) {
            root = newNode;
            return root;
        }
        Node * temp = root;
        while(newNode->father == nullptr) {
            if(data == temp->key) break;
            if (data < temp->key) {
                if(temp->left == nullptr) {
                    temp->left = newNode;
                    newNode->father = temp;
                    return newNode;
                } else {
                    temp = temp->left;
                }
            }
            if (data > temp->key) {
                if(temp->right == nullptr) {
                    temp->right = newNode;
                    newNode->father = temp;
                    return newNode;
                } else {
                    temp = temp->right;
                }
            }
        }
        return newNode;
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

  void reBalance(Node * fixMe) {
    while(fixMe != nullptr) {
      updateHeight(fixMe);
      if(findHeight(fixMe->left) >= findHeight(fixMe->right) + 2) {
        if(findHeight(fixMe->left->left) >= findHeight(fixMe->left->right)) {
          rotateRight(fixMe);
        } else {
          rotateLeft(fixMe->left);
          rotateRight(fixMe);
        }
      } else if(findHeight(fixMe->right) >= findHeight(fixMe->left) + 2) {
        if(findHeight(fixMe->right->right) >= findHeight(fixMe->right->left)) {
          rotateLeft(fixMe);
        } else {
          rotateRight(fixMe->right);
          rotateLeft(fixMe);
        }
      }
      fixMe = fixMe->father;
    }
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
    if(temp->father == nullptr) {
      bt.root = temp;
    } else {
      if(temp->father->right != nullptr) {
        if(temp->father->right->key == rotateMe->key) {
          temp->father->right = temp;
        } else {
          temp->father->left = temp;
        }
      } else {
        temp->father->left = temp;
      }
    }
    updateHeight(temp);
    updateHeight(rotateMe);
  }
  void rotateRight(Node * rotateMe) {
    Node * temp = rotateMe->left;
    if(temp == nullptr) return;
    //move the right tree of the child to be the left tree of parent
    rotateMe->left = temp->right;
    if(rotateMe->left != nullptr) {
      rotateMe->left->father = rotateMe;
    }
    //change the fathers
    temp->father = rotateMe->father;
    //rotate the nodes
    rotateMe->father = temp;
    temp->right = rotateMe;
    //check to which side the father belong
    if(temp->father == nullptr) {
      bt.root = temp;
    } else {
      if(temp->father->left != nullptr) {
        if(temp->father->left->key == rotateMe->key) {
          temp->father->left = temp;
        } else {
          temp->father->right = temp;
        }
      } else {
        temp->father->right = temp;
      }
    }
    
    updateHeight(temp);
    updateHeight(rotateMe);
  }

  int findHeight(Node * myHeight) {
    if (myHeight == nullptr) return -1;
    return myHeight->height;
  }

  void updateHeight(Node * updateMe) {
    updateMe->height = std::max(findHeight(updateMe->left), findHeight(updateMe->right)) + 1;
  }
  BinaryTree bt;

  public:
  AVLTree() {
  }

  void insert(T key) {
    Node * newNode = bt.addElement(key);
    reBalance(newNode);
  }
  void deleteKey(T key) {
    Node * deletedNodeParent = bt.deleteElement(key);
    reBalance(deletedNodeParent);
  }
  T & findKey(T key) {
    Node * temp = findElement(key);
    if(temp != nullptr) return temp->key;
    std::cout << " element not found";
  }
  void test() {
    bt.inorderTreeWalk(bt.root);
  }
};

void print(int i) {
    std::cout << i << '\n';
}

int main() {
  AVLTree<int> * Atree = new AVLTree<int>();
  Atree->insert(100);
  Atree->insert(200);
  Atree->insert(180);
  Atree->insert(300);
  Atree->insert(400);
  Atree->insert(50);
  Atree->insert(25);
  Atree->insert(250);
  Atree->deleteKey(300);
  Atree->test();

  return 0;
}