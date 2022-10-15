#include <CDS/LinkedHashMap>
#include <CDS/HashMap>
#include <CDS/HashSet>
#include <CDS/LinkedHashSet>
#include <CDS/Array>
#include <CDS/LinkedList>

int main () {

    std :: cout << cds :: linkedHashSetOf ( 3, 1, 2 ) << '\n';
    std :: cout << cds :: hashSetOf ( 3, 1, 2 ) << '\n';
    std :: cout << cds :: arrayOf ( 3, 1, 2 ) << '\n';
    std :: cout << cds :: linkedListOf ( 3, 1, 2 ) << '\n';
    std :: cout << cds :: listOf ( 3, 1, 2 ) << '\n';
    std :: cout << cds :: setOf ( 3, 1, 2 ) << '\n';
    std :: cout << cds :: mapOf ( cds :: mapEntryOf (3, 1), cds :: mapEntryOf (1, 1), cds :: mapEntryOf (2, 4) ) << '\n';
    std :: cout << cds :: hashMapOf ( cds :: mapEntryOf (3, 1), cds :: mapEntryOf (1, 1), cds :: mapEntryOf (2, 4) ) << '\n';
    std :: cout << cds :: linkedHashMapOf ( cds :: mapEntryOf (3, 1), cds :: mapEntryOf (1, 1), cds :: mapEntryOf (2, 4) ) << '\n';

    auto view = cds :: StringView ( "abcd" );
    std :: cout << view << '\n';

    return 0;
}