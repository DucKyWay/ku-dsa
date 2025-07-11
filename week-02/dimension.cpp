#include <iostream>
#include <iomanip>

using namespace std;

struct Rectangle {
    double x1, y1, x2, y2;
};

double findMin(double a, double b) {
    return (a < b) ? a : b;
}
double findMax(double a, double b) {
    return (a > b) ? a : b;
}

// intersect a, b
double intersectArea(Rectangle a, Rectangle b) {
    double x_left = findMax(a.x1, b.x1);
    double y_bottom = findMax(a.y1, b.y1);
    double x_right = findMin(a.x2, b.x2);
    double y_top = findMin(a.y2, b.y2);

    if (x_right <= x_left || y_top <= y_bottom)
        return 0.0;

    return (x_right - x_left) * (y_top - y_bottom);
}

int main() {
    int n;
    cin >> n;

    Rectangle rects[10005];

    for (int i = 0; i < n; ++i) {
        cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
    }

    double maxArea = 0.0;

    // check all rectangle intersect and find area
    for (int i = 0; i < n; ++i) {
        Rectangle base = rects[i];
        for (int j = i + 1; j < n; ++j) {
            double area = intersectArea(base, rects[j]);
            if (area > maxArea)
                maxArea = area;
        }
    }

    cout << fixed << setprecision(6) << maxArea << endl;
    return 0;
}
