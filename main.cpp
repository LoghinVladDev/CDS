#include <CDS/experimental/JSON>

using namespace cds;

int main () {

    json::JsonObject json;

    for ( auto it = json.begin(); it != json.end(); ++ it ) {
        auto const & e = it.operator*();
        decltype ( it.operator*() ) e2;
    }

    for ( auto const & e : json ) {

    }

}