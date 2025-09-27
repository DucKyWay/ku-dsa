#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// โครงสร้างเก็บพิกัด 3 มิติ
struct Pos {
    int x, y, z;
};

// คำสั่งเคลื่อนที่ (ทิศทางและจำนวนก้าว)
struct MoveCmd {
    char dir;  // 'L','R','F','B','U','D'
    int step;  // จำนวนก้าว
};

// คลาสจัดการเขาวงกต 3 มิติ พร้อมวิธีโหลดข้อมูลและคำนวณผล
class Maze3D {
private:
    int ns, nw;                                      // ขนาดช่อง (ns) และจำนวนคำสั่งwhispeer (nw)
    vector<MoveCmd> whispers;
    vector<vector<vector<int>>> map3D, result;       // แผนที่และผลลัพธ์การเดิน
    int stepCount;                                   // ตัวนับก้าวแสดงลำดับการเดิน
    // เวกเตอร์เก็บการเคลื่อนที่ตามแกน x,y,z 6 ทิศทาง
    const int dx[6] = {-1, 1, 0, 0, 0, 0};
    const int dz[6] = { 0, 0, 1,-1, 0, 0};
    const int dy[6] = { 0, 0, 0, 0, 1,-1};
    const char dirc[6] = {'L','R','F','B','U','D'}; // รหัสทิศทาง

public:
    Maze3D(int size, int w): ns(size), nw(w), stepCount(1) {
        map3D.assign(ns, vector<vector<int>>(ns, vector<int>(ns)));
        result.assign(ns, vector<vector<int>>(ns, vector<int>(ns, 0)));
    }

    void loadMap(istream& in) {
        string sep;
        for (int y = 0; y < ns; ++y) {
            for (int z = 0; z < ns; ++z) {
                for (int x = 0; x < ns; ++x) {
                    in >> map3D[y][x][z];
                }
            }
            in >> sep; // อ่านเส้นคั่น ("----------")
        }
    }

    void loadWhispers(istream& in) {
        string line;
        getline(in, line); // ข้ามบรรทัดว่างหลัง map input
        for (int i = 0; i < nw; ++i) {
            getline(in, line);
            stringstream ss(line);
            string cmd;
            while (getline(ss, cmd, ',')) { 
                MoveCmd m;
                m.dir = cmd[0];
                m.step = stoi(cmd.substr(1));
                whispers.push_back(m);
            }
        }
    }

    // ฟังก์ชันหลัก: ตรวจจับจุดเริ่ม, เดินตามกระซิบ, แล้ว dfs สำรวจพื้นที่ที่เดินถึง
    void solve(Pos start) {
        // ถ้าตำแหน่งเริ่มไม่ใช่พื้นที่เดินได้ ให้จบ
        if (map3D[start.y][start.x][start.z] == 0) {
            cout << "IMPOSSIBLE" << endl;
            return;
        }
        Pos cow = start;
        result[cow.y][cow.x][cow.z] = -stepCount++; // ตำแหน่งเริ่มเป็นก้าวแรก (ลบไว้)

        // เดินตามคำสั่งกระซิบ
        for (auto& w : whispers)
            walkWithWhisper(cow, w);

        // จากตำแหน่งสุดท้าย เริ่ม DFS สำรวจพื้นที่ต่อ
        dfs(cow);

        // แสดงผลลัพธ์
        printResult();
    }

private:
    // หา index ของทิศทางจากตัวอักษร
    int getDirIndex(char d) const {
        for (int i = 0; i < 6; ++i)
            if (dirc[i] == d)
                return i;
        return -1;
    }

    // ตรวจสอบขอบเขตภายในเขาวงกต
    bool inBounds(int x, int y, int z) const {
        return x >= 0 && x < ns && y >= 0 && y < ns && z >= 0 && z < ns;
    }

    // เดินตามกระซิบทีละก้าว ถ้าเจออุปสรรคหรือเคยเดินแล้วหยุด
    void walkWithWhisper(Pos& p, const MoveCmd& w) {
        int idx = getDirIndex(w.dir);
        for (int i = 0; i < w.step; ++i) {
            int nx = p.x + dx[idx];
            int ny = p.y + dy[idx];
            int nz = p.z + dz[idx];
            if (!inBounds(nx, ny, nz) || map3D[ny][nx][nz] == 0 || result[ny][nx][nz] != 0)
                return;
            result[ny][nx][nz] = -stepCount++;
            p = {nx, ny, nz};
        }
    }

    // DFS สำรวจพื้นที่รอบ ๆ
    void dfs(const Pos& p) {
        for (int i : {2, 0, 1, 3, 4, 5}) { // ลำดับ F, L, R, B, U, D
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];
            int nz = p.z + dz[i];
            if (!inBounds(nx, ny, nz) || map3D[ny][nx][nz] == 0 || result[ny][nx][nz] != 0)
                continue;
            result[ny][nx][nz] = stepCount++;
            dfs({nx, ny, nz});
        }
    }

    // แสดงผลลัพธ์ในรูปแบบตาราง พร้อมเครื่องหมาย '*' สำหรับบล็อก
    void printResult() const {
        int maxSteps = ns * ns * ns;
        int width = to_string(maxSteps).size() + 1;
        for (int y = 0; y < ns; ++y) {
            for (int z = 0; z < ns; ++z) {
                for (int x = 0; x < ns; ++x) {
                    if (map3D[y][x][z] == 0)
                        cout << setw(width) << "*";
                    else
                        cout << setw(width) << result[y][x][z];
                }
                cout << endl;
            }
            cout << "----------" << endl;
        }
    }
};

int main() {
    int ns, nw;
    char sep;
    cin >> ns >> nw;
    int sx, sz;
    cin >> sx >> sep >> sz;
    --sx; --sz; // ปรับเป็น 0-based index

    Maze3D maze(ns, nw);
    maze.loadMap(cin);
    maze.loadWhispers(cin);

    Pos start{sx, 0, sz};
    maze.solve(start);       

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