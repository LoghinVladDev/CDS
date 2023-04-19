#include <CDS/Array>
#include <CDS/LinkedList>
#include <CDS/HashSet>
#include <CDS/LinkedHashSet>
#include <CDS/HashMap>
#include <CDS/LinkedHashMap>

using namespace cds;

class DefaultCopyMove : public cds :: Object {
public:
    DefaultCopyMove () noexcept = default;
    DefaultCopyMove ( DefaultCopyMove const & ) noexcept = default;
    DefaultCopyMove ( DefaultCopyMove && ) noexcept = default;

    auto toString () const noexcept -> String override {
        return "Default, Copy, Move";
    }
};

class DefaultCopy : public cds :: Object {
public:
    DefaultCopy () noexcept = default;
    DefaultCopy ( DefaultCopy const & ) noexcept = default;
    DefaultCopy ( DefaultCopy && ) noexcept = delete;

    auto toString () const noexcept -> String override {
        return "DefaultCopy";
    }
};

class DefaultMove : public cds :: Object {
public:
    DefaultMove () noexcept = default;
    DefaultMove ( DefaultMove const & ) noexcept = delete;
    DefaultMove ( DefaultMove && ) noexcept = default;

    auto toString () const noexcept -> String override {
        return "DefaultMove";
    }
};

class CopyMove : public cds :: Object {
public:
    CopyMove () noexcept = delete;
    CopyMove ( CopyMove const & ) noexcept = default;
    CopyMove ( CopyMove && ) noexcept = default;

    auto toString () const noexcept -> String override {
        return "CopyMove";
    }
};

class Move : public cds :: Object {
public:
    Move () noexcept = delete;
    Move ( Move const & ) noexcept = delete;
    Move ( Move && ) noexcept = default;

    auto toString () const noexcept -> String override {
        return "Move";
    }
};

class Copy : public cds :: Object {
public:
    Copy () noexcept = delete;
    Copy ( Copy const & ) noexcept = default;
    Copy ( Copy && ) noexcept = delete;

    auto toString () const noexcept -> String override {
        return "Copy";
    }
};

class Default : public cds :: Object {
public:
    Default () noexcept = default;
    Default ( Default const & ) noexcept = delete;
    Default ( Default && ) noexcept = delete;

    auto toString () const noexcept -> String override {
        return "Default";
    }
};

class None : public cds :: Object {
public:
    None () noexcept = delete;
    None ( None const & ) noexcept = delete;
    None ( None && ) noexcept = delete;

    auto toString () const noexcept -> String override {
        return "None";
    }
};

#include <CDS/Tuple>

