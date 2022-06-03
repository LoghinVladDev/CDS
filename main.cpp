#include <CDS/experimental/Array>
#include <CDS/experimental/LinkedList>

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

#include <CDS/experimental/Tuple>

int main () {

    cds :: experimental :: Array < DefaultCopyMove > a;
    cds :: experimental :: Array < DefaultCopy > b;
    cds :: experimental :: Array < DefaultMove > c;
    cds :: experimental :: Array < CopyMove > d;
    cds :: experimental :: Array < Move > e;
    cds :: experimental :: Array < Copy > f;
    cds :: experimental :: Array < Default > g;
    cds :: experimental :: Array < None > h;

    cds :: experimental :: Array < DefaultCopyMove > const ac;
    cds :: experimental :: Array < DefaultCopy > const bc;
    cds :: experimental :: Array < DefaultMove > const cc;
    cds :: experimental :: Array < CopyMove > const dc;
    cds :: experimental :: Array < Move > const ec;
    cds :: experimental :: Array < Copy > const fc;
    cds :: experimental :: Array < Default > const gc;
    cds :: experimental :: Array < None > const hc;

    cds :: experimental :: LinkedList < DefaultCopyMove > la;
    cds :: experimental :: LinkedList < DefaultCopy > lb;
    cds :: experimental :: LinkedList < DefaultMove > lc;
    cds :: experimental :: LinkedList < CopyMove > ld;
    cds :: experimental :: LinkedList < Move > le;
    cds :: experimental :: LinkedList < Copy > lf;
    cds :: experimental :: LinkedList < Default > lg;
    cds :: experimental :: LinkedList < None > lh;

    cds :: experimental :: LinkedList < DefaultCopyMove > const lac;
    cds :: experimental :: LinkedList < DefaultCopy > const lbc;
    cds :: experimental :: LinkedList < DefaultMove > const lcc;
    cds :: experimental :: LinkedList < CopyMove > const ldc;
    cds :: experimental :: LinkedList < Move > const lec;
    cds :: experimental :: LinkedList < Copy > const lfc;
    cds :: experimental :: LinkedList < Default > const lgc;
    cds :: experimental :: LinkedList < None > const lhc;

    cds :: experimental :: Array < int > arr = { 5, 4, 3, 2, 1 };
    cds :: experimental :: Array < int > const arrc = { 1, 2, 3, 4, 5 };

    experimental :: Collection < int > & c2 = arr;

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

arrc.findLast ( [](int v){return true;} );
    std :: for_each ( arrc.begin(), arrc.end(), [] ( auto const & v ) { std :: cout << v << '\n'; } );
* arr.begin() = 3;
//    arr.insertBefore ( arr.begin(), 3 );

    std :: cout << arrc.sub < cds :: experimental :: Array > ( 1, 3 );
    std :: cout << arrc.sub < cds :: experimental :: Array < int > > ( 1, 3 ) << '\n';

    arr.sort();
    std :: cout << arr << '\n';
    arr.sort([](int a, int b){ return a > b; });
    std :: cout << arr << '\n';

    return 0;
}