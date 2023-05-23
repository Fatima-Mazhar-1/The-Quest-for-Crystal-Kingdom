
#pragma once
#include"linkedList.h"
#include"Map.h"
#include<algorithm>
#include"vector.h"//vector


template<class T>
class Graph {

public:
    int** Matrix;
    int Vertices;
    Graph(int v = 0) :Vertices(v) {
        if (v == 0) {
            Matrix = NULL;
        }
        else {
            Matrix = new int* [Vertices];
            for (int i = 0; i < Vertices; i++) {
                Matrix[i] = new int[Vertices];
            }
            for (int i = 0; i < Vertices; i++) {
                for (int j = 0; j < Vertices; j++) {
                    Matrix[i][j] = std::numeric_limits<int>::max();
                }
            }
        }
    }
    void convertToMatrix(Map map, int row, int cols) {
        int count = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < cols; j++) {
                if (map.getNumberAtindex(i, j) == count) {
                    Matrix[count][count] = 0;
                    if (i + 1 < row) {
                        if (map.getCharAtindex(i + 1, j) == '%')
                            Matrix[count][count + row] = 1000;
                        else if (map.getCharAtindex(i + 1, j) == '#' || map.getCharAtindex(i + 1, j) == '@' ||
                            map.getCharAtindex(i + 1, j) == '&' || map.getCharAtindex(i + 1, j) == '$') {
                            Matrix[count][count + row] = 100;

                        }
                        else {
                            Matrix[count][count + row] = 1;
                        }
                    }
                    if (i - 1 >= 0) {
                        if (map.getCharAtindex(i - 1, j) == '%')
                            Matrix[count][count - row] = 1000;
                        else if (map.getCharAtindex(i - 1, j) == '#' || map.getCharAtindex(i - 1, j) == '@' ||
                            map.getCharAtindex(i - 1, j) == '&' || map.getCharAtindex(i - 1, j) == '$') {
                            Matrix[count][count - row] = 100;

                        }
                        else {
                            Matrix[count][count - row] = 1;
                        }
                    }
                    if (j + 1 < cols) {
                        if (map.getCharAtindex(i, j + 1) == '%')
                            Matrix[count][count + 1] = 1000;
                        else if (map.getCharAtindex(i, j + 1) == '#' || map.getCharAtindex(i, j + 1) == '@' ||
                            map.getCharAtindex(i, j + 1) == '&' || map.getCharAtindex(i, j + 1) == '$') {
                            Matrix[count][count + 1] = 100;

                        }
                        else {
                            Matrix[count][count + 1] = 1;
                        }
                    }
                    if (j - 1 >= 0) {
                        if (map.getCharAtindex(i, j - 1) == '%')
                            Matrix[count][count - 1] = 1000;
                        else if (map.getCharAtindex(i, j - 1) == '#' || map.getCharAtindex(i, j - 1) == '@' ||
                            map.getCharAtindex(i, j - 1) == '&' || map.getCharAtindex(i, j - 1) == '$') {
                            Matrix[count][count - 1] = 100;

                        }
                        else {
                            Matrix[count][count - 1] = 1;
                        }
                    }
                }
                count++;
            }
        }
        int i = row - 1;
        int j = cols - 1;
        if (map.getNumberAtindex(i, j) == count) {
            Matrix[count][count] = 0;
            if (i + 1 < row) {
                if (map.getCharAtindex(i + 1, j) == '%')
                    Matrix[count][count + row] = 1000;
                else if (map.getCharAtindex(i + 1, j) == '#' || map.getCharAtindex(i + 1, j) == '@' ||
                    map.getCharAtindex(i + 1, j) == '&' || map.getCharAtindex(i + 1, j) == '$') {
                    Matrix[count][count + row] = 100;

                }
                else {
                    Matrix[count][count + row] = 1;
                }
            }
            if (i - 1 > 0) {
                if (map.getCharAtindex(i - 1, j) == '%')
                    Matrix[count][count - row] = 1000;
                else if (map.getCharAtindex(i - 1, j) == '#' || map.getCharAtindex(i - 1, j) == '@' ||
                    map.getCharAtindex(i - 1, j) == '&' || map.getCharAtindex(i - 1, j) == '$') {
                    Matrix[count][count - row] = 100;

                }
                else {
                    Matrix[count][count - row] = 1;
                }
            }
            if (j + 1 < cols) {
                if (map.getCharAtindex(i, j + 1) == '%')
                    Matrix[count][count + 1] = 1000;
                else if (map.getCharAtindex(i, j + 1) == '#' || map.getCharAtindex(i, j + 1) == '@' ||
                    map.getCharAtindex(i, j + 1) == '&' || map.getCharAtindex(i, j + 1) == '$') {
                    Matrix[count][count + 1] = 100;

                }
                else {
                    Matrix[count][count + 1] = 1;
                }
            }
            if (j - 1 > 0) {
                if (map.getCharAtindex(i, j - 1) == '%')
                    Matrix[count][count - 1] = 1000;
                else if (map.getCharAtindex(i, j - 1) == '#' || map.getCharAtindex(i, j - 1) == '@' ||
                    map.getCharAtindex(i, j - 1) == '&' || map.getCharAtindex(i, j - 1) == '$') {
                    Matrix[count][count - 1] = 100;

                }
                else {
                    Matrix[count][count - 1] = 1;
                }
            }
        }
    }
    void PrintMatrix() {
        for (int i = 0; i < Vertices; i++) {
            for (int j = 0; j < Vertices; j++) {
                cout << Matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};



void dijkstra(int** graph, int num_vertices, int source,int dest)
{
    int* dist = new int[num_vertices];
    bool* visited = new bool[num_vertices];
    int* prev = new int[num_vertices];

    int i = 0;
    while (i < num_vertices) {
        dist[i] = std::numeric_limits<int>::max();
        visited[i] = false;
        prev[i] = -1;
        i++;
    }

    dist[source] = 0;

    int a = 0;
    while (a < num_vertices - 1) {
        int min_dist = abs(std::numeric_limits<int>::max());
        int min_vertex;

        int j = 0;
        while (j < num_vertices) {
            if (!visited[j] && dist[j] <= min_dist) {
                min_dist = dist[j];
                min_vertex = j;
            }
            j++;
        }

        visited[min_vertex] = true;

        int k = 0;
        while (k < num_vertices) {
            int weight = graph[min_vertex][k];
            (weight > 0) ? ((dist[min_vertex] + weight < dist[k] && dist[min_vertex] + weight > 0)
                ? (dist[k] = dist[min_vertex] + weight, prev[k] = min_vertex)
                : 0)
                : 0;
            k++;
        }

        a++;
    }

    int b = 0;
    do {
        if (dist[b] != std::numeric_limits<int>::max())
            cout << "Shortest distance from " << source << " to " << b << " is: " << dist[b] << endl;
        b++;
    } while (b < num_vertices);
    cout << endl;
    cout << "Shortest Distance from (0,0) to Crystal: " << dist[dest]<<endl;

    delete[] dist;
    delete[] visited;
    delete[] prev;
}


void floyd(int** graph, int n, int source,int dest) {

    // Initialize distances with the graph
    int** dist = new int* [n];
    for (int i = 0; i < n; i++) {
        dist[i] = new int[n];
        for (int j = 0; j < n; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Compute all-pairs shortest paths
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != std::numeric_limits<int>::max() && dist[k][j] != std::numeric_limits<int>::max() && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print shortest distances
  
    cout << "\nShortest Distance from custom location to crystal :\n" << endl;
    for (int j = 0; j < n; j++) {
        if (dist[source][j] == std::numeric_limits<int>::max()) {

        }
        else {
            cout << dist[source][j] << " ";
        }
    }
    cout << endl;

    cout << "Shortest Distance from (0,0) to Crystal: " << dist[source][dest] << endl;

    // Free memory
    for (int i = 0; i < n; i++) {
        delete[] dist[i];
    }
    delete[] dist;
}
void printMST(int n, int** adjMat, int* parent) {
    
    cout << "\n-*-*-*-*-*-*-*-*-*-*-*-*-*-Minimum Spanning Tree Prim's -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n" << endl;
   
    int count = 0;
    for (int i = 0; i < n; i++) {
        cout << parent[i] << " - " << i << "\tWeight: " << adjMat[i][parent[i]] << endl;
        count += adjMat[i][parent[i]];
    }
    
    cout << "Total weight of MST Prim's: " << count << endl;
   
}

void prim(int n, int** adjMat) {
    // Initialize all keys to infinity and visited array to false
    int* key = new int[n];
    int i = 0;
    while (i < n) {
        key[i] = std::numeric_limits<int>::max();
        i++;
    }

    bool* visited = new bool[n] {false};
    int* parent = new int[n] {-1};
    int v = 0;
    while (v < n) {
        (adjMat[0][v] != std::numeric_limits<int>::max()) ? (key[v] = adjMat[0][v], parent[v] = 0) : 0;

        v++;
    }

    // Set the key of the first vertex to 0
    key[0] = 0;

    // Loop through all vertices
    int c = 0;
    while (c < n)
    {
        int u = -1;
        int j = 0;
        while (j < n)
        {
            (!visited[j] && (u == -1 || key[j] < key[u])) ? u = j : 0;

            j++;
        }

        // Add the vertex with the minimum key to the MST
        visited[u] = true;

        // Update the key values of all adjacent vertices
        int v = 0;
        while (v < n)
        {
            if (adjMat[u][v] != std::numeric_limits<int>::max() && !visited[v] && adjMat[u][v] < key[v])
            {
                key[v] = adjMat[u][v];
                parent[v] = u;
            }
            v++;
        }
        c++;
    }

    printMST(n, adjMat, parent);
}


struct Edge {
    int src, dest, weight;
    Edge& operator=(const Edge& other) {
        if (this != &other) {
            src = other.src;
            dest = other.dest;
            weight = other.weight;
        }
        return *this;
    }
    bool operator>(const Edge& other) {
        return weight > other.weight;
    }
    bool operator<(const Edge& other) {
        return weight < other.weight;
    }
};



// Find function to find the parent of a vertex in the union-find data structure
int find(int vertex, int*& parent) {
    if (parent[vertex] == vertex) {
        return vertex;
    }
    return find(parent[vertex], parent);
}

// Union function to merge two sets
void unionSets(int v1, int v2, int*& parent) {
    int parent1 = find(v1, parent);
    int parent2 = find(v2, parent);
    parent[parent1] = parent2;
}

// Kruskal's algorithm to find MST using adjacency matrix
void kruskal(int n, int** adjMatrix) {
    vector<Edge> edges;  // Vector to store all edges
    int* parent = new int[n] {-1};  // Vector to store the parent of each vertex
    for (int i = 0; i < n; i++) {
        parent[i] = i;  // Initialize parent of each vertex as itself
        for (int j = i + 1; j < n; j++) {
            if (adjMatrix[i][j] != 0) {  // If there is an edge between i and j
                edges.push_back({ i, j, adjMatrix[i][j] });  // Add the edge to the edges vector
            }
        }
    }
    edges.bubbleSort(); // Sort the edges by weight
    int mstWeight = 0;  // Total weight of the MST
    
    cout << "\n-*-*-*-*-*-*-*-*-*-*-*-*-*-Minimum Spanning Tree Kruskal's -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n" << endl;
    
 
    for (vectorNode<Edge>* curr = edges.begin(); curr <= edges.end(); curr = curr->next) {
        int parent1 = find(curr->data.src, parent);
        int parent2 = find(curr->data.dest, parent);
        if (parent1 != parent2) {  // If the two vertices belong to different sets
            cout << curr->data.src << " - " << curr->data.dest << "\tWeight: " << curr->data.weight << endl;
            unionSets(curr->data.src, curr->data.dest, parent);  // Merge the two sets
            mstWeight += curr->data.weight;
        }
    }
    
    cout << "Total weight of MST Kruskal's: " << mstWeight << endl;
    
}
