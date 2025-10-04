#include <iostream>
#include <string>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
    Node(int k): key(k), left(nullptr), right(nullptr) {}
}

Node *insertBST(Node *root, int key) {
    if(!root) return new Node(key);
    if(key)
}

void inorder(Node *root) {
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

void preorder(Node *root) {
    cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node *root) {
    postorder(root->left);
    postorder(root->right);
    cout << root->key << " ";
}

Node *minNode(Node *root) {
    while(root && root->left) {
        root = root->left;
    }
    return root;
}

Node *maxNode(Node *root) {

}

int main() {
    Node* root = nullptr;
    int vals[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    for (int x : vals) root = insertBST(root, x);

    cout << "Inorder (rec): ";   inorder(root);      cout << "\n";
    cout << "Preorder (rec): ";  preorder(root);     cout << "\n";
    cout << "Postorder (rec): "; postorder(root);    cout << "\n";
    
    cout << "Min=" << (minNode(root)->key) << ", Max=" << (maxNode(root)->key) << "\n";
    cout << "Height=" << height(root) << ", Balanced? " << (isBalancedON(root) ? "Yes" : "No") << "\n";
    cout << "Valid BST? " << (isValidBST(root) ? "Yes" : "No") << "\n";

    return 0;
}