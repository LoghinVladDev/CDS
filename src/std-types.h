//
// Created by loghin on 17.02.2021.
//

#ifndef CDS_STD_TYPES_H
#define CDS_STD_TYPES_H

typedef char * CString;
typedef const char * StringLiteral;

typedef unsigned char CDS_uint8;
typedef unsigned short int CDS_uint16;
typedef unsigned int CDS_uint32;
typedef unsigned long long int CDS_uint64;

typedef signed char CDS_sint8;
typedef signed short int CDS_sint16;
typedef signed int CDS_sint32;
typedef signed long long int CDS_sint64;

typedef CDS_uint8 CDS_byte;

typedef CDS_uint64 Size;
typedef CDS_sint64 SignedSize;

typedef SignedSize Index;

#ifdef __cplusplus
#include <functional>
namespace dataTypes {
#define GEN_ONCE(_text) _text
#define GEN_TWICE(_text) _text, _text
#define GEN_FUNCTION_TYPEDEFS(_group, _retType, _paramType, _paramCount, _exceptSpec, _preExceptSpec) \
    template<class T> using _preExceptSpec ## Value ## _group = auto (*) ( _paramCount(_paramType)) _exceptSpec -> _retType;\
    template<class T> using _preExceptSpec ## Reference ## _group = auto (*) ( _paramCount(_paramType &)) _exceptSpec -> _retType;\
    template<class T> using _preExceptSpec ## ConstReference ## _group = auto (*) ( _paramCount(_paramType const &)) _exceptSpec -> _retType;\
    template<class T> using _preExceptSpec ## LambdaValue ## _group = std::function < auto ( _paramCount(_paramType)) _exceptSpec -> _retType >; \
    template<class T> using _preExceptSpec ## LambdaReference ## _group = std::function < auto ( _paramCount(_paramType &)) _exceptSpec -> _retType >; \
    template<class T> using _preExceptSpec ## LambdaConstReference ## _group = std::function < auto ( _paramCount(_paramType const &)) _exceptSpec -> _retType >;

    GEN_FUNCTION_TYPEDEFS(CompareFunction, bool, T, GEN_TWICE, noexcept, )
    GEN_FUNCTION_TYPEDEFS(CompareFunction, bool, T, GEN_TWICE, noexcept(false), Throw )
    GEN_FUNCTION_TYPEDEFS(Action, void, T, GEN_ONCE, noexcept, )
    GEN_FUNCTION_TYPEDEFS(Action, void, T, GEN_ONCE, noexcept(false), Throw )
    GEN_FUNCTION_TYPEDEFS(Predicate, bool, T, GEN_ONCE, noexcept, )
    GEN_FUNCTION_TYPEDEFS(Predicate, bool, T, GEN_ONCE, noexcept(false), Throw )

#undef GEN_FUNCTION_TYPEDEFS
#undef GEN_TWICE
#undef GEN_ONCE
}

namespace dataTypes {

    template <class T>
    struct SingleListNode {
        T                    data;
        SingleListNode<T>  * pNext       {nullptr};
    };
}

#endif

#endif //CDS_STD_TYPES_H
