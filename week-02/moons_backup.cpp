#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <tuple>
#include <iomanip>

using namespace std;

struct Pos {
    int x, y, z;
};

struct MoveCmd {
    char dir;
    int step;
};

int ns, nw;
vector<vector<vector<int>>> map3D;    // พื้นที่ 3 มิติ
vector<MoveCmd> whispers;
int step_count = 1;
vector<vector<vector<int>>> result;  // key map

// ทิศทางการเคลื่อนที่       L  R   F  B  U  D
const int dx[6] =       {-1, 1,  0, 0, 0, 0};
const int dz[6] =       { 0, 0,  1,-1, 0, 0};
const int dy[6] =       { 0, 0,  0, 0, 1,-1};
const char dirc[6] =    {'L','R','F','B','U','D'};

int get_dir_index(char d) {
    for (int i = 0; i < 6; i++)
        if (dirc[i] == d) return i;
    return -1;
}

bool in_bounds(int x, int y, int z) {
    return x >= 0 && x < ns && y >= 0 && y < ns && z >= 0 && z < ns;
}

void walk_with_whisper(Pos &p, char dir, int steps) {
    int idx = get_dir_index(dir);
    for (int i = 0; i < steps; ++i) {
        int nx = p.x + dx[idx];
        int ny = p.y + dy[idx];
        int nz = p.z + dz[idx];
        if (!in_bounds(nx, ny, nz) || map3D[ny][nx][nz] == 0 || result[ny][nx][nz] != 0)
            return; // ทางตันหรือเดินแล้ว
        result[ny][nx][nz] = -step_count++;
        p = {nx, ny, nz};
    }
}

void dfs(Pos p) {
    for (int i : {2, 0, 1, 3, 4, 5}) { // F L R B U D
        int nx = p.x + dx[i];
        int ny = p.y + dy[i];
        int nz = p.z + dz[i];
        if (!in_bounds(nx, ny, nz)) continue;
        if (map3D[ny][nx][nz] == 0 || result[ny][nx][nz] != 0) continue;
        result[ny][nx][nz] = step_count++;
        dfs({nx, ny, nz});
    }
}

int main() {
    cin >> ns >> nw;
    int sx, sz;
    char ch;
    cin >> sx >> ch >> sz;
    sx--; sz--;

    map3D = vector<vector<vector<int>>>(ns, vector<vector<int>>(ns, vector<int>(ns)));
    result = vector<vector<vector<int>>>(ns, vector<vector<int>>(ns, vector<int>(ns, 0)));

    for (int y = 0; y < ns; ++y) {
        for (int z = 0; z < ns; ++z)
            for (int x = 0; x < ns; ++x)
                cin >> map3D[y][x][z];
        string sep;
        cin >> sep; // ----------
    }

    string line;
    cin.ignore();
    for (int i = 0; i < nw; ++i) {
        getline(cin, line);
        stringstream ss(line);
        string cmd;
        while (getline(ss, cmd, ',')) {
            MoveCmd m;
            m.dir = cmd[0];
            m.step = stoi(cmd.substr(1));
            whispers.push_back(m);
        }
    }

    Pos cow = {sx, 0, sz};
    if (map3D[0][sx][sz] == 0) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    result[0][sx][sz] = -step_count++;
    for (auto &w : whispers)
        walk_with_whisper(cow, w.dir, w.step);

    dfs(cow);

    int width = to_string(ns * ns * ns).size() + 1;
    for (int y = 0; y < ns; ++y) {
        for (int z = 0; z < ns; ++z) {
            for (int x = 0; x < ns; ++x) {
                if (map3D[y][x][z] == 0) cout << setw(width) << "*";
                else cout << setw(width) << result[y][x][z];
            }
            cout << endl;
        }
        cout << "----------" << endl;
    }
    return 0;
}

/*
3 3
1,1
1 1 1
1 1 1
1 1 1
----------
1 1 1
1 1 1
1 1 1
----------
0 1 1
1 1 1
0 1 1
----------
D1,F1
U1,F1,L2
D2,B2,F1,R1
*/