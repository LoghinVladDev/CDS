#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <vector>
using namespace std;
ifstream fin ("vacanta2020.in");
ofstream fout ("vacanta2020.out");
int n,m,i,j,c,fr[35002],ticketsNo;
int maxValue = 0x7FFFFFFF,nodeHasEdgeWith1[35002];
long long dist[35002];

struct graphEdge {
    int node, cost;
};
list <graphEdge> Mat[35001];

struct pathEdge {
    int from = -1, to = -1, cost = -1;
};
vector <pathEdge> Edges[35001];

int edgeCost (int node, int val) {
    for (auto & i : Mat[node])
        if (i.node == val)
            return i.cost;
    return 0;
}

void copyPrevEdges (int fromNode, int toNode) {
    Edges[toNode].clear();
    for (auto & i : Edges[fromNode])
        Edges[toNode].push_back(i);
}

void dijkstra (int finalNode) {
    int cost = edgeCost(1,finalNode);
    pathEdge e;
    if (cost) {
        dist[finalNode] = 0;
        nodeHasEdgeWith1[finalNode] = 1;
        e.from = 1;
        e.to = finalNode;
        e.cost = cost;
        Edges[finalNode].push_back(e);
        return;
    }
    int i;
    i = 1;
    while (i <= n) {
        int min = maxValue;
        int node = -1;
        for (j = 1;j <= n;j++)
            if (dist[j] < min && ! fr[j]) {
                min = dist[j];
                node = j;
            }
        if (node == -1) {
            i++;
            continue;
        }
        if (node == finalNode)
            return;
        fr[node] = 1;
        for (j = 1;j <= n;j++) {
            cost = edgeCost(node,j);
            if (dist[node] + cost < dist[j] && cost) {
                if (nodeHasEdgeWith1[node])
                    dist[node] = edgeCost(node,1);
                dist[j] = dist[node] + cost;
                copyPrevEdges(node, j);
                e.from = node;
                e.to = j;
                e.cost = cost;
                Edges[j].push_back(e);
            }
        }
        i++;
    }
}

int main() {
    fin >> n >> m >> ticketsNo;
    while (m--) {
        fin >> i >> j >> c;
        graphEdge e = {j,c};
        Mat[i].push_back(e);
        e.node = i;
        Mat[j].push_back(e);
    }
    for (int i = 2;i <= n;i++)
        dist[i] = maxValue;
    for (i = 2;i <= n;i++) {
        dijkstra(i);
        sort (Edges[i].begin(),Edges[i].end(), [](pathEdge a, pathEdge b) { return a.cost > b.cost; });
    }
    for (i = 2;i <= n;i++)
        if (! edgeCost(1,i))
            for (j = 1;j <= ticketsNo;j++)
                dist[i] -= Edges[i][j - 1].cost;
    for (i = 1;i <= n;i++) {
        if (edgeCost(1,i))
            dist[i] = 0;
        fout << dist[i] << ' ';
    }
    return 0;
}