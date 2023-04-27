#include <bits/stdc++.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <iostream>
#include <limits>

using namespace std;

int minKey(const vector<int>& key, const vector<bool>& visited) {
    int min = std::numeric_limits<int>::max(), min_index;
    for (int v = 0; v < key.size(); v++)
        if (!visited[v] && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void primMST(const vector<vector<int>>& graph, bool disp = false) {
    int V = graph.size();
    vector<int> parent(V);
    vector<int> key(V, std::numeric_limits<int>::max());
    vector<bool> visited(V, false);

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, visited);
        visited[u] = true;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && visited[v] && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
}

vector<vector<int>> read(string name, int count) {
    vector<vector<int>> matrix;
    string line, number_str;
    int number;

    ifstream file(name, ios::in);
    if (!file.is_open()) {
        cout << "Could not open the file\n";
        return matrix;
    }

    int kol_count = 0;
    while (getline(file, line) && kol_count < count) {
        stringstream ss(line);
        vector<int> kol;
        while (getline(ss, number_str, ',')) {
            try {
                number = stoi(number_str);
                kol.push_back(number);
            }
            catch (invalid_argument e) {
            }
        }
        if (!kol.empty()) {
            matrix.push_back(kol);
            kol_count++;
        }
    }

    file.close();
    return matrix;
}

int main() {
    vector<double> times;
    int krok = 100;
    int num_rep = 10;
    int instances = 1000 / krok;
    bool draw = false;

    for (int i = 1; i <= instances; i++) {
        vector<vector<int>> matrix = read("test.txt", i * 100);
        times.clear(); 
        for (int j = 0; j < num_rep; j++) {
            auto start_time = std::chrono::high_resolution_clock::now();
            primMST(matrix, false);
            auto end_time = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
            times.push_back(elapsed.count());
        }
        double avg_time = accumulate(times.begin(), times.end(), 0.0) / times.size(); // fix the accumulate call
        primMST(matrix, draw);
        cout << "\nSredni czas n=" << i * krok << " to " << avg_time << " ms\n";
    }

    system("pause");
    return 0;
}

