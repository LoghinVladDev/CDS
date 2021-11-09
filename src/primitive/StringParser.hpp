//
// Created by loghin on 27.09.2021.
//

#ifndef CDS_STRINGPARSER_HPP
#define CDS_STRINGPARSER_HPP

#include <CDS/String>
#include <CDS/LinkedList>
#include <CDS/Integer>

namespace cds {

    class StringParser : public Object {
    private:
        String const            * _parsingOver { nullptr };
        Index                     _current {0};
        LinkedList < Integer >    _marks;

    public:
        StringParser() noexcept = delete;
        explicit StringParser(String const & string) noexcept : _parsingOver(& string) {}
    };

}

#endif //CDS_STRINGPARSER_HPP
