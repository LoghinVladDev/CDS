//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ITERABLE_REMOVE_OF_HPP__
#define __CDS_SHARED_ITERABLE_REMOVE_OF_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > class __IterableRemoveOf {                    // NOLINT(bugprone-reserved-identifier)

                private:
                    template <
                            typename __TIterableType        = __IterableType,       // NOLINT(bugprone-reserved-identifier)
                            typename __TFromIterableType    = __FromIterableType,   // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isSame < __TIterableType, __TFromIterableType > ()
                            > = 0
                    > auto __iro_selfReferentialCase_removeOf (                     // NOLINT(bugprone-reserved-identifier)
                            Size                        count,
                            __FromIterableType  const & from
                    ) noexcept -> Size;

                private:
                    template <
                            typename __TIterableType        = __IterableType,       // NOLINT(bugprone-reserved-identifier)
                            typename __TFromIterableType    = __FromIterableType,   // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    ! cds :: meta :: isSame < __TIterableType, __TFromIterableType > ()
                            > = 0
                    > auto __iro_selfReferentialCase_removeOf (                     // NOLINT(bugprone-reserved-identifier)
                            Size                        count,
                            __FromIterableType  const & from
                    ) noexcept -> Size;

                private:
                    template <
                            typename __TIterableType        = __IterableType,       // NOLINT(bugprone-reserved-identifier)
                            typename __TFromIterableType    = __FromIterableType,   // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isSame < __TIterableType, __TFromIterableType > ()
                            > = 0
                    > auto __iro_selfReferentialCase_removeFirstOf (                // NOLINT(bugprone-reserved-identifier)
                            __FromIterableType const & from
                    ) noexcept -> bool;

                private:
                    template <
                            typename __TIterableType        = __IterableType,       // NOLINT(bugprone-reserved-identifier)
                            typename __TFromIterableType    = __FromIterableType,   // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    ! cds :: meta :: isSame < __TIterableType, __TFromIterableType > ()
                            > = 0
                    > auto __iro_selfReferentialCase_removeFirstOf (                // NOLINT(bugprone-reserved-identifier)
                            __FromIterableType const & from
                    ) noexcept -> bool;

                private:
                    template <
                            typename __TIterableType        = __IterableType,       // NOLINT(bugprone-reserved-identifier)
                            typename __TFromIterableType    = __FromIterableType,   // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isSame < __TIterableType, __TFromIterableType > ()
                            > = 0
                    > auto __iro_selfReferentialCase_removeLastOf (                 // NOLINT(bugprone-reserved-identifier)
                            __FromIterableType const & from
                    ) noexcept -> bool;

                private:
                    template <
                            typename __TIterableType        = __IterableType,       // NOLINT(bugprone-reserved-identifier)
                            typename __TFromIterableType    = __FromIterableType,   // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    ! cds :: meta :: isSame < __TIterableType, __TFromIterableType > ()
                            > = 0
                    > auto __iro_selfReferentialCase_removeLastOf (                 // NOLINT(bugprone-reserved-identifier)
                            __FromIterableType const & from
                    ) noexcept -> bool;

                private:
                    template <
                            typename __TIterableType        = __IterableType,       // NOLINT(bugprone-reserved-identifier)
                            typename __TFromIterableType    = __FromIterableType,   // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isSame < __TIterableType, __TFromIterableType > ()
                            > = 0
                    > auto __iro_selfReferentialCase_removeAllOf (                  // NOLINT(bugprone-reserved-identifier)
                            __FromIterableType const & from
                    ) noexcept -> Size;

                private:
                    template <
                            typename __TIterableType        = __IterableType,       // NOLINT(bugprone-reserved-identifier)
                            typename __TFromIterableType    = __FromIterableType,   // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    ! cds :: meta :: isSame < __TIterableType, __TFromIterableType > ()
                            > = 0
                    > auto __iro_selfReferentialCase_removeAllOf (                  // NOLINT(bugprone-reserved-identifier)
                            __FromIterableType const & from
                    ) noexcept -> Size;

                private:
                    auto __iro_selfReferentialCase_removeNotOf ( // NOLINT(bugprone-reserved-identifier)
                            Size                        count,
                            __FromIterableType  const & from
                    ) noexcept -> Size;

                private:
                    auto __iro_selfReferentialCase_removeFirstNotOf ( // NOLINT(bugprone-reserved-identifier)
                            __FromIterableType const & from
                    ) noexcept -> bool;

                private:
                    auto __iro_selfReferentialCase_removeLastNotOf ( // NOLINT(bugprone-reserved-identifier)
                            __FromIterableType const & from
                    ) noexcept -> bool;

                private:
                    auto __iro_selfReferentialCase_removeAllNotOf ( // NOLINT(bugprone-reserved-identifier)
                            __FromIterableType const & from
                    ) noexcept -> Size;

                protected:
                    auto removeOf (
                            Size                        count,
                            __FromIterableType  const & from
                    ) noexcept -> Size;

                protected:
                    auto removeFirstOf (
                            __FromIterableType const & from
                    ) noexcept -> bool;

                protected:
                    auto removeLastOf (
                            __FromIterableType const & from
                    ) noexcept -> bool;

                protected:
                    auto removeAllOf (
                            __FromIterableType const & from
                    ) noexcept -> Size;

                protected:
                    auto removeNotOf (
                            Size                        count,
                            __FromIterableType  const & from
                    ) noexcept -> Size;

                protected:
                    auto removeFirstNotOf (
                            __FromIterableType const & from
                    ) noexcept -> bool;

                protected:
                    auto removeLastNotOf (
                            __FromIterableType const & from
                    ) noexcept -> bool;

                protected:
                    auto removeAllNotOf (
                            __FromIterableType const & from
                    ) noexcept -> Size;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_ITERABLE_REMOVE_OF_HPP__
