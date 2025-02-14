#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> getOrder(vector<vector<int>>& tasks) {
    int n = tasks.size();
    vector<pair<int, pair<int, int>>> sortedTasks;
    
    for (int i = 0; i < n; i++) {
        sortedTasks.push_back({tasks[i][0], {tasks[i][1], i}});
    }
    sort(sortedTasks.begin(), sortedTasks.end());

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> result;
    long long time = 0;
    int index = 0;

    while (index < n || !pq.empty()) {
        if (pq.empty()) {
            time = max(time, (long long)sortedTasks[index].first);
        }
        while (index < n && sortedTasks[index].first <= time) {
            pq.push({sortedTasks[index].second.first, sortedTasks[index].second.second});
            index++;
        }
        pair<int, int> top = pq.top();
        pq.pop();
        time += top.first;
        result.push_back(top.second);
    }

    return result;
}

int main() {
    vector<vector<int>> tasks = {{1, 2}, {2, 4}, {3, 2}, {4, 1}};
    vector<int> order = getOrder(tasks);
    for (int i : order) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
