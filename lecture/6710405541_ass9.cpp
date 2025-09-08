/*
แบบฝึกหัดในสไลด์ wk9.3 หน้า 19
ให้นิสิตเขียนโปรแกรมภาษา C/C++ เพื่อทำงานต่อไปนี้
1. สร้างกราฟเพื่อแสดงเขาวงกต ดังภาพในสไลด์
2. สร้างฟังก์ชันในการสำรวจกราฟโดยใช้ BFS เพื่อตรวจสอบว่ามีเส้นทางจาก S ไปยัง F หรือไม่ (answer: yes/no)

You are to create a C/C++ program that does the followings:
1. Create the graph that can represents the above maze.
2. Traverse the graph using BFS to check whether there is a path from S to F
(answer “YES” if there is path, and answer “NO” otherwise)
*/

#include <bits/stdc++.h>
using namespace std;

void addEdge(vector<vector<int>>& graph, int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
}

vector<int> bfs(int start, int finish, const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> parent(n, -1);
    queue<int> q;

    q.push(start);
    parent[start] = start;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == finish) break;

        for (int v : graph[u]) {
            if (parent[v] == -1) {
                parent[v] = u;
                q.push(v);
            }
        }
    }

    // สร้าง path กลับ start
    vector<int> path;
    if (parent[finish] != -1) {
        for (int v = finish; v != start; v = parent[v]) {
            path.push_back(v);
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
    }

    return path;
}

int main() {
    
    int n = 14;
    vector<vector<int>> graph(n);

    addEdge(graph, 0, 1);  // S - A
    addEdge(graph, 1, 2);  // A - B
    addEdge(graph, 2, 3);  // B - C
    addEdge(graph, 3, 4);  // C - D
    addEdge(graph, 4, 5);  // D - E
    addEdge(graph, 5, 6);  // E - F

    // แยก
    addEdge(graph, 2, 7);  // B - G
    addEdge(graph, 7, 8);  // G - H
    addEdge(graph, 8, 4);  // H - D

    // แยกซ้อนแยก
    addEdge(graph, 7, 9);   // G - I
    addEdge(graph, 9, 10);  // I - J
    addEdge(graph, 10, 11); // J - K
    addEdge(graph, 11, 12); // K - L
    addEdge(graph, 12, 13); // L - M
    addEdge(graph, 13, 5);  // M - E

    vector<int> path = bfs(0, 6, graph);

    if (!path.empty()) {
        cout << "YES" << endl;
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}