#include "iostream"
#include "stack"
#include "queue"


using namespace std;

//Node class
class Node {
public:
    int data;
    Node *left;
    Node *right;

    explicit Node(int d) {
        data = d;
        left = nullptr;
        right = nullptr;
    }
};


//PLR
//preOrder Recursive Function
void preOrder(Node *root) {
    if (!root) return;
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

//LRP
//postOrder Recursive Function
void postOrder(Node *root) {
    if (!root) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

//LPR
//inOrder Recursive Function
void inOrder(Node *root) {
    if (!root) return;
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}


//Height of the Tree
int height(Node *root) {
    if (!root) return 0;
    return max(height(root->left), height(root->right)) + 1;
}


bool checkBST(Node *root, int minv, int maxv) {
    if (!root) return true;
    if (root->data < minv || root->data > maxv) return false;
    return checkBST(root->left, minv, root->data - 1) && checkBST(root->right, root->data + 1, maxv);
}

Node *createBST(Node *root, int k) {
    if (root == nullptr) return new Node(k);
    if (root->data > k) root->left = createBST(root->left, k);
    else root->right = createBST(root->right, k);
    return root;
}

Node *lowestCommonAncestorBST(Node *root, int v1, int v2) {
    if (!root) return nullptr;
    Node *d = nullptr;
    if (root->data > v1 && root->data > v2) d = lowestCommonAncestorBST(root->left, v1, v2);
    else if (root->data < v1 && root->data < v2) d = lowestCommonAncestorBST(root->right, v1, v2);
    else return root;
    return d;
}

Node *resolve(Node *root, int v) {
    if (!root) return nullptr;
    if (root->data == v) return root;
    Node *l = resolve(root->left, v);
    Node *r = resolve(root->right, v);
    return l ? l : r;
}

Node *findSmallest(Node *root) {
    Node *temp = root;
    while (temp && temp->left) temp = temp->left;
    return temp;
}

Node *findLargest(Node *root) {
    Node *temp = root;
    while (temp && temp->right) temp = temp->right;
    return temp;
}

Node *findInOrder(Node *root, Node *t, Node *&temp) {
    if (!root) return nullptr;

    bool res = root->data == t->data;

    Node *l = findInOrder(root->left, t, temp);
    Node *r = findInOrder(root->right, t, temp);

    if (res || l || r) {

        if (l && root->left->data == l->data) {
            temp = root;
            return nullptr;
        }

        return root;
    }

    return nullptr;
}

Node *inOrderSuccessor(Node *root, int v) {

    Node *t = resolve(root, v);

    if (t->right) {
        return findSmallest(t->right);
    } else {
        if (findLargest(root)->data == v) return nullptr;

        Node *temp = nullptr;
        findInOrder(root, t, temp);
        return temp;
    }
}

Node *inOrderSuccessorEasyUtil(Node *root, Node *n) {
    // step 1 of the above algorithm
    if (n->right != nullptr)
        return findSmallest(n->right);

    Node *succ = nullptr;

    // Start from root and search for successor down the tree
    while (root != nullptr) {
        if (n->data < root->data) {
            succ = root;
            root = root->left;
        } else if (n->data > root->data)
            root = root->right;
        else
            break;
    }

    return succ;
}

Node *inOrderSuccessorEasy(Node *root, int v) {
    Node *n = resolve(root, v);
    return inOrderSuccessorEasyUtil(root, n);
}

Node *preOrderSuccessorUtil(Node *root, Node *n) {
    if (n->left) return n->left;
    if (!n->left && n->right) return n->right;
    Node *successor = nullptr;
    while (root != nullptr) {
        if (root->data > n->data) {
            successor = root->right;
            root = root->left;
        } else if (root->data < n->data)
            root = root->right;
        else
            break;
    }
    return successor;
}

Node *preOrderSuccessor(Node *root, int v) {
    Node *n = resolve(root, v);
    return preOrderSuccessorUtil(root, n);
}

Node *findInRight(Node *root) {
    while (root->left) root = root->left;
    while (root->right) root = root->right;
    return root;
}

Node *postOrderSuccessorUtil(Node *root, Node *n) {
    if (root == n) return nullptr;
    Node *successor = nullptr;
    while (root != nullptr) {
        if (root->data < n->data) {
            successor = root;
            root = root->right;
        } else if (root->data > n->data) {
            if (root->left && root->left->data == n->data) {
                return findInRight(root->right);
            }
            root = root->left;
        } else {
            break;
        }
    }
    return successor;
}

Node *postOrderSuccessor(Node *root, int v) {
    Node *n = resolve(root, v);
    return postOrderSuccessorUtil(root, n);
}


Node *deleteNodeBST(Node *root, int v) {
    if (!root) return nullptr;
    if (root->data > v) root->left = deleteNodeBST(root->left, v);
    else if (root->data < v) root->right = deleteNodeBST(root->right, v);
    else {
        if (!root->left) {
            if (root->right) {
                Node *temp = root->right;
                free(root);
                return temp;
            }
            free(root);
            return nullptr;
        } else if (!root->right) {
            if (root->left) {
                Node *temp = root->left;
                free(root);
                return temp;
            }
            free(root);
            return nullptr;
        }
        Node *temp = inOrderSuccessor(root, v);
        cout << "  " << temp->data << "   ";
        root->data = temp->data;
        root->right = deleteNodeBST(root->right, temp->data);
    }
    return root;
}


int main() {

    //Creating a BST
    Node *bst = new Node(10);
    bst->left = new Node(7);
    bst->right = new Node(14);

    bst->left->left = new Node(6);
    bst->left->right = new Node(9);
    bst->right->left = new Node(11);

    bst->right->right = new Node(15);
    bst->right->right->right = new Node(16);
    cout << endl;
    cout << endl << "Binary Search Tree" << endl;
    inOrder(bst);

    //checking if it is BST
    cout << endl << "Is it a binary Search Tree? ";
    if (checkBST(bst, INT_MIN, INT_MAX)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    cout << endl;

    //Creating a BST
    cout << endl << "Creating BST with 5,2,7,1,4,6,8,9" << endl;
    vector<int> arr = {5, 2, 7, 1, 4, 6, 8, 9};
    Node *root = nullptr;
    for (auto f: arr) {
        root = createBST(root, f);
    }

    //Printing inorder for BST
    cout << "InOrder for the bst: ";
    inOrder(root);
    cout << endl;


    //LowestCommonAncestorInBST
    cout << endl << "LowestCommonAncestor 2, 4 : ";
    Node *d = lowestCommonAncestorBST(root, 2, 4);
    cout << d->data << endl;
    cout << "LowestCommonAncestor 4, 9 : ";
    d = lowestCommonAncestorBST(root, 4, 9);
    cout << d->data << endl;
    cout << endl;


    //InOrderSuccessor
    cout << "InOrder for the bst: ";
    inOrder(root);
    for (auto f : arr) {
        Node *temp = nullptr;
        temp = inOrderSuccessor(root, f);
        if (temp)
            cout << endl << "InOrderSuccessor for " << f << " : " << temp->data;
        else
            cout << endl << "InOrderSuccessor for " << f << " : NULL";
    }
    cout << endl;

    cout << endl << "InOrder using a different approach";
    for (auto f : arr) {
        Node *temp = nullptr;
        temp = inOrderSuccessorEasy(root, f);
        if (temp)
            cout << endl << "InOrderSuccessor for " << f << " : " << temp->data;
        else
            cout << endl << "InOrderSuccessor for " << f << " : NULL";
    }
    cout << endl;

    //PreOrderSuccessor
    cout << endl << endl << "PreOrder for the bst: ";
    preOrder(root);

    for (auto f : arr) {
        Node *temp = nullptr;
        temp = preOrderSuccessor(root, f);
        if (temp)
            cout << endl << "PreOrderSuccessor for " << f << " : " << temp->data;
        else
            cout << endl << "PreOrderSuccessor for " << f << " : NULL";
    }
    cout << endl;

    //PostOrderSuccessor
    cout << endl << endl << "PostOrder for the bst: ";
    postOrder(root);
    for (auto f : arr) {
        Node *temp = nullptr;
        temp = postOrderSuccessor(root, f);
        if (temp)
            cout << endl << "PostOrderSuccessor for " << f << " : " << temp->data;
        else
            cout << endl << "PostOrderSuccessor for " << f << " : NULL";
    }
    cout << endl;

    //Deletion Code
    cout << endl << endl << "InOrder Before: ";
    inOrder(root);
    cout << endl << "Deleting Node 9";
    deleteNodeBST(root, 9);
    cout << endl << "InOrder After: ";
    inOrder(root);
    cout << endl;

    return 0;
}
