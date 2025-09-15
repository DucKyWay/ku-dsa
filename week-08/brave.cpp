#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct Node {
    string data;
    Node* parent;
    vector<Node*> children;

    Node(string v) {
        data = v;
        parent = nullptr;
    }
};

void swapNode(Node* &a, Node* &b) {
    Node* temp = a;
    a = b;
    b = temp;
}

void sortChild(vector<Node*>& children) {

    int n = children.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (children[j]->data > children[j + 1]->data) {
                swapNode(children[j], children[j + 1]);
            }
        }
    }
}

void printTree(Node* root, int depth = 0) {

    for (int i = 1; i < depth; i++) {
        cout << "  ";
    }
    if (depth > 0) cout << "|_";
    cout << root->data << endl;

    sortChild(root->children);
    for (auto child : root->children) {
        printTree(child, depth + 1);
    }
}

void removeChild(Node* parent, Node* node) {

    vector<Node *>& vec = parent->children;
    for (int i = 0; i < (int)vec.size(); i++) {
        if (vec[i] == node) {
            for (int j = i; j < (int)vec.size() - 1; j++) {
                vec[j] = vec[j + 1];
            }
            vec.pop_back();
            break;
        }
    }
}

void deleteSubtree(Node* node, map<string, Node*>& nodes) {
    for (auto child : node->children) {
        deleteSubtree(child, nodes);
    }
    nodes.erase(node->data);
    delete node;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    map<string, Node*> nodes;
    Node* root = nullptr;

    string cmd; // node parent, m node parent, r node
    while (cin >> cmd) {
        if (cmd == "M") { // move
            string nodeName, newParentName;
            cin >> nodeName >> newParentName;

            Node* node = nodes[nodeName];
            if (node->parent != nullptr) {
                removeChild(node->parent, node);
            }

            if (newParentName == "NULL") {
		// child -> root 	
		if(root != nullptr && root != node) {
			node->children.push_back(root);
			root->parent = node;
		}
                node->parent = nullptr;
                root = node;
            } else {
		// child -> new root
                Node* newParent = nodes[newParentName];
                node->parent = newParent;
                newParent->children.push_back(node);
            }
        }
        else if (cmd == "R") { // remove
            string nodeName;
            cin >> nodeName;
            Node* node = nodes[nodeName];
            if (node->parent != nullptr) {
                removeChild(node->parent, node);
            } else {
                root = nullptr;
            }
            deleteSubtree(node, nodes);
        }
        else { // new
		string child, parent;
		child = cmd;
            cin >> parent;
            if (nodes.find(child) == nodes.end())
                nodes[child] = new Node(child);
            if (parent != "NULL" && nodes.find(parent) == nodes.end())
                nodes[parent] = new Node(parent);

            if (parent == "NULL") {
                root = nodes[child];
            } else {
                nodes[child]->parent = nodes[parent];
                nodes[parent]->children.push_back(nodes[child]);
            }
        }
    }

    if (root == nullptr) 	cout << "IMPOSSIBLE" << endl;
    else 			        printTree(root);

    return 0;
}
