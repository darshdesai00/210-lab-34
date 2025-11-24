#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

const int SIZE = 9;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;

    // Airport labels (same order as nodes 0–8)
    vector<string> airportNames = {
        "SFO - San Francisco (Check-In Terminal)",
        "LAX - Los Angeles (Security Gate)",
        "SEA - Seattle (Main Terminal)",
        "DEN - Denver (Food Court)",
        "PHX - Phoenix (Passenger Lounge)",
        "DFW - Dallas (Shuttle Depot)",
        "ORD - Chicago (Runway Access)",
        "ATL - Atlanta (Baggage Claim)",
        "JFK - New York (Parking Garage)"
    };

    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);

        for (auto &edge : edges) {
            adjList[edge.src].push_back({edge.dest, edge.weight});
            adjList[edge.dest].push_back({edge.src, edge.weight});
        }
    }

    // ===============================
    //       Airport Network Print
    // ===============================
    void printAirportNetwork() {
        cout << "Airport Transportation Network:\n";
        cout << "====================================\n\n";

        for (int i = 0; i < SIZE; i++) {
            cout << airportNames[i] << " connects to:\n";
            for (auto &v : adjList[i]) {
                cout << "  → " << airportNames[v.first]
                     << " (Travel Time: " << v.second << " minutes)\n";
            }
            cout << endl;
        }
    }

    // ===============================
    //              DFS
    // ===============================
    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> s;

        s.push(start);

        cout << "Airport Route Exploration (DFS) from " 
             << airportNames[start] << ":\n";
        cout << "=====================================\n";

        while (!s.empty()) {
            int v = s.top();
            s.pop();

            if (!visited[v]) {
                visited[v] = true;

                cout << "Inspecting: " << airportNames[v] << endl;

                for (int i = adjList[v].size() - 1; i >= 0; i--) {
                    int neighbor = adjList[v][i].first;
                    int dist = adjList[v][i].second;

                    if (!visited[neighbor]) {
                        cout << "  → Possible next hop: " 
                             << airportNames[neighbor]
                             << " (" << dist << " minutes)\n";
                        s.push(neighbor);
                    }
                }
                cout << endl;
            }
        }
        cout << endl;
    }

    // ===============================
    //              BFS
    // ===============================
    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "Airport Layer-by-Layer Reachability (BFS) from "
             << airportNames[start] << ":\n";
        cout << "=============================================\n";

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            cout << "Checking: " << airportNames[v] << endl;

            for (auto &neighbor : adjList[v]) {
                int next = neighbor.first;
                int dist = neighbor.second;

                if (!visited[next]) {
                    visited[next] = true;
                    cout << "  → Reaching next area: " 
                         << airportNames[next]
                         << " (" << dist << " minutes)\n";
                    q.push(next);
                }
            }
            cout << endl;
        }
        cout << endl;
    }
};

int main() {

    // Step 2 graph (unchanged)
    vector<Edge> edges = {
        {0, 1, 8}, {0, 2, 21},
        {1, 2, 6}, {1, 3, 5}, {1, 4, 4},
        {2, 7, 11}, {2, 8, 8},
        {3, 4, 9},
        {5, 6, 10}, {5, 7, 15}, {5, 8, 5},
        {6, 7, 3}, {6, 8, 7},
        {7, 8, 11}
    };

    Graph graph(edges);

    graph.printAirportNetwork();
    graph.DFS(0);  // Start DFS at San Francisco
    graph.BFS(0);  // Start BFS at San Francisco

    return 0;
}
