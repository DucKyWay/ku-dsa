#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// heap
void heapify(vector<int>&A, int i, int n) {
    int large = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && A[left] > A[large])
        large = left;

    if (right < n && A[right] > A[large])
        large = right;

    if (large != i) {
        int temp = A[i];
        A[i] = A[large];
        A[large] = temp;
        heapify(A, large, n);
    }
}

// bottom to top
void buildMaxHeap(vector<int>&A, int n) {
    for(int i = n / 2 - 1; i >= 0; i--) {
        heapify(A, i, n);
    }
}

// root <> last
void heapSort(vector<int>& A, int n) {
    buildMaxHeap(A, n);
    for(int i = n - 1; i > 0; i--) {
        int tmp = A[0];
        A[0] = A[i];
        A[i] = tmp;
        heapify(A, 0, i);
    }
}

// bst
struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

Node* insertBST(Node* root, int v) {
    if (!root) return new Node(v);
    if (v < root->val) root->left = insertBST(root->left, v);
    else root->right = insertBST(root->right, v);
    return root;
}

void inorder(Node* root, vector<int>& out) {
    if (!root) return;
    inorder(root->left, out);
    out.push_back(root->val);
    inorder(root->right, out);
}

// --- helper เพิ่มเติม (ไม่แตะของเดิม) ---
// ใส่ค่าแบบ postorder จากลิสต์ inorder (เรียงน้อย->มาก) เพื่อให้เป็น Max Heap โดยคงรูปทรงเดิม
void assignPostorder(Node* root, const vector<int>& in, int& idx) {
    if (!root) return;
    assignPostorder(root->left, in, idx);
    assignPostorder(root->right, in, idx);
    root->val = in[idx++];
}

// เก็บค่าแบบ BFS เพื่อนำไปเป็น collection ของต้นนั้น
vector<int> bfs(Node* root) {
    vector<int> out;
    if (!root) return out;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* u = q.front(); q.pop();
        out.push_back(u->val);
        if (u->left) q.push(u->left);
        if (u->right) q.push(u->right);
    }
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // tawipak tonmai
    vector<vector<int>> trees;
    for (int i = 0; i < n; i++) {
        Node* root = nullptr;
        int num;
        while (true) {
            cin >> num;
            if (num == -111) break;
            root = insertBST(root, num);
        }

        // create bst to max heap with in, post
        vector<int> inVals;
        inorder(root, inVals);
        int idx = 0;
        assignPostorder(root, inVals, idx);

        // bfs to collection
        vector<int> vals = bfs(root);
        trees.push_back(vals);
    }

    // mrege and build max heap
    vector<int> merged = trees[0];
    buildMaxHeap(merged, (int)merged.size());
    for (int i = 1; i < n; i++) {
        merged.insert(merged.end(), trees[i].begin(), trees[i].end());
        buildMaxHeap(merged, (int)merged.size());
    }

    for (int i = 0; i < (int)merged.size(); i++) {
        cout << merged[i];
        if (i != (int)merged.size() - 1)
            cout << ",";
    }
    cout << "\n";

    return 0;
}
