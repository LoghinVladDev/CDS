//
// Created by loghin on 22/09/2021.
//

#ifndef CDS_UTILITY_HPP
#define CDS_UTILITY_HPP

#include <type_traits>
#include "../prepro.h"
#include <CDS/memory/Allocation>
#include <CDS/Conversion>
#include <CDS/Limits>
#include <CDS/meta/TypeTraits>

namespace cds {

    template < typename T, typename SmartPointerType >
    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto copy ( T const & object ) noexcept -> SmartPointerType {
        return SmartPointerType ( copy ( object ) );
    }

    template < typename T > 
    __CDS_NoDiscard __CDS_MaybeUnused constexpr auto compare ( T const & left, T const & right ) noexcept -> bool {
        return meta :: equals ( left, right );
    } 

    template < typename T > 
    __CDS_MaybeUnused constexpr auto streamPrint ( std :: ostream & out, T const & object ) noexcept -> std :: ostream & {
        return meta :: print ( out, object );
    }

    template < typename T, typename = meta :: EnableIf < meta :: isCopyConstructible < T > () > >
    __CDS_NoDiscard __CDS_OptimalInline auto copy ( T const & obj ) noexcept -> T * {
        return Memory :: instance().create < T > ( obj );
    }

    template < typename T, meta :: EnableIf < meta :: isPrintable < T > () > = 0 >
    __CDS_OptimalInline auto println ( T const & obj ) noexcept -> std :: ostream & {
        return std :: cout << obj << '\n';
    }

}

#include "../shared/impl/arithmetic.hpp"
#include "../shared/impl/generalPredicates.hpp"


#endif //CDS_UTILITY_HPP
