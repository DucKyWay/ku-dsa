#include <bits/stdc++.h>
using namespace std;

struct node {
    int key;
    struct node* parent;
    struct node* left;
    struct node* right;
};

int height(struct node *root) {
    if(root->parent == nullptr) return 0;
    else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        if(leftHeight > rightHeight) {
            return leftHeight++;
        } else {
            return rightHeight++;
        }
    }
}

int main() {
    return 0;
}