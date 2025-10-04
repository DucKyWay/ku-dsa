#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct Node {
    string val;
    Node *left;
    Node *right;
    Node(string v): val(v), left(nullptr), right(nullptr) {}
};

char toLowerChar(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A' + 'a';
    return c;
}

string toLower(const string& s) {
    string res = s;
    for (size_t i = 0; i < res.size(); i++) {
        res[i] = toLowerChar(res[i]);
    }
    return res;
}

Node* insert(Node* node, const string& val) {
    if (!node) return new Node(val);
    if (val < node->val) node->left = insert(node->left, val);
    else node->right = insert(node->right, val);
    return node;
}

void searchInOrder(Node* node, const string& target, string result[], int& count) {
    if (!node) return;

    searchInOrder(node->left, target, result, count);

    string lowerNode = toLower(node->val);
    string lowerTarget = toLower(target);
    if (lowerNode == lowerTarget) {
        result[count++] = node->val;
    }

    searchInOrder(node->right, target, result, count);
}

void search(Node* root, const string& target) {
    string result[5000];
    int count = 0;
    searchInOrder(root, target, result, count);

    if (count == 0) {
        cout << "\"" << target << "\" is not found!" << endl;
    } else {
        for (int i = 0; i < count; i++) {
            if (i) cout << " ";
            cout << result[i];
        }
        cout << endl;
    }
}

int main() {
    
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    string line;
    if(!getline(cin, line)) return 0;

    // ตอนสอบนึกไม่ออกอุ
    stringstream ss(line);
    string t, targets[200];
    int targetCount = 0;
    while(ss >> t) {
        targets[targetCount++] = t;
    }

    Node* root = nullptr;
    string name;
    while (cin >> name) {
        root = insert(root, name);
    }

    for (int i = 0; i < targetCount; i++) {
        search(root, targets[i]);
    }

    return 0;
}

/*
alice 
alice 
Alice 
aliCe 
Alice

alice Bob 
bob 
alIce 
bOb 
BoB 
alice 
Alice 
bob 
Alice

alice Bob SaaC Chok 
BOB  
chOk 
alice 
aLice 
ChoK 
bOb
*/
