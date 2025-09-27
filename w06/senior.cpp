#include <iostream>
#include <vector>

using namespace std;

int binarySearch(const vector<int>& list, int target) {
    int left = 0, right = list.size() - 1;
    int round = 0;
    
    while(left <= right) {
        round++;
        int mid = left + (right - left) / 2;

        if(list[mid] == target) {
            return round;
        }
        else if(list[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    vector<int> on_event;
    int find;
    
    while(cin >> find) {
        on_event.push_back(find);
    }
    
    int target = on_event.back();
    on_event.pop_back();
    
    int i = binarySearch(on_event, target);
    if(i != -1) {
        cout << "Present - " << i << endl;
    } else {
        cout << "Absent" << endl;
    }

    return 0;
}

/*
1 3 4 5 8 9 15
4

7 8 9 16 34 38
39
*/
