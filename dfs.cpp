#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

const int MAX = 100000; // Maximum number of nodes
vector<int> graph[MAX]; // Adjacency list
bool visited[MAX];      // Track visited nodes

// Parallel Depth First Search (DFS)
void parallel_dfs(int start_node) {
    stack<int> s;
    s.push(start_node);

    while (!s.empty()) {
        int curr_node;

        // Protect stack operations using a critical section
        #pragma omp critical
        {
            curr_node = s.top();
            s.pop();
        }

        if (!visited[curr_node]) {
            visited[curr_node] = true;
            cout << curr_node << " ";  // Output visited node

            // Parallel loop to process adjacent nodes
            #pragma omp parallel for
            for (int i = graph[curr_node].size() - 1; i >= 0; i--) { // Reverse order for correct DFS
                int adj_node = graph[curr_node][i];

                // Ensure only unvisited nodes are pushed
                if (!visited[adj_node]) {
                    #pragma omp critical
                    s.push(adj_node);
                }
            }
        }
    }
}

int main() {
    int n, m, start_node;
    cout << "Enter number of nodes, edges, and starting node: ";
    cin >> n >> m >> start_node;

    cout << "Enter " << m << " pairs of edges (u v):\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // Undirected graph
    }

    // Initialize visited array in parallel
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    cout << "Nodes visited in DFS order: ";
    parallel_dfs(start_node);
    cout << endl;

    return 0;
}
