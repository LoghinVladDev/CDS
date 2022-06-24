//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_PRIMITIVE_ALLOCATION_HPP__
#define __CDS_PRIMITIVE_ALLOCATION_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __allocation { // NOLINT(bugprone-reserved-identifier)

                template < typename __Type, Size __size = sizeof ( __Type ) > // NOLINT(bugprone-reserved-identifier)
                struct __RawContainer { // NOLINT(bugprone-reserved-identifier)

                    Byte _data [ __size ];

                    constexpr static auto size = __size;

                    using Type = __Type;

                    template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    constexpr auto construct (
                            __ArgumentTypes && ... arguments
                    ) noexcept -> void {

                        new ( this->_data ) __Type ( std :: forward < __ArgumentTypes > ( arguments ) ... );
                    }

                    constexpr auto destruct () noexcept -> void {

                        reinterpret_cast < __Type * > ( this->_data )->~__Type ();
                    }

                    constexpr auto data () const noexcept -> __Type const & {

                        return * reinterpret_cast < __Type const * > ( this->_data );
                    }

                    __CDS_cpplang_NonConstConstexprMemberFunction auto data () noexcept -> __Type & {

                        return * reinterpret_cast < __Type * > ( this->_data );
                    }
                };


                template < typename __Type, Size __primitiveSize = sizeof ( __Type ) > // NOLINT(bugprone-reserved-identifier)
                inline auto __allocPrimitiveObject () noexcept -> __Type * { // NOLINT(bugprone-reserved-identifier)

                    return reinterpret_cast < __Type * > ( malloc ( __primitiveSize ) );
                }


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
                inline auto __freePrimitiveObject ( // NOLINT(bugprone-reserved-identifier)
                        __Type * pObject
                ) noexcept -> void {

                    free ( pObject );
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
