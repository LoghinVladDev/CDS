//
// Created by loghin on 19.01.2021.
//

#ifndef CDS_NOTIMPLEMENTEDEXCEPTION_H
#define CDS_NOTIMPLEMENTEDEXCEPTION_H


#include <exception>
class NotImplementedException : public std::exception {
    [[nodiscard]] const char * what() const noexcept override {
        return "Function/Feature not yet implemented";
    }
};


#endif //CDS_NOTIMPLEMENTEDEXCEPTION_H
