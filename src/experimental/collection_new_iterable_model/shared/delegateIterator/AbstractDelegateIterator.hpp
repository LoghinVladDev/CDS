//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ABSTRACT_DELEGATE_ITERATOR_HPP__
#define __CDS_SHARED_ABSTRACT_DELEGATE_ITERATOR_HPP__

#include "IteratorAdvanceDirection.hpp"

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                using __GenericIterator = void const *; // NOLINT(bugprone-reserved-identifier)


                template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
                class __AbstractDelegateIterator {      // NOLINT(bugprone-reserved-identifier)

                protected:
                    constexpr __AbstractDelegateIterator() noexcept;

                public:
                    __CDS_cpplang_ConstexprDestructor virtual ~__AbstractDelegateIterator() noexcept;

                public:
                    __CDS_cpplang_ConstexprPureAbstract virtual auto advance (
                            __IteratorAdvanceDirection direction
                    ) noexcept -> void = 0;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto equals (
                            __AbstractDelegateIterator const & iterator
                    ) const noexcept -> bool = 0;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto valid () const noexcept -> bool = 0;

                public:
                    __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto iterator () const noexcept -> __GenericIterator;

                public:
                    __CDS_NoDiscard virtual auto copy () const noexcept -> __AbstractDelegateIterator * = 0;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto value () const noexcept -> __ElementType & = 0;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_ABSTRACT_DELEGATE_ITERATOR_HPP__
