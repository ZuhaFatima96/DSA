#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

Node* insert(Node* root, int value) {
   
    if (root == nullptr) {
        return new Node(value);
    }


    if (value <= root->data) {
    
        root->left = insert(root->left, value);
    } else {
      
        root->right = insert(root->right, value);
    }

   
    return root;
}


void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

int main() {
    Node* root = nullptr;
    root = insert(root, 10);
    insert(root, 5);
    insert(root, 15);
    insert(root, 3);
    insert(root, 7);
    insert(root, 12);
    insert(root, 18);

    cout << "Inorder Traversal: ";
    inorder(root);
    cout << endl;

    return 0;
}
