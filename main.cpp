//#include <iostream>
//
//using namespace std;
//
//// max & min din vector
//
//void findMinMax ( int v[], int n, int & min, int & max ) {
//
//}
//
///// returnam ?
//
///// putem defini propriile tipuri
//
///**
// * 'Alias'
// */
//
//using intreg = int;
//
///**
// * 'Structura'
// */
//
//struct MinMax {
//    int min;
//    int max;
//};
//
//MinMax findMinMax ( int v[], int n ) {
//    MinMax rezultat;
//
//    rezultat.min = v[0];
//    rezultat.max = v[0];
//
//    for (int i = 1; i < n; ++i) {
//        if ( v[i] < rezultat.min ) {
//            rezultat.min = v[i];
//        }
//
//        if ( v[i] > rezultat.max ) {
//            rezultat.max = v[i];
//        }
//    }
//
//    return rezultat;
//}
//
//int main () {
//
//    /// int = tip de date
//    int x; /// x este un intreg
//    int y; /// y este un intreg
//    intreg z;
//
//    MinMax minMax;
//    minMax.min = 3;
//    minMax.max = 4;
//
//    int v[] = { 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1 };
//    int n = 11;
//
//    minMax = findMinMax ( v, n );
//
//    cout << minMax.min << " " << minMax.max << '\n';
//
//    return 0;
//}

#include <iostream>
//
//using namespace std;
//
///*
// * Sa se sorteze numerele dupa suma cifrelor
// */
//
//struct Element {
//    int numar;
//    int sumaCifrelor;
//};
//
//int main () {
//    Element numere [ 20 ];
//    int n;
//
//    cin >> n;
//    for (int i = 0; i < n; ++i) {
//        cin >> numere[i].numar;
//
//        int x = numere[i].numar;
//
//        numere[i].sumaCifrelor = 0;
//        while ( x > 0 ) {
//            numere[i].sumaCifrelor += x % 10;
//            x /= 10;
//        }
//    }
//
//    for ( int i = 0; i < n - 1; ++ i ) {
//        for ( int j = i + 1; j < n; ++ j ) {
//            if ( numere[i].sumaCifrelor > numere[j].sumaCifrelor ) {
//                Element aux = numere[i];
//                numere[i] = numere[j];
//                numere[j] = aux;
//            }
//        }
//    }
//
//    for (int i = 0; i < n; ++i) {
//        cout << numere[i].numar << ' ';
//    }
//
//}

//struct punct {
//    int x, y;
//};
//
//struct punct2 {
//    int x;
//    int y;
//} E; /// E este o variabila de tip punct2
///// punct2 E;
//
//punct A, B;
//punct2 C, D;
//
//struct { /// structura anonima. F are un tip de date, F are un tip de date fara nume ( anonim )
//    int x, y;
//} F;
//
//struct punct {
//    int x, y;
//};
//
//struct segment {
//    punct A, B;
//};
//
//segment S;
//
//
//int main () {
//    S.A.x = 3;
//    S.A.y = 3;
//
//    S.B.x = 6;
//    S.B.y = 7;
//}

struct punct {
    float x, y;
} A, B, C;

using namespace std;

struct elev
{
    char nume[20];
    int nota1;
    int nota2;
} e1,e2;

/**
 * a. e1=e2+1;
 * e1 = elev.       e2 + 1 ( elev + intreg ) ? invalid
 * e2 = elev
 *
 * b. e1.nume[2]=’x’;
 * e1 elev. e1.nume = sir de caractere ( vector de char ). e1.nume[2] = caracter
 * caracter = 'x' ( caracter ) valid
 *
 * c. e1=e2;
 * e1 = elev
 * e2 = elev
 * elev = elev valid
 *
 *
 * d. e1.nota1=e2.nota2+1;
 * e1.nota1 = int
 * e2.nota2 = int
 *
 * e2.nota2 + 1 = int + int = int
 * int = int valid
 */

int main () {
    A.x = 1;
    A.y = 5;

    B.x = 6;
    B.y = 2;

    C.x = (A.x + B.x) / 2;
    C.y = (A.y + B.y) / 2;

    cout << C.x << ' ' << C.y << '\n';
}

//Scrieţi definiţia corectă a unui tip de date necesar pentru a memora simultan, într-o singură
//variabilă de acest tip, următoarele caracteristici ale unui autoturism: marca (cuvânt de
//        maximum 20 caractere) şi anul fabricaţiei (număr natural format din exact 4 cifre), astfel
//        încât expresia C/C++ de mai jos să aibă ca valoare vechimea maşinii ale cărei caracteristici
//sunt memorate în variabila x.
//2008-x.anul_fabricatiei

struct masina {
    char marca[20];
    int anul_fabricatiei;
} x;

void f () {
    x.marca;
    masina * adr = & x;
    ( * adr ).marca;
    adr->marca;
}