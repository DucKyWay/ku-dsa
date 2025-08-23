#include <iostream>
#include <vector>
using namespace std;

const int TABLE_SIZE = 20;

typedef struct tools {
    string name;
    double x, y, z;
} Tools;


int main() {

    vector<Tools> tool_list;
    Tools tool;

    while(true) {
        cin >> tool.name;
        if(tool.name == "--------------------") {
            break;
        }
        cin >> tool.x >> tool.y >> tool.z;
        tool_list.push_back(tool);  
    };

    char search[TABLE_SIZE];
    while(cin >> search) {
        bool find = false;
        for(int i = 0; i < tool_list.size(); i++) {
            if(tool_list[i].name == search) {
                find = true;
                cout << "( " << tool_list[i].x << tool_list[i].y << tool_list[i].z << " )" << endl;
                break;
            }
        }
        if(find == false) {
            cout << "Item not found." << endl;
        }
    }
    
    return 0;
}