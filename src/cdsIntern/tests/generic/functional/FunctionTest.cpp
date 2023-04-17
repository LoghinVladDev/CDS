//
// Created by vlad.loghin on 17.04.23.
//

#include "FunctionTest.hpp"
#include <CDS/Function>

namespace {
    using cds::Function;
}

inline namespace ftg {
    bool malfunction = false;

    namespace v {
        void vNoParamClassic () { (void) malfunction; }
        void vOneParamCopyClassic (int x) { if (x != 1) { malfunction = true; } }
        void vOneParamRefClassic (int & x) { if (x != 1) {malfunction = true;} x = 0; if (x != 0) {malfunction = true;} }
        void vOneParamCRefClassic (int const & x) { if (x != 1) {malfunction = true;} }
        void vOneParamMRefClassic (int && x) { if (x != 1) {malfunction = true;} x = 0; }
        void vTwoParamsCopyClassic (int x, int y) { if (x != 1 || y != 2) {malfunction = true;} }
        void vTwoParamsCopyRef (int x, int & y) { if (x != 1 || y != 2) {malfunction = true;} y = 1; if (y != 1) {malfunction = true;} }
        void vTwoParamsRefRef (int & x, int & y) { if (x != 1 || y != 2) {malfunction = true;} x = 0; y = 1; if (x != 0 || y != 1) { malfunction = true; } }
        void vTwoParamsRefCref (int & x, int const & y) { if (x != 1 || y != 2) {malfunction = true;} x = 0; if (x != 0) {malfunction = true;} }
        void vTwoParamsCRefRef (int const & x, int & y) { if (x != 1 || y != 2) {malfunction = true;} y = 1; if (y != 1) {malfunction = true;} }

        auto vNoParamTrailing () -> void { (void) malfunction; }
        auto vOneParamRefTrailing (int & x) -> void { if (x != 1) {malfunction = true;} x = 0; if (x != 0) {malfunction = true;} }
    }

    template <typename I, typename F, typename = void>
    struct StaticAssertCheckDeclval : cds::meta::FalseType {};

    template <typename I, typename F>
    struct StaticAssertCheckDeclval <I, F, cds::meta::Void < decltype ( I (cds::meta::valueOf <F> ()) ) >> : cds::meta::TrueType {};
}

auto glob::FunctionTest::execute () noexcept -> bool {

    bool allOk = true;
    this->executeSubtest (this->versionedString ("FunctionTestGroup-FTG-globalFunction-vOneParam-%v : FTG-00100-%v"), [& allOk, this](){
        cds::Function <void()> const vNoParam = & v::vNoParamClassic;

        cds::Function <void(int)> const vOneParamCopy = & v::vOneParamCopyClassic;
        cds::Function <void(int &)> const vOneParamCopyMalfRef = & v::vOneParamCopyClassic;
        cds::Function <void(int const &)> const vOneParamCopyMalfCref = & v::vOneParamCopyClassic;
        cds::Function <void(int &&)> const vOneParamCopyMalfMRef = & v::vOneParamCopyClassic;

        cds::Function <void(int &)> const vOneParamRef = & v::vOneParamRefClassic;

        cds::Function <void(int)> const vOneParamCrefMalfCopy = & v::vOneParamCRefClassic;
        cds::Function <void(int &)> const vOneParamCrefMalfRef = & v::vOneParamCRefClassic;
        cds::Function <void(int const &)> const vOneParamCref = & v::vOneParamCRefClassic;
        cds::Function <void(int &&)> const vOneParamCrefMalfMRef = & v::vOneParamCRefClassic;

        cds::Function <void(int)> const vOneParamMrefMalfCopy = & v::vOneParamMRefClassic;
        cds::Function <void(int &&)> const vOneParamMref = & v::vOneParamMRefClassic;

        int x;
        int y;
        auto r = [& x, & y] {x = 1; y = 2;};

        vNoParam ();
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00101-vNoParam-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00101-vNoParam-%v' OK"));

        r ();
        vOneParamCopy (1);
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00102-vOneParamCopy-prvalue-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00102-vOneParamCopy-prvalue-%v' OK"));

        vOneParamCopy (x);
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00103-vOneParamCopy-lvalueCopy-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00103-vOneParamCopy-lvalueCopy-%v' OK"));

        r ();
        vOneParamCopyMalfRef (x);
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00104-vOneParamCopyMalfRef-lvalue-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00104-vOneParamCopyMalfRef-lvalue-%v' OK"));

        r ();
        vOneParamCopyMalfCref (1);
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00105-vOneParamCopyMalfCref-prvalue-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00105-vOneParamCopyMalfCref-prvalue-%v' OK"));

        vOneParamCopyMalfCref (x);
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00106-vOneParamCopyMalfCref-lvalue-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00106-vOneParamCopyMalfCref-lvalue-%v' OK"));

        r ();
        vOneParamCopyMalfMRef (1);
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00107-vOneParamCopyMalfMRef-prvalue-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00107-vOneParamCopyMalfMRef-prvalue-%v' OK"));

        vOneParamCopyMalfMRef (cds::exchange(x, 1));
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00108-vOneParamCopyMalfMRef-lvalueExplicitDecay-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00108-vOneParamCopyMalfMRef-lvalueExplicitDecay-%v' OK"));

        r ();
        vOneParamRef (x);
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00109-vOneParamRef-lvalueExplicitDecay-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00109-vOneParamRef-lvalueExplicitDecay-%v' OK"));

        r ();
        vOneParamCrefMalfCopy (1);
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00110-vOneParamCrefMalfCopy-prvalueRefBind-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00110-vOneParamCrefMalfCopy-prvalueRefBind-%v' OK"));

        vOneParamCrefMalfCopy (x);
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00111-vOneParamCrefMalfCopy-lvalueRefBind-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00111-vOneParamCrefMalfCopy-lvalueRefBind-%v' OK"));

        r ();
        vOneParamCrefMalfRef (x);
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00112-vOneParamCrefMalfRef-lvalueRefDecay-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00112-vOneParamCrefMalfRef-lvalueRefDecay-%v' OK"));

        r ();
        vOneParamCref (1);
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00113-vOneParamCref-prvalue-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00113-vOneParamCref-prvalue-%v' OK"));

        vOneParamCref (x);
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00114-vOneParamCref-lvalue-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00114-vOneParamCref-lvalue-%v' OK"));

        r ();
        vOneParamCrefMalfMRef (1);
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00115-vOneParamCrefMalfMRef-prvalue-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00115-vOneParamCrefMalfMRef-prvalue-%v' OK"));

        vOneParamCrefMalfMRef (cds::exchange (x, 1));
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00116-vOneParamCrefMalfMRef-lvalueExchangeDecay-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00116-vOneParamCrefMalfMRef-lvalueExchangeDecay-%v' OK"));

        r ();
        vOneParamMrefMalfCopy (1);
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00117-vOneParamMrefMalfCopy-prvalue-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00117-vOneParamMrefMalfCopy-prvalue-%v' OK"));

        vOneParamMrefMalfCopy (cds::exchange (x, 1));
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00118-vOneParamMrefMalfCopy-lvalueCopy-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00118-vOneParamMrefMalfCopy-lvalueCopy-%v' OK"));

        r ();
        vOneParamMref (1);
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00117-vOneParamMref-prvalueToXValue-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00117-vOneParamMref-prvalueToXValue-%v' OK"));

        vOneParamMref (cds::exchange (x, 1));
        if (malfunction) {
            this->logError (this->versionedString("'FTC-00118-vOneParamMref-lvalueToXValue-%v' failed"));
        }
        this->logOK (this->versionedString("'FTC-00118-vOneParamMref-lvalueToXValue-%v' OK"));
    });

    return allOk;
}
