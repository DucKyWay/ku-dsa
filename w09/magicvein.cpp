#include <iostream>
#include <string>
using namespace std;

struct Node {
    int val;
    Node* next = nullptr;
    Node(int v): val(v), next(nullptr) {}
};

class LinkedList {
    private:
        Node* head;
        Node* tail;
        size_t length;

        // mergesort
        Node* merge(Node* left, Node* right) {
            if (!left) 
                return right;
            if (!right) 
                return left;

            Node dummy(0);
            Node* curr = &dummy;

            while (left && right) {
                if (left->val <= right->val) {
                    curr->next = left;
                    left = left->next;
                } else {
                    curr->next = right;
                    right = right->next;
                }
                curr = curr->next;
            }
            
            curr->next = (left ? left : right);
            return dummy.next;
        }
        
        Node* split(Node* start) {
            if (!start || !start->next) return nullptr;

            Node* slow = start;
            Node* fast = start->next;

            while (fast && fast->next) {
                slow = slow->next;
                fast = fast->next->next;
            }
            
            Node* mid = slow->next;
            slow->next = nullptr;
            return mid;
        }

        Node* mergeSort(Node* node) {
            if (!node || !node->next) 
                return node;

            Node* mid = split(node);
            Node* left = mergeSort(node);
            Node* right = mergeSort(mid);

            return merge(left, right);
        }
        
    public: 
        LinkedList() : head(nullptr), tail(nullptr), length(0) {}
        ~LinkedList() { clear(); }
        
        void push_back(int v) {
            Node* newNode = new Node(v);
            if (!head) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            length++;
        }

        void sort() {
            head = mergeSort(head);

            tail = head;
            while (tail && tail->next) {
                tail = tail->next;
            }
        }

        bool empty() {
            return head == nullptr;
        }

        void clear() {
            Node* curr = head;
            while (curr) {
                Node* nextNode = curr->next;
                delete curr;
                curr = nextNode;
            }
            head = tail = nullptr;
            length = 0;
        }

        Node* getHead() { return head; }

        void print() {
            if (empty()) {
                cout << "IMPOSSIBLE" << endl;
                return;
            }

            Node* curr = head;
            bool first = true;
            while (curr) {
                if (!first) cout << " ";
                cout << curr->val;
                first = false;
                curr = curr->next;
            }
            cout << endl;
        }
};

bool isPrime(int n) {
    if (n <= 1)     return false;
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) 
            return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x;
    cin >> x;

    for (int i = 0; i < x; i++) {
        int m;
        cin >> m;

        LinkedList all, res;

        for (int j = 0; j < m; j++) {
            int amount;
            cin >> amount;
            if (amount > 0) {
                all.push_back(amount);
            }
        }

        int minLim, maxLim;
        cin >> minLim >> maxLim;
        if (minLim > maxLim) swap(minLim, maxLim);

        // คุ้มมมมมมมมมมมมมมม
        for (Node* cur = all.getHead(); cur != nullptr; cur = cur->next) {
            int v = cur->val;

            bool valid = false;
            if (v >= minLim && v <= maxLim) valid = true;
            if (isPrime(v)) valid = true;
            if (v % 7 == 0) valid = true;

            if (valid) {
                res.push_back(v);
            }
        }

        res.sort();
        res.print();
    }

    return 0;
}