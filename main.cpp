#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <limits>
using namespace std;

const int SIZE = 9;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;

    vector<string> airportNames = {
        "SFO - San Francisco",
        "LAX - Los Angeles",
        "SEA - Seattle",
        "DEN - Denver",
        "PHX - Phoenix",
        "DFW - Dallas",
        "ORD - Chicago",
        "ATL - Atlanta",
        "JFK - New York"
    };

    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);
        for (auto &edge : edges) {
            adjList[edge.src].push_back({edge.dest, edge.weight});
            adjList[edge.dest].push_back({edge.src, edge.weight});
        }
    }

    void printAirportNetwork() {
        cout << "\nAirport Transportation Network:\n\n";
        for (int i = 0; i < SIZE; i++) {
            cout << airportNames[i] << " connects to:\n";
            for (auto &v : adjList[i]) {
                cout << "  → " << airportNames[v.first]
                     << " (" << v.second << " minutes)\n";
            }
            cout << endl;
        }
    }

    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> s;
        s.push(start);

        cout << "\nDFS Route from " << airportNames[start] << ":\n\n";

        while (!s.empty()) {
            int v = s.top();
            s.pop();

            if (!visited[v]) {
                visited[v] = true;
                cout << airportNames[v] << endl;

                for (int i = adjList[v].size() - 1; i >= 0; i--) {
                    int nxt = adjList[v][i].first;
                    if (!visited[nxt]) s.push(nxt);
                }
            }
        }
        cout << endl;
    }

    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\nBFS Layers from " << airportNames[start] << ":\n\n";

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            cout << airportNames[v] << endl;

            for (auto &neighbor : adjList[v]) {
                int nxt = neighbor.first;
                if (!visited[nxt]) {
                    visited[nxt] = true;
                    q.push(nxt);
                }
            }
        }
        cout << endl;
    }

    void shortestPath(int start) {
        vector<int> dist(SIZE, numeric_limits<int>::max());
        dist[start] = 0;

        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int d = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            if (d > dist[node]) continue;

            for (auto &edge : adjList[node]) {
                int nxt = edge.first;
                int w = edge.second;

                if (dist[node] + w < dist[nxt]) {
                    dist[nxt] = dist[node] + w;
                    pq.push({dist[nxt], nxt});
                }
            }
        }

        cout << "\nShortest Paths from " << airportNames[start] << ":\n";
        for (int i = 0; i < SIZE; i++) {
            cout << start << " -> " << i << " : " << dist[i] << endl;
        }
        cout << endl;
    }

    void minimumSpanningTree() {
        vector<int> key(SIZE, numeric_limits<int>::max());
        vector<int> parent(SIZE, -1);
        vector<bool> inMST(SIZE, false);

        key[0] = 0;

        for (int i = 0; i < SIZE - 1; i++) {
            int minKey = numeric_limits<int>::max();
            int u = -1;

            for (int v = 0; v < SIZE; v++) {
                if (!inMST[v] && key[v] < minKey) {
                    minKey = key[v];
                    u = v;
                }
            }

            inMST[u] = true;

            for (auto &edge : adjList[u]) {
                int v = edge.first;
                int w = edge.second;

                if (!inMST[v] && w < key[v]) {
                    key[v] = w;
                    parent[v] = u;
                }
            }
        }

        cout << "\nMinimum Spanning Tree:\n";
        for (int i = 1; i < SIZE; i++) {
            cout << parent[i] << " - " << i
                 << " (cost: " << key[i] << ")\n";
        }
        cout << endl;
    }
};

int main() {
    vector<Edge> edges = {
        {0,1,8}, {0,2,21},
        {1,2,6}, {1,3,5}, {1,4,4},
        {2,7,11}, {2,8,8},
        {3,4,9},
        {5,6,10}, {5,7,15}, {5,8,5},
        {6,7,3}, {6,8,7},
        {7,8,11}
    };

    Graph graph(edges);

    int choice = -1;
    while (choice != 0) {
        cout << "\nAirport Network Menu:\n";
        cout << "[1] Display airport network\n";
        cout << "[2] DFS\n";
        cout << "[3] BFS\n";
        cout << "[4] Shortest paths\n";
        cout << "[5] Minimum Spanning Tree\n";
        cout << "[0] Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: graph.printAirportNetwork(); break;
            case 2: graph.DFS(0); break;
            case 3: graph.BFS(0); break;
            case 4: graph.shortestPath(0); break;
            case 5: graph.minimumSpanningTree(); break;
            case 0: break;
            default: cout << "Invalid option.\n";
        }
    }

    return 0;
}
