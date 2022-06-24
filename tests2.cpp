#include <CDS/experimental/Collection>
#include <CDS/experimental/Array>
#include <CDS/experimental/LinkedList>
#include <CDS/experimental/OrderedSet>
#include <CDS/experimental/UnorderedSet>
#include <CDS/experimental/HashSet>
#include <CDS/experimental/HashMap>
#include <CDS/smartPointers/UniquePointer>
#include <chrono>

#include <random>
#include <fstream>

using namespace cds;
using namespace cds :: literals;
#include <unordered_set>
#include <unordered_map>

int main () {

    auto a = cds :: experimental :: arrayOf (
            cds :: makeUnique < int > ( 3 ),
            cds :: makeUnique < int > ( 2 ),
            cds :: makeUnique < int > ( 3 ),
            cds :: makeUnique < int > ( 4 )
    );

    std :: cout << a << '\n';

    auto a2 = std :: move ( a );

    std :: cout << a << '\n';
    std :: cout << a2 << '\n';

    return 0;
}