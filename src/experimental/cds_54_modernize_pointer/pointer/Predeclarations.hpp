/*
 * Created by loghin on 20/11/22.
 */

#ifndef __CDS_SMART_POINTERS_PREDECLARATIONS_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SMART_POINTERS_PREDECLARATIONS_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {
    namespace __hidden {
        namespace __impl {

            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __DefaultSmartPointerDeleter {   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public:
                auto operator () (
                        __ElementType * pointer
                ) const noexcept -> void {

                    delete pointer;
                }
            };


            template < typename __ElementType >                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __DefaultSmartPointerDeleter < __ElementType [] > {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public:
                template <
                        typename __ConvertibleType,
                        cds :: meta :: EnableIf <
                                cds :: meta :: isConvertible < __ConvertibleType (*)[], __ElementType (*)[] > ()
                        > = 0
                > auto operator () (
                        __ConvertibleType * pointer
                ) const noexcept -> void {

                    delete [] pointer;
                }
            };

        } /* namespace __impl */
    } /* namespace __hidden */

    /**
     * @class abstract type representing a smart pointer to a given type
     * @tparam __ElementType is the addressed type
     */
    template <
            typename __ElementType  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class SmartPointer;

    /**
     * @class type representing an Unique Pointer ( owned by one object only ) to a given type
     * @tparam __ElementType is the addressed type
     * @tparam __Deleter is the type of meta-class that will handle the deletion of the memory
     */
    template <
            typename __ElementType,                                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Deleter = __hidden :: __impl :: __DefaultSmartPointerDeleter < __ElementType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class UniquePointer;

    /**
     * @class type representing a Shared Pointer ( deleted when not owned ) to a given type
     * @tparam __ElementType is the addressed type
     * @tparam __Deleter is the type of meta-class that will handle the deletion of the memory
     */
    template <
            typename __ElementType,                                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Deleter = __hidden :: __impl :: __DefaultSmartPointerDeleter < __ElementType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class SharedPointer;

    /**
     * @class type representing a Raw Pointer ( not owned, only addressed ) to a given type
     * @tparam __ElementType is the addressed type
     */
    template <
            typename __ElementType  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class RawPointer;

    /**
     * @class type representing a Shared Pointer Observer ( not owned, can gain ownership over shared area through elevation ) to a given type
     * @tparam __ElementType is the addressed type
     * @tparam __Deleter is the type of meta-class that will handle the deletion of the memory
     */
    template <
            typename __ElementType,                                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Deleter = __hidden :: __impl :: __DefaultSmartPointerDeleter < __ElementType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class WeakPointer;

    template <
            typename __ElementType  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > using ForeignPointer = RawPointer < __ElementType >;

    template <
            typename __ElementType,                                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Deleter = __hidden :: __impl :: __DefaultSmartPointerDeleter < __ElementType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > using AtomicSharedPointer = SharedPointer < __ElementType, __Deleter >;

} /* namespace cds */

#endif /* __CDS_SMART_POINTERS_PREDECLARATIONS_HPP__ */