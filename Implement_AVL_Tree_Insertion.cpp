#include <iostream>
#include <algorithm> 
using namespace std;


struct Node {
    int key, height;
    Node *left, *right;
    Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

// Utility to get height of a node
int getHeight(Node* n) {
    return n ? n->height : 0;
}

// Get balance factor of a nodeS
int getBalance(Node* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Right rotate subtree rooted with y
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Left rotate subtree rooted with x
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Insert key and balance the AVL tree
Node* insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // Duplicate keys not allowed

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    // Perform rotations based on balance factor
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Pre-order traversal of the tree
void preOrder(Node* root) {
    if (!root) return;
    cout << root->key << " ";
    preOrder(root->left);
    preOrder(root->right);
}

int main() {
    Node* root = nullptr;
    int keys[] = {10, 20, 30, 40, 50, 25};

    for (int key : keys) {
        cout << "\nInserting " << key << "...\n";
        root = insert(root, key);
        cout << "Pre-order after insertion: ";
        preOrder(root);
        cout << endl;
    }

    return 0;
}
