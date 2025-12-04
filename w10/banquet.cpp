#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

// โครงสร้างข้อมูลลูกค้า
struct Item {
    string name;
    int level;      // 0 = VIP สูงสุด
    int seq;        // ลำดับมาถึง (สำหรับ tie-break)
};

// comparator สำหรับ min-heap ด้วย vector
inline bool higherPriority(const Item& a, const Item& b) {
    // level น้อยสำคัญกว่า; ถ้าเท่ากัน คนมาถึงก่อนสำคัญกว่า
    if (a.level != b.level) return a.level < b.level;
    return a.seq < b.seq;
}

void heapifyDown(vector<Item>& A, int i, int n) {
    while (true) {
        int l = 2*i + 1, r = 2*i + 2, best = i;
        if (l < n && higherPriority(A[l], A[best])) best = l;
        if (r < n && higherPriority(A[r], A[best])) best = r;
        if (best == i) break;
        swap(A[i], A[best]);
        i = best;
    }
}

void buildMinHeap(vector<Item>& A) {
    for (int i = (int)A.size()/2 - 1; i >= 0; --i) heapifyDown(A, i, (int)A.size());
}

Item popMin(vector<Item>& A) {
    Item top = A[0];
    A[0] = A.back();
    A.pop_back();
    if (!A.empty()) heapifyDown(A, 0, (int)A.size());
    return top;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Item> all;
    string name; 
    int level;
    int seq = 0;

    // อ่านจน EOF
    while (cin >> name >> level) {
        all.push_back({name, level, seq++});
    }

    if (all.empty()) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    // สมมติ: เราจะคำนวณตำแหน่งของ "ชื่อในบรรทัดสุดท้ายตัวแรก" (เป้าหมาย)
    string targetName = all.back().name;

    // หาอย่างน้อยต้องมี target อยู่ในข้อมูล
    bool found = false;
    for (auto& x : all) if (x.name == targetName) { found = true; break; }
    if (!found) { 
        cout << "IMPOSSIBLE\n"; 
        return 0; 
    }

    // สร้าง heap (min-heap) ด้วย vector เท่านั้น
    vector<Item> heap = all;
    buildMinHeap(heap);

    // นับจำนวนคนที่จะได้คิวก่อนถึง target
    int wait = 0;
    while (!heap.empty()) {
        Item cur = popMin(heap);
        if (cur.name == targetName) break; // ถึงคิว target แล้ว
        ++wait;
    }

    cout << "GET QUEUE : " << wait << "\n";
    return 0;
}
