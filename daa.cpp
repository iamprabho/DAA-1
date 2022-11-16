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