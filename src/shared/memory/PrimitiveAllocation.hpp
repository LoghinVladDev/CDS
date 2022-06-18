//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_PRIMITIVE_ALLOCATION_HPP__
#define __CDS_PRIMITIVE_ALLOCATION_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __allocation { // NOLINT(bugprone-reserved-identifier)

                template < typename __Type, Size __primitiveSize = sizeof ( __Type ) > // NOLINT(bugprone-reserved-identifier)
                inline auto __allocPrimitiveArray ( // NOLINT(bugprone-reserved-identifier)
                        Size capacity
                ) noexcept -> __Type * {

                    return reinterpret_cast < __Type * > ( malloc ( capacity * __primitiveSize ) );
                }


                template < typename __Type, Size __primitiveSize = sizeof ( __Type ) > // NOLINT(bugprone-reserved-identifier)
                inline auto __reallocPrimitiveArray ( // NOLINT(bugprone-reserved-identifier)
                        __Type  * pBuffer,
                        Size      newCapacity
                ) noexcept -> __Type * {

                    return reinterpret_cast < __Type * > (
                            realloc ( pBuffer, newCapacity * __primitiveSize )
                    );
                }


                template < typename __Type > // NOLINT(bugprone-reserved-identifier)
                inline auto __freePrimitiveArray ( // NOLINT(bugprone-reserved-identifier)
                        __Type * pBuffer
                ) noexcept -> void {

                    free ( pBuffer );
                }

            }
        }
    }
}

#endif // __CDS_PRIMITIVE_ALLOCATION_HPP__
