// 1A FRACTIONAL KNAPSACK WITH GREEDY METHOD
#include <iostream>
#include <algorithm>

using namespace std;

struct Item
{
    int value, weight;

    Item(int value, int weight)
    {
        this->value = value;
        this->weight = weight;
    }
};

bool cmp(struct Item a, struct Item b)
{
    double r1 = (double)a.value / (double)a.weight;
    double r2 = (double)b.value / (double)b.weight;

    return r1 > r2;
}

double fractionalKnapsack(int W, struct Item arr[], int N)
{

    sort(arr, arr + N, cmp);
    double finalvalue = 0.0;

    for (int i = 0; i < N; i++)
    {
        if (arr[i].weight <= W)
        {
            W -= arr[i].weight;
            finalvalue += arr[i].value;
        }
        else
        {
            finalvalue += arr[i].value * ((double)W / (double)arr[i].weight);
        }
    }

    return finalvalue;
}

int main()
{
    int W = 50;
    struct Item arr[] = {{20, 10}, {40, 20}, {30, 20}, {50, 20}};

    int N = sizeof(arr) / sizeof(arr[0]);

    cout << fractionalKnapsack(W, arr, N);

    return 0;
}

// 1B 0 1 KNAPSACK WITH DYNAMIC PROGRAMMING
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int max(int a, int b) { return a > b ? a : b; };

// Returns the maximum value that
// can be put in a knapsack of capacity W
int knapsack(int W, int wt[], int val[], int n)
{
    int i, w;
    vector<vector<int>> K(n + 1, vector<int>(W + 1));

    // Build table K[][] in bottom up manner
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] > w)
                K[i][w] = K[i - 1][w];

            else
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
        }
    }
    return K[n][W];
}

int main()
{
    int W = 50;
    int w[] = {20, 10, 30};
    int v[] = {50, 20, 40};

    int N = sizeof(w) / sizeof(w[0]);

    cout << knapsack(W, w, v, N);
    return 0;
}

// 2 BELLMAN FORD WITH DYNAMIC PROGRAMMING
#include <iostream>
#include <algorithm>

using namespace std;

struct Graph
{
    int source, destination, weight;
};

void printOutput(int dist[], int v)
{
    cout << "Vertex"
         << "\t"
         << "Distance from source vertex \n";
    for (int i = 0; i < v; i++)
    {
        cout << i << "\t" << dist[i] << "\n";
    }
}

void bellmanFord(Graph g[], int sourceV, int V, int E)
{
    int dist[V];
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
    }

    dist[sourceV] = 0;

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u, v, w;

            u = g[j].source;
            v = g[j].destination;
            w = g[j].weight;

            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
            }
        }
    }
    for (int i = 0; i < E; i++)
    {
        int u, v, w;

        u = g[i].source;
        v = g[i].destination;
        w = g[i].weight;

        if (dist[u] + w < dist[v])
        {
            cout << "Negative cycle exist in the weighted graph \n";
        }
    }
    printOutput(dist, V);
    return;
}

int main()
{
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    Graph g[E];

    for (int i = 0; i < E; i++)
    {
        int S, D, W;
        cout << "Enter source, destination and weight: ";
        cin >> S >> D >> W;

        g[i].source = S;
        g[i].destination = D;
        g[i].weight = W;
    }

    bellmanFord(g, 0, V, E);

    return 0;
}

// 3 N-QUEEN WITH RECURSION
#include <iostream>
#include <algorithm>
#define N 4

using namespace std;

void printSolution(int board[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << " " << board[i][j] << " ";
        }
        cout << "\n";
    }
}

// if queen is safe to place at board[row][col] on left
bool isSafe(int board[N][N], int row, int col)
{
    int i, j;
    // left side
    for (i = 0; i < col; i++)
    {
        if (board[row][i])
        {
            return false;
        }
    }
    // upper left diagonal
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j])
        {
            return false;
        }
    }

    // lower left diagonal
    for (i = row, j = col; j >= 0, i < N; i++, j--)
    {
        if (board[i][j])
        {
            return false;
        }
    }
    return true;
}

bool solveNQueen(int board[N][N], int col)
{

    // base case
    if (col >= N)
    {
        return true;
    }
    // if queen can be place at board[i][col]
    for (int i = 0; i < N; i++)
    {
        if (isSafe(board, i, col))
        {
            board[i][col] = 1;

            if (solveNQueen(board, col + 1))
                return true;
            board[i][col] = 0;
        }
    }
    return false;
}

int main()
{
    int board[N][N] = {{0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0}};

    if (solveNQueen(board, 0) == false)
    {
        cout << "No solution exist";
        return 0;
    }

    printSolution(board);
    return 0;
}

// 5 TRAVELLING SALESMAN BRANCH AND BOUND
// C++ program to solve Traveling Salesman Problem
// using Branch and Bound.
#include <bits/stdc++.h>
using namespace std;
const int N = 4;

// final_path[] stores the final solution ie, the
// path of the salesman.
int final_path[N + 1];

// visited[] keeps track of the already visited nodes
// in a particular path
bool visited[N];

// Stores the final minimum weight of shortest tour.
int final_res = INT_MAX;

// Function to copy temporary solution to
// the final solution
void copyToFinal(int curr_path[])
{
    for (int i = 0; i < N; i++)
        final_path[i] = curr_path[i];
    final_path[N] = curr_path[0];
}

// Function to find the minimum edge cost
// having an end at the vertex i
int firstMin(int adj[N][N], int i)
{
    int min = INT_MAX;
    for (int k = 0; k < N; k++)
        if (adj[i][k] < min && i != k)
            min = adj[i][k];
    return min;
}

// function to find the second minimum edge cost
// having an end at the vertex i
int secondMin(int adj[N][N], int i)
{
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < N; j++)
    {
        if (i == j)
            continue;

        if (adj[i][j] <= first)
        {
            second = first;
            first = adj[i][j];
        }
        else if (adj[i][j] <= second &&
                 adj[i][j] != first)
            second = adj[i][j];
    }
    return second;
}

// function that takes as arguments:
// curr_bound -> lower bound of the root node
// curr_weight-> stores the weight of the path so far
// level-> current level while moving in the search
//		 space tree
// curr_path[] -> where the solution is being stored which
//			 would later be copied to final_path[]
void TSPRec(int adj[N][N], int curr_bound, int curr_weight,
            int level, int curr_path[])
{
    // base case is when we have reached level N which
    // means we have covered all the nodes once
    if (level == N)
    {
        // check if there is an edge from last vertex in
        // path back to the first vertex
        if (adj[curr_path[level - 1]][curr_path[0]] != 0)
        {
            // curr_res has the total weight of the
            // solution we got
            int curr_res = curr_weight +
                           adj[curr_path[level - 1]][curr_path[0]];

            // Update final result and final path if
            // current result is better.
            if (curr_res < final_res)
            {
                copyToFinal(curr_path);
                final_res = curr_res;
            }
        }
        return;
    }

    // for any other level iterate for all vertices to
    // build the search space tree recursively
    for (int i = 0; i < N; i++)
    {
        // Consider next vertex if it is not same (diagonal
        // entry in adjacency matrix and not visited
        // already)
        if (adj[curr_path[level - 1]][i] != 0 &&
            visited[i] == false)
        {
            int temp = curr_bound;
            curr_weight += adj[curr_path[level - 1]][i];

            // different computation of curr_bound for
            // level 2 from the other levels
            if (level == 1)
                curr_bound -= ((firstMin(adj, curr_path[level - 1]) +
                                firstMin(adj, i)) /
                               2);
            else
                curr_bound -= ((secondMin(adj, curr_path[level - 1]) +
                                firstMin(adj, i)) /
                               2);

            // curr_bound + curr_weight is the actual lower bound
            // for the node that we have arrived on
            // If current lower bound < final_res, we need to explore
            // the node further
            if (curr_bound + curr_weight < final_res)
            {
                curr_path[level] = i;
                visited[i] = true;

                // call TSPRec for the next level
                TSPRec(adj, curr_bound, curr_weight, level + 1,
                       curr_path);
            }

            // Else we have to prune the node by resetting
            // all changes to curr_weight and curr_bound
            curr_weight -= adj[curr_path[level - 1]][i];
            curr_bound = temp;

            // Also reset the visited array
            memset(visited, false, sizeof(visited));
            for (int j = 0; j <= level - 1; j++)
                visited[curr_path[j]] = true;
        }
    }
}

// This function sets up final_path[]
void TSP(int adj[N][N])
{
    int curr_path[N + 1];

    // Calculate initial lower bound for the root node
    // using the formula 1/2 * (sum of first min +
    // second min) for all edges.
    // Also initialize the curr_path and visited array
    int curr_bound = 0;
    memset(curr_path, -1, sizeof(curr_path));
    memset(visited, 0, sizeof(curr_path));

    // Compute initial bound
    for (int i = 0; i < N; i++)
        curr_bound += (firstMin(adj, i) +
                       secondMin(adj, i));

    // Rounding off the lower bound to an integer
    curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;

    // We start at vertex 1 so the first vertex
    // in curr_path[] is 0
    visited[0] = true;
    curr_path[0] = 0;

    // Call to TSPRec for curr_weight equal to
    // 0 and level 1
    TSPRec(adj, curr_bound, 0, 1, curr_path);
}

// Driver code
int main()
{
    // Adjacency matrix for the given graph
    int adj[N][N] = {{0, 10, 15, 20},
                     {10, 0, 35, 25},
                     {15, 35, 0, 30},
                     {20, 25, 30, 0}};

    TSP(adj);

    printf("Minimum cost : %d\n", final_res);
    printf("Path Taken : ");
    for (int i = 0; i <= N; i++)
        printf("%d ", final_path[i]);

    return 0;
}