int main () {

    cds :: Array < DefaultCopyMove > a;
    cds :: Array < DefaultCopy > b;
    cds :: Array < DefaultMove > c;
    cds :: Array < CopyMove > d;
    cds :: Array < Move > e;
    cds :: Array < Copy > f;
    cds :: Array < Default > g;
    cds :: Array < None > h;

    cds :: Array < DefaultCopyMove > const ac;
    cds :: Array < DefaultCopy > const bc;
    cds :: Array < DefaultMove > const cc;
    cds :: Array < CopyMove > const dc;
    cds :: Array < Move > const ec;
    cds :: Array < Copy > const fc;
    cds :: Array < Default > const gc;
    cds :: Array < None > const hc;

    cds :: LinkedList < DefaultCopyMove > la;
    cds :: LinkedList < DefaultCopy > lb;
    cds :: LinkedList < DefaultMove > lc;
    cds :: LinkedList < CopyMove > ld;
    cds :: LinkedList < Move > le;
    cds :: LinkedList < Copy > lf;
    cds :: LinkedList < Default > lg;
    cds :: LinkedList < None > lh;

    cds :: LinkedList < DefaultCopyMove > const lac;
    cds :: LinkedList < DefaultCopy > const lbc;
    cds :: LinkedList < DefaultMove > const lcc;
    cds :: LinkedList < CopyMove > const ldc;
    cds :: LinkedList < Move > const lec;
    cds :: LinkedList < Copy > const lfc;
    cds :: LinkedList < Default > const lgc;
    cds :: LinkedList < None > const lhc;

    cds :: HashSet < DefaultCopyMove > hsla;
    cds :: HashSet < DefaultCopy > hslb;
    cds :: HashSet < DefaultMove > hslc;
    cds :: HashSet < CopyMove > hsld;
    cds :: HashSet < Move > hsle;
    cds :: HashSet < Copy > hslf;
    cds :: HashSet < Default > hslg;
    cds :: HashSet < None > hslh;

    cds :: HashSet < DefaultCopyMove > const hslac;
    cds :: HashSet < DefaultCopy > const hslbc;
    cds :: HashSet < DefaultMove > const hslcc;
    cds :: HashSet < CopyMove > const hsldc;
    cds :: HashSet < Move > const hslec;
    cds :: HashSet < Copy > const hslfc;
    cds :: HashSet < Default > const hslgc;
    cds :: HashSet < None > const hslhc;

    cds :: HashMap < DefaultCopyMove, DefaultCopyMove > hmla;
    cds :: HashMap < DefaultCopy, DefaultCopy > hmlb;
    cds :: HashMap < DefaultMove, DefaultMove > hmlc;
    cds :: HashMap < CopyMove, CopyMove > hmld;
    cds :: HashMap < Move, Move > hmle;
    cds :: HashMap < Copy, Copy > hmlf;
    cds :: HashMap < Default, Default > hmlg;
    cds :: HashMap < None, None > hmlh;

    cds :: HashMap < DefaultCopyMove, DefaultCopyMove > const hmlac;
    cds :: HashMap < DefaultCopy, DefaultCopy > const hmlbc;
    cds :: HashMap < DefaultMove, DefaultMove > const hmlcc;
    cds :: HashMap < CopyMove, CopyMove > const hmldc;
    cds :: HashMap < Move, Move > const hmlec;
    cds :: HashMap < Copy, Copy > const hmlfc;
    cds :: HashMap < Default, Default > const hmlgc;
    cds :: HashMap < None, None > const hmlhc;

    cds :: LinkedHashSet < DefaultCopyMove > lhsla;
    cds :: LinkedHashSet < DefaultCopy > lhslb;
    cds :: LinkedHashSet < DefaultMove > lhslc;
    cds :: LinkedHashSet < CopyMove > lhsld;
    cds :: LinkedHashSet < Move > lhsle;
    cds :: LinkedHashSet < Copy > lhslf;
    cds :: LinkedHashSet < Default > lhslg;
    cds :: LinkedHashSet < None > lhslh;

    cds :: LinkedHashSet < DefaultCopyMove > const lhslac;
    cds :: LinkedHashSet < DefaultCopy > const lhslbc;
    cds :: LinkedHashSet < DefaultMove > const lhslcc;
    cds :: LinkedHashSet < CopyMove > const lhsldc;
    cds :: LinkedHashSet < Move > const lhslec;
    cds :: LinkedHashSet < Copy > const lhslfc;
    cds :: LinkedHashSet < Default > const lhslgc;
    cds :: LinkedHashSet < None > const lhslhc;

    cds :: LinkedHashMap < DefaultCopyMove, DefaultCopyMove > lhmla;
    cds :: LinkedHashMap < DefaultCopy, DefaultCopy > lhmlb;
    cds :: LinkedHashMap < DefaultMove, DefaultMove > lhmlc;
    cds :: LinkedHashMap < CopyMove, CopyMove > lhmld;
    cds :: LinkedHashMap < Move, Move > lhmle;
    cds :: LinkedHashMap < Copy, Copy > lhmlf;
    cds :: LinkedHashMap < Default, Default > lhmlg;
    cds :: LinkedHashMap < None, None > lhmlh;

    cds :: LinkedHashMap < DefaultCopyMove, DefaultCopyMove > const lhmlac;
    cds :: LinkedHashMap < DefaultCopy, DefaultCopy > const lhmlbc;
    cds :: LinkedHashMap < DefaultMove, DefaultMove > const lhmlcc;
    cds :: LinkedHashMap < CopyMove, CopyMove > const lhmldc;
    cds :: LinkedHashMap < Move, Move > const lhmlec;
    cds :: LinkedHashMap < Copy, Copy > const lhmlfc;
    cds :: LinkedHashMap < Default, Default > const lhmlgc;
    cds :: LinkedHashMap < None, None > const lhmlhc;

    cds :: Array < int > arr = { 5, 4, 3, 2, 1 };
    cds :: Array < int > const arrc = { 1, 2, 3, 4, 5 };

    Collection < int > & c2 = arr;

//    arr.forEach ( [] ( int v ) { v = 3; } );
//    arr.forEach ( [] ( int & v ) { v = 3; } );
//    arr.forEach ( [] ( int const & v ) { (void)v; } );
//    arrc.forEach ( [] ( int v ) { v = 3; } );
////    arrc.forEach ( [] ( int & v ) { /*v = 3;*/ v; } );
//    arrc.forEach ( [] ( int const & v ) { (void)v; } );
//
//    arr.forEach ( [] ( auto v ) { v = 3; } );
//    arr.forEach ( [] ( auto & v ) { v = 3; } );
//    arr.forEach ( [] ( auto const & v ) { (void)v; } );
//    arrc.forEach ( [] ( auto v ) { v = 3; } );
//    arrc.forEach ( [] ( auto & v ) { /*v = 3;*/ (void)v; } );
//    arrc.forEach ( [] ( auto const & v ) { (void)v; } );

    (void)arrc.findLastThat ( [](int v){return true;} );
    std :: for_each ( arrc.begin(), arrc.end(), [] ( auto const & v ) { std :: cout << v << '\n'; } );
    * arr.begin() = 3;
//    arr.insertBefore ( arr.begin(), 3 );
    std :: cout << arrc.sub < cds :: Array > ( 1, 3 );
    std :: cout << arrc.sub < cds :: Array < int > > ( 1, 3 ) << '\n';

    arr.sort();
    std :: cout << arr << '\n';
    arr.sort([](int a, int b){ return a > b; });
    std :: cout << arr << '\n';

    return 0;
}