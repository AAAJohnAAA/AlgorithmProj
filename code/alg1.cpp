#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace std::chrono;

const int POINT_COUNT = 5000;

struct Point {
    double x, y;
    bool visited;
};

double distance(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

vector<int> nearestNeighborTSP(vector<Point>& points) {
    int n = points.size();
    vector<int> path;
    path.push_back(0);
    points[0].visited = true;

    int current = 0;
    for (int step = 1; step < n; ++step) {
        double minDist = numeric_limits<double>::max();
        int next = -1;
        for (int i = 0; i < n; ++i) {
            if (!points[i].visited) {
                double d = distance(points[current], points[i]);
                if (d < minDist) {
                    minDist = d;
                    next = i;
                }
            }
        }
        if (next != -1) {
            points[next].visited = true;
            path.push_back(next);
            current = next;
        }
    }

    path.push_back(0);
    return path;
}

double calculateTotalDistance(const vector<Point>& points, const vector<int>& path) {
    double total = 0.0;
    for (size_t i = 1; i < path.size(); ++i) {
        total += distance(points[path[i - 1]], points[path[i]]);
    }
    return total;
}

int main() {
    srand(time(0));

    vector<Point> points(POINT_COUNT);
    for (int i = 0; i < POINT_COUNT; ++i) {
        points[i].x = rand() % 1000;
        points[i].y = rand() % 1000;
        points[i].visited = false;
    }

    auto start = high_resolution_clock::now();

    vector<int> path = nearestNeighborTSP(points);
    double totalDist = calculateTotalDistance(points, path);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    cout << fixed << setprecision(2);
    cout << "总点数: " << POINT_COUNT << endl;
    cout << "路径总长度: " << totalDist << endl;
    cout << "运行时间: " << duration.count() << " 毫秒" << endl;

    return 0;
}
