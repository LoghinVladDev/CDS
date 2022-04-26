#include <CDS/experimental/Array>

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

#include <vector>

int main () {

    cds :: experimental :: Array < DefaultCopyMove > a;
    cds :: experimental :: Array < DefaultCopy > b;
    cds :: experimental :: Array < DefaultMove > c;
    cds :: experimental :: Array < CopyMove > d;
    cds :: experimental :: Array < Move > e;
    cds :: experimental :: Array < Copy > f;
    cds :: experimental :: Array < Default > g;
    cds :: experimental :: Array < None > h;

    std :: vector < DefaultCopyMove > a1;
    std :: vector < DefaultCopy > b1;
    std :: vector < DefaultMove > c1;
    std :: vector < CopyMove > d1;
    std :: vector < Move > e1;
    std :: vector < Copy > f1;
    std :: vector < Default > g1;
    std :: vector < None > h1;
    std :: vector < None > h2 (std::move(h1));
    return 0;
}