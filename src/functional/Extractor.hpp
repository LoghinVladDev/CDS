//
// Created by loghin on 6/22/22.
//

#ifndef __CDS_EXTRACTOR_HPP__
#define __CDS_EXTRACTOR_HPP__

namespace cds {

    namespace utility {         // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __BaseType, typename __ExtractedType >                                  // NOLINT(bugprone-reserved-identifier)
                constexpr auto __extractHint ( __BaseType const & ) noexcept -> __ExtractedType const &;    // NOLINT(bugprone-reserved-identifier)

            }
        }

        template < typename __BaseType, typename __ExtractedType > // NOLINT(bugprone-reserved-identifier)
        using ExtractorFunction = decltype (
                & cds :: utility :: __hidden :: __impl :: __extractHint < __BaseType, __ExtractedType >
        );
    }

    template <
            typename                                                            __BaseType,          // NOLINT(bugprone-reserved-identifier)
            typename                                                            __ExtractedType,     // NOLINT(bugprone-reserved-identifier)
            cds :: utility :: ExtractorFunction < __BaseType, __ExtractedType > __extractor          // NOLINT(bugprone-reserved-identifier)
    > class FunctionExtractor {

    public:
        __CDS_NoDiscard constexpr auto operator () (
                __BaseType const & value
        ) const noexcept ( noexcept ( __extractor ( value ) ) ) -> __ExtractedType const & {

            return __extractor ( value );
        }
    };

}

#endif // __CDS_EXTRACTOR_HPP__
