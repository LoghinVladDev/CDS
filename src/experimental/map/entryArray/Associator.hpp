//
// Created by loghin on 6/15/22.
//

#ifndef __CDS_EX_MAP_ENTRY_ARRAY_ENTRY_ASSOCIATOR_HPP__
#define __CDS_EX_MAP_ENTRY_ARRAY_ENTRY_ASSOCIATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl { // NOLINT(bugprone-reserved-identifier)

                template < typename __ValueType > // NOLINT(bugprone-reserved-identifier)
                template < typename __KeyType > // NOLINT(bugprone-reserved-identifier)
                class __EntryArray < __ValueType > :: __EntryAssociator { // NOLINT(bugprone-reserved-identifier)

                private:
                    __EntryArray < __ValueType > & _array;

                public:
                    constexpr __EntryAssociator (
                            __EntryArray < __ValueType > & array
                    ) noexcept;

                protected:
                    __CDS_OptimalInline auto rightShiftFrom (
                            Index index
                    ) noexcept -> void {

                        (void) this->_array.pNewBefore ( index );
                    }

                public:
                    virtual ~__EntryAssociator() noexcept = default;

                public:
                    virtual auto clear () noexcept -> void {
                        this->_array.clear();
                    }

                protected:
                    virtual auto getAssociation (
                            __KeyType const & key
                    ) noexcept -> Index = 0;

                public:
                    template < typename __TValueType = __ValueType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __TValueType > () > = 0 >
                    __CDS_OptimalInline auto put (
                            __KeyType   const & key,
                            __ValueType const & value
                    ) noexcept -> void {

                        auto associatedIndex = this->getAssociation ( key );
                        Memory :: instance().destroy (
                                cds :: exchange (
                                        this->_array._pData [ associatedIndex ],
                                        Memory :: instance().create < __ValueType > ( value )
                                )
                        );
                    }

                public:
                    template < typename __TValueType = __ValueType, cds :: meta :: EnableIf < cds :: meta :: isMoveConstructible < __TValueType > () > = 0 >
                    __CDS_OptimalInline auto put (
                            __KeyType   const & key,
                            __ValueType      && value
                    ) noexcept -> void {

                        auto associatedIndex = this->getAssociation ( key );
                        Memory :: instance().destroy (
                                cds :: exchange (
                                        this->_array._pData [ associatedIndex ],
                                        Memory :: instance().create < __ValueType > ( std :: move ( value ) )
                                )
                        );
                    }
                };

            }
        }
    }
}

#endif // __CDS_EX_MAP_ENTRY_ARRAY_ENTRY_ASSOCIATOR_HPP__
