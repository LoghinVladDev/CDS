#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
//ifstream fin ("minlex.in");
//ofstream fout ("minlex.out");
#define fin cin
#define fout cout
char s[100002],c,k,f[200002], minim[100001];
int i,counter,pos;
long long lg;


int main()
{
    fin >> s;
    lg = strlen(s);
    strcat (f, s);
    strcat (f, s);

    memset(minim, 'z', 100000);

    for ( i = 0; i < lg; ++ i ) {
        c = f[i + lg];
        f[i + lg] = 0;

        if ( strcmp ( f + i, minim ) < 0 ) {
            strcpy(minim, f + i);
            pos = i;
        }

        f[i + lg] = c;
    }

    fout << pos << '\n';
    return 0;
}
