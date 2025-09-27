#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int x) : data(x), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int x) {
    if (!root) return new Node(x);
    if (x < root->data) root->left = insert(root->left, x);
    else if (x > root->data) root->right = insert(root->right, x);
    return root;
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void reverse_inorder(Node* root) {
    if (!root) return;
    reverse_inorder(root->right);
    cout << root->data << " ";
    reverse_inorder(root->left);
}

bool search(Node* root, int x) {
    if (!root) return false;
    if (root->data == x) return true;
    if (x < root->data) return search(root->left, x);
    return search(root->right, x);
}

int depth(Node* root) {
    if (!root) return 0;
    int l = depth(root->left);
    int r = depth(root->right);
    return (l > r ? l : r) + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Node* root = nullptr;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        root = insert(root, v[i]);
    }
    
    string cmd;
    while (cin >> cmd) {
        if (cmd == "s") {
            cout << "Ascending order: ";
            inorder(root);
            cout << "\n";
        } else if (cmd == "r") {
            cout << "Descending order: ";
            reverse_inorder(root);
            cout << "\n";
        } else if (cmd == "d") {
            cout << "Depth: " << depth(root) << "\n";
        } else if (cmd == "e") {
            break;
        } else if (cmd == "f") {
            int x;
            while (cin >> x) {
                if (x == -111) break;
                if (search(root, x)) {
                    cout << "Node " << x << " is in the tree.\n";
                } else {
                    cout << "Node not found.\n";
                }
            }
        } else if (cmd == "e") {
            break;
        } else {
            cout << "Unknown command.\n";
        }
    }

    return 0;
}
