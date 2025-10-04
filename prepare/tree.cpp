#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string data;
    int size;
    vector<Node *>children;

    Node(string s, int n): data(s), size(n) {}
};

int getSize(Node *root) {
    if (!root) return 0;
    int total = root->size;
    for (auto c : root->children) {
        total += getSize(c);
    }
    return total;
}

void preorder(Node *root, int depth = 0) {
    if(!root) return;

    for(int i = 0; i < depth; i++) cout << " ";
    cout << root->data << " (" << root->size << ")" << endl;

    for(auto c : root->children) {
        preorder(c, depth + 1);
    }
}

void postorder(Node *root, int depth = 0) {
    if(!root) return;

    for(auto c : root->children) {
        postorder(c, depth + 1);
    }

    for(int i = 0; i < depth; i++) cout << " ";
    cout << root->data << " (" << root->size << ")" << endl;
}

int main() {
    Node *root = new Node("/user/rt/courses/", 1);

    Node *cs016 = new Node("cs016/", 2);
    Node *cs252 = new Node("cs252/", 1);

    Node *grades016 = new Node("grades/", 8);
    Node *homeworks = new Node("homeworks/", 1);
    Node *hw1 = new Node("hw1/", 3);
    Node *hw2 = new Node("hw2/", 2);
    Node *hw3 = new Node("hw3/", 4);
    Node *programs = new Node("programs/", 1);
    Node *pr1 = new Node("pr1/", 57);
    Node *pr2 = new Node("pr2/", 97);
    Node *pr3 = new Node("pr3/", 74);

    homeworks->children = {hw1, hw2, hw3};
    programs->children = {pr1, pr2, pr3};

    Node *projects = new Node("projects/", 1);
    Node *papers = new Node("papers/", 1);
    Node *buylow = new Node("buylow/", 26);
    Node *sellhigh = new Node("sellhigh/", 55);
    Node *demos = new Node("demos/", 1);
    Node *market = new Node("market", 4786);
    Node *grades252 = new Node("grades/", 3);

    papers->children = {buylow, sellhigh};
    demos->children = {market};
    projects->children = {papers, demos};

    cs016->children = {grades016, homeworks, programs};
    cs252->children = {projects, grades252};

    root->children = {cs016, cs252};

    cout << "Preorder\n";
    preorder(root);

    cout << "\nPostorder\n";
    postorder(root);

    return 0;
}
