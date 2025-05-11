#include <iostream>
#include <algorithm>
using namespace std;

// Node structure
struct Node {
    int key, height;
    Node *left, *right;

    Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

// Utility: Get height of node
int getHeight(Node* n) {
    return n ? n->height : 0;
}

// Utility: Get balance factor
int getBalance(Node* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

// Right rotate (LL case)
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

// Left rotate (RR case)
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

// Find node with min value (used in deletion)
Node* minValueNode(Node* node) {
    Node* curr = node;
    while (curr && curr->left)
        curr = curr->left;
    return curr;
}

// Insert a key into AVL tree
Node* insert(Node* root, int key) {
    if (!root) return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root; // ignore duplicates

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bal = getBalance(root);

    // Rebalance if needed
    if (bal > 1 && key < root->left->key)
        return rightRotate(root);
    if (bal < -1 && key > root->right->key)
        return leftRotate(root);
    if (bal > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bal < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Delete a node from AVL tree
Node* deleteNode(Node* root, int key) {
    if (!root) return nullptr;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Found the node to delete
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        } else {
            // Node with 2 children
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // Update height and balance
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bal = getBalance(root);

    // Rebalance if needed
    if (bal > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (bal > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bal < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (bal < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Print tree in pre-order (root-left-right)
void preOrder(Node* root) {
    if (!root) return;
    cout << root->key << " ";
    preOrder(root->left);
    preOrder(root->right);
}

int main() {
    Node* root = nullptr;

    // Insert values
    int values[] = {30, 20, 40, 10, 25, 35, 50};
    for (int v : values)
        root = insert(root, v);

    cout << "Pre-order before deletion:\n";
    preOrder(root);
    cout << "\n";

    // Delete a few nodes
    root = deleteNode(root, 20);  // has 2 children
    cout << "After deleting 20:\n";
    preOrder(root);
    cout << "\n";

    root = deleteNode(root, 30);  // delete root
    cout << "After deleting 30:\n";
    preOrder(root);
    cout << "\n";

    root = deleteNode(root, 10);  // leaf
    cout << "After deleting 10:\n";
    preOrder(root);
    cout << "\n";

    return 0;
}
