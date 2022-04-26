//
// Created by loghin on 4/23/2022.
//

#ifndef __CDS_EX_VIEW_HPP__
#define __CDS_EX_VIEW_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename IterableType >
        class View {
        private:
            IterableType & iterable;

        public:
            explicit constexpr View ( IterableType & iterable ) noexcept :
                    iterable ( iterable ) {

            }

            template < typename DerivedIterableType, EnableIf < isDerivedFrom < RemoveReference < DerivedIterableType >, RemoveReference < IterableType > > :: value > = 0 >
            explicit constexpr View ( DerivedIterableType & iterable ) noexcept :
                    iterable ( iterable ) {

            }

            __CDS_NoDiscard __CDS_OptimalInline auto size () const noexcept -> Size {
                return this->iterable.size();
            }

            class Iterator {
            private:
                using IterableTypeIterator = typename std :: conditional <
                        Type < IterableType > :: isConst,
                        typename IterableType :: ConstIterator,
                        typename IterableType :: Iterator
                > :: type;

                using IterableTypeElementType = typename std :: conditional <
                        Type < IterableType > :: isConst,
                        typename IterableType :: ElementType const,
                        typename IterableType :: ElementType
                > :: type;

                IterableTypeIterator it;

            public:
                explicit Iterator ( IterableTypeIterator it ) noexcept :
                        it ( std :: move ( it ) ) {

                }

                __CDS_OptimalInline auto operator * () const noexcept -> IterableTypeElementType & {
                    return * this->it;
                }

                __CDS_OptimalInline auto operator ++ () noexcept -> Iterator & {
                    (void) ++ this->it;
                    return * this;
                }

                __CDS_OptimalInline auto operator != ( Iterator const & itObj ) const noexcept -> bool {
                    return this->it != itObj.it;
                }
            };

            __CDS_OptimalInline auto begin () noexcept -> Iterator {
                return Iterator ( this->iterable.begin() );
            }

            __CDS_OptimalInline auto end () noexcept -> Iterator {
                return Iterator ( this->iterable.end() );
            }
        };

    }
}

#endif // __CDS_EX_VIEW_HPP__
