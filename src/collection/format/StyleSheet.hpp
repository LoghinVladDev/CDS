//
// Created by loghin on 05.12.2021.
//

#ifndef CDS_STYLESHEET_HPP
#define CDS_STYLESHEET_HPP

#include <CDS/Object>
#include <CDS/HashMap>

namespace cds {

    class StyleSheet : public Object {
    public:
        class Style : public Object {
        private:

            HashMap < String, String > properties;

        public:

            __CDS_MaybeUnused __CDS_OptimalInline auto operator [] ( String const & propertyName ) const noexcept (false) -> String const & {
                if ( ! this->properties.containsKey( propertyName ) ) {
                    throw KeyException ( propertyName );
                }

                return this->properties[propertyName];
            }

            __CDS_MaybeUnused __CDS_OptimalInline auto operator [] ( String const & propertyName ) noexcept (false) -> String & {
                if ( ! this->properties.containsKey( propertyName ) ) {
                    throw KeyException ( propertyName );
                }

                return this->properties[propertyName];
            }

            __CDS_NoDiscard auto toString () const noexcept -> String override {
                return this->properties.sequence().fold(
                        "{\n"_s,
                        [](String const & foldedString, auto & entry) {
                            return foldedString + "\t" + entry.first() + ": " + entry.second() + ";\n";
                        }
                );
            }

        };

    private:



    };

}

__CDS_RegisterParseType(StyleSheet)

#endif //CDS_STYLESHEET_HPP
