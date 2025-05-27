/*
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

const int MAX_N = 20; // ����������
int n; // ����
double dist[MAX_N][MAX_N]; // �������
bool visited[MAX_N];
double minCost = numeric_limits<double>::max();
vector<int> bestPath;
vector<int> path;

// ��������ŷ����þ���
double calcDistance(pair<double, double>& a, pair<double, double>& b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

// ���ݺ���
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
            if (newCost < minCost) { // ��֦
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
    cout << "�������ĸ��� (���20): ";
    cin >> n;
    if (n > MAX_N || n <= 1) {
        cout << "����������2��" << MAX_N << "֮�䣡" << endl;
        return 1;
    }

    vector<pair<double, double>> points(n);
    for (int i = 0; i < n; i++) {
        points[i].first = rand() % 1000;
        points[i].second = rand() % 1000;
    }

    // ����������
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
    cout << "�ܵ���: " << n << endl;
    cout << "·���ܳ���: " << minCost << endl;
    cout << "����ʱ��: " << elapsed.count() << " ��" << endl;

    return 0;
}
*/