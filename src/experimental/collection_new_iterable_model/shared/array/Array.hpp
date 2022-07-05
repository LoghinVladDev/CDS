//
// Created by loghin on 7/5/22.
//

#ifndef __CDS_SHARED_ARRAY_HPP__
#define __CDS_SHARED_ARRAY_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > class __Array {                                                       // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename, typename >
                    friend class __ListServer; // NOLINT(bugprone-reserved-identifier)

                protected:
                    using ElementType = __ElementType;

                private:
                    static Size const __a_minCapacity = 32ULL; // NOLINT(bugprone-reserved-identifier)

                private:
                    struct __ArrayImplDataContainer { // NOLINT(bugprone-reserved-identifier)
                        __ElementType * _pBuffer;
                        Size            _bufferOffset;
                        Size            _elementCount;
                        Size            _frontCapacity;
                        Size            _backCapacity;
                        Size            _frontNextCapacity;
                        Size            _backNextCapacity;
                    };

                private:
                    __ArrayImplDataContainer * _pData { nullptr };

                protected:
                    auto __a_clear ( // NOLINT(bugprone-reserved-identifier)
                            bool destroyBuffer
                    ) noexcept -> void;

                protected:
                    __CDS_NoDiscard constexpr auto __a_size () const noexcept -> Size; // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __a_remove ( // NOLINT(bugprone-reserved-identifier)
                            Index index
                    ) noexcept -> void;

                protected:
                    __CDS_NoDiscard constexpr auto __a_get ( // NOLINT(bugprone-reserved-identifier)
                            Index index
                    ) noexcept -> ElementType *;

                protected:
                    __CDS_NoDiscard constexpr auto __a_get ( // NOLINT(bugprone-reserved-identifier)
                            Index index
                    ) const noexcept -> ElementType const *;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_ARRAY_HPP__