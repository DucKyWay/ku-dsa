#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ลึก
void dfs(int curr, int endTower, vector<vector<int>> &graph, vector<bool> &visited, int &total) {
    
    if (curr == endTower) {
        total++;
        return;
    }
    visited[curr] = true;

    for (int next : graph[curr]) {
        if (!visited[next])
            dfs(next, endTower, graph, visited, total);
    }
    visited[curr] = false;
}

// กว้าง
vector<int> bfs(int start, int goal, vector<vector<int>> &graph, int nTower) {
    vector<int> parent(nTower, -1);
    vector<bool> done(nTower, false);
    queue<int> q;

    q.push(start);
    done[start] = true;

    while (!q.empty()) {
        
        int curr = q.front();
        q.pop();

        if (curr == goal) break;
        for (int next : graph[curr]) {
            if (!done[next]) {
                done[next] = true;
                parent[next] = curr;
                q.push(next);
            }
        }
    }

    if (!done[goal]) return {};

    vector<int> path;
    int cur = goal;
    while (cur != -1) {
        path.push_back(cur);
        cur = parent[cur];
    }

    // implement reverse :(
    vector<int> rev;
    for (int i = (int)path.size() - 1; i >= 0; i--) {
        rev.push_back(path[i]);
    }

    return rev;
}

int main() {
    
    int nTower, nBridge;
    cin >> nTower >> nBridge;

    vector<vector<int>> graph(nTower);

    for (int i = 0; i < nBridge; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int sTower, eTower;
    cin >> sTower >> eTower;

    // หาจำนวน
    vector<bool> visited(nTower, false);
    int total = 0;
    dfs(sTower, eTower, graph, visited, total);

    // สั้นสุด
    vector<int> shortPath = bfs(sTower, eTower, graph, nTower);

    if (shortPath.empty()) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << total << "\n";
        for (int i = 0; i < (int)shortPath.size(); i++) {
            if (i > 0) 
                cout << " ";
            cout << shortPath[i];
        }
        cout << "\n";
    }

    return 0;
}
