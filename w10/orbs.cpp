#include <iostream>
#include <vector>
using namespace std;

void heapify(vector<int>& arr, int n, int i) {
    int large = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[large])
        large = left;

    if (right < n && arr[right] > arr[large])
        large = right;

    if (large != i) {
        // swap largest to last
        int temp = arr[i];
        arr[i] = arr[large];
        arr[large] = temp;

        // heap only ที่เหลือ
        heapify(arr, n, large);
    }
}

// bottom to top
void buildMaxHeap(vector<int>& arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// root <-> last element
void heapSort(vector<int>& arr, int n) {
    buildMaxHeap(arr, n);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> power(n);
    for (int i = 0; i < n; i++) {
        cin >> power[i];
    }

    heapSort(power, n);

    // max to min
    for (int i = n - 1; i >= 0; i--) {
        cout << power[i];
        if (i > 0) cout << " ";
    }
    cout << endl;

    return 0;
}
