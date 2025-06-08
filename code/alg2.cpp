#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int MAX_N = 20; // 最大点数限制
int n; // 点数
double dist[MAX_N][MAX_N]; // 距离矩阵
bool visited[MAX_N];
double minCost = numeric_limits<double>::max();
vector<int> bestPath;
vector<int> path;

// 计算两点欧几里得距离
double calcDistance(pair<double, double>& a, pair<double, double>& b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

// 回溯函数
void backtrack(int currentNode, int visitedCount, double currentCost) {
    if (visitedCount == n) {
        if (dist[currentNode][0] > 0) {
            double totalCost = currentCost + dist[currentNode][0];
            if (totalCost < minCost) {
                minCost = totalCost;
                bestPath = path;
                bestPath.push_back(0);
            }
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[currentNode][i] > 0) {
            double newCost = currentCost + dist[currentNode][i];
            if (newCost < minCost) { // 剪枝
                visited[i] = true;
                path.push_back(i);
                backtrack(i, visitedCount + 1, newCost);
                visited[i] = false;
                path.pop_back();
            }
        }
    }
}

int main() {
    srand(time(0));
    cout << "请输入点的个数 (最多20): ";
    cin >> n;
    if (n > MAX_N || n <= 1) {
        cout << "点数必须在2到" << MAX_N << "之间！" << endl;
        return 1;
    }

    vector<pair<double, double>> points(n);
    for (int i = 0; i < n; i++) {
        points[i].first = rand() % 1000;
        points[i].second = rand() % 1000;
    }

    // 计算距离矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = calcDistance(points[i], points[j]);
        }
    }

    for (int i = 0; i < n; i++) visited[i] = false;
    visited[0] = true;
    path.push_back(0);

    auto start = high_resolution_clock::now();
    backtrack(0, 1, 0);
    auto end = high_resolution_clock::now();

    duration<double> elapsed = end - start;

    cout << fixed << setprecision(2);
    cout << "总点数: " << n << endl;
    cout << "路径总长度: " << minCost << endl;
    cout << "运行时间: " << elapsed.count() << " 秒" << endl;

    return 0;
}
