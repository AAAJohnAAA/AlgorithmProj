#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

struct Point {
    double x, y;
};

double dist(const Point& a, const Point& b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

double pathLength(const vector<Point>& points, const vector<int>& path) {
    double sum = 0;
    for (size_t i = 1; i < path.size(); ++i) {
        sum += dist(points[path[i - 1]], points[path[i]]);
    }
    return sum;
}

vector<int> nearestNeighbor(const vector<Point>& points) {
    int n = (int)points.size();
    vector<bool> visited(n, false);
    vector<int> path;
    path.reserve(n + 1);

    int current = 0;
    path.push_back(current);
    visited[current] = true;

    for (int step = 1; step < n; ++step) {
        double minDist = 1e20;
        int next = -1;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                double d = dist(points[current], points[i]);
                if (d < minDist) {
                    minDist = d;
                    next = i;
                }
            }
        }
        current = next;
        path.push_back(current);
        visited[current] = true;
    }
    path.push_back(path[0]);
    return path;
}

void twoOptSwap(vector<int>& path, int i, int k) {
    while (i < k) {
        swap(path[i], path[k]);
        ++i;
        --k;
    }
}

void twoOpt(const vector<Point>& points, vector<int>& path, int maxIter) {
    int n = (int)path.size() - 1;
    bool improved = true;
    int iter = 0;

    while (improved && iter < maxIter) {
        improved = false;
        ++iter;
        for (int i = 1; i < n - 1; ++i) {
            for (int k = i + 1; k < n; ++k) {
                double d1 = dist(points[path[i - 1]], points[path[i]]) + dist(points[path[k]], points[path[k + 1]]);
                double d2 = dist(points[path[i - 1]], points[path[k]]) + dist(points[path[i]], points[path[k + 1]]);
                if (d2 < d1) {
                    twoOptSwap(path, i, k);
                    improved = true;
                }
            }
            if (improved) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cout.precision(6);
    cout << fixed;

    int n;
    cout << "请输入点的数量：";
    cin >> n;
    if (n < 2) {
        cout << "点数至少为2" << endl;
        return 0;
    }

    int k;
    cout << "请输入2-opt最大迭代次数 k：";
    cin >> k;
    if (k < 1) {
        cout << "迭代次数至少为1" << endl;
        return 0;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1000);

    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        points[i] = { dis(gen), dis(gen) };
    }

    auto start = high_resolution_clock::now();

    vector<int> path = nearestNeighbor(points);
    twoOpt(points, path, k);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    double length = pathLength(points, path);

    cout << "点数量: " << n << "\n";
    cout << "路径总长度: " << length << "\n";
    cout << "运行时间: " << duration.count() << " 毫秒\n";

    return 0;
}
