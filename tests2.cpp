#include <iostream>
#include <fstream>
using namespace std;
ifstream fin ("cladire5.in");
ofstream fout ("cladire5.out");
int n,mat[101][101],dist[101],i,j,p,fr[101],c;
int maxValue = 0x7FFFFFFF;

int main () {
    fin >> n >> p;
    while (fin >> i >> j >> c)
        mat[i][j] = c;
    for (i = 1;i <= n;i++)
        dist[i] = maxValue;
    dist[p] = 0;
    i = 1;
    while (i <= n) {
        int min = maxValue;
        int node = -1;
        for (j = 1;j <= n;j++)
            if (dist[j] < min && ! fr[j] ) {
                min = dist[j];
                node = j;
            }

        if ( node == -1 ) {
            i ++;
            continue;
        }

        fr[node] = 1;
        for (j = 1;j <= n;j++)
            if (mat[node][j] + dist[node] < dist[j] && mat[node][j])
                dist[j] = mat[node][j] + dist[node];
        i++;
    }
    for (i = 1;i <= n;i++)
        if ( dist[i] != maxValue )
            std::cout << dist[i] << ' ';
        else
            std::cout << -1 << ' ';
    return 0;
}