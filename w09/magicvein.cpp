#include <iostream>
#include <string>
using namespace std;

struct Node {
    long long val;
    Node* next;
    Node(long long v): val(v), next(nullptr) {}
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
        Node* current = &dummy;

        while (left && right) {
            if (left->val <= right->val) {
                current->next = left;
                left = left->next;
            } else {
                current->next = right;
                right = right->next;
            }
            current = current->next;
        }

        current->next = (left ? left : right);
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

    void push_back(long long v) {
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

    bool empty() const {
        return head == nullptr;
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
        length = 0;
    }

    Node* getHead() const { return head; }

    void print() const {
        if (empty()) {
            cout << "IMPOSSIBLE\n";
            return;
        }

        Node* current = head;
        bool first = true;
        while (current) {
            if (!first) cout << " ";
            cout << current->val;
            first = false;
            current = current->next;
        }
        cout << "\n";
    }
};

bool isPrime(long long n) {
    if (n <= 1)     return false;
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    for (long long i = 5; i * i <= n; i += 6) {
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

    while (x--) {
        int m;
        cin >> m;

        LinkedList allGroups;
        LinkedList result;

        for (int i = 0; i < m; i++) {
            long long amount;
            cin >> amount;
            if (amount >= 0) {
                allGroups.push_back(amount);
            }
        }

        long long minLimit, maxLimit;
        cin >> minLimit >> maxLimit;
        if (minLimit > maxLimit) swap(minLimit, maxLimit);

        // คุ้มมมมมมมมมมมมมมม
        for (Node* cur = allGroups.getHead(); cur != nullptr; cur = cur->next) {
            long long v = cur->val;

            bool valid = false;
            if (v >= minLimit && v <= maxLimit) valid = true;
            if (isPrime(v)) valid = true;
            if (v % 7 == 0) valid = true;

            if (valid) {
                result.push_back(v);
            }
        }

        result.sort();
        result.print();

        allGroups.clear();
        result.clear();
    }

    return 0;
}