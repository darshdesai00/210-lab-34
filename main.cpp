#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

const int SIZE = 7;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;

    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);
        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;
            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    void printGraph() {
        cout << "Graph's adjacency list:\n";
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    // DFS (Depth-First Search)
    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> s;

        s.push(start);
        visited[start] = true;

        cout << "DFS starting from vertex " << start << ":\n";

        while (!s.empty()) {
            int v = s.top();
            s.pop();
            cout << v << " ";

            for (auto &neighbor : adjList[v]) {
                int next = neighbor.first;
                if (!visited[next]) {
                    visited[next] = true;
                    s.push(next);
                }
            }
        }

        cout << endl;
    }

    // BFS (Breadth-First Search)
    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        cout << "BFS starting from vertex " << start << ":\n";

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (auto &neighbor : adjList[v]) {
                int next = neighbor.first;
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }

        cout << endl;
    }
};

int main() {
    vector<Edge> edges = {
        {0,1,12},{0,2,8},{0,3,21},
        {2,3,6},{2,6,2},{5,6,6},
        {4,5,9},{2,4,4},{2,5,5}
    };

    Graph graph(edges);

    graph.printGraph();
    cout << endl;

    graph.DFS(0);
    graph.BFS(0);

    return 0;
}
