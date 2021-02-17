//
// Created by loghin on 17.02.2021.
//

#ifndef CDS_STD_TYPES_H
#define CDS_STD_TYPES_H

typedef char * CString;
typedef const char * StringLiteral;

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;
typedef unsigned long long int uint64;

typedef signed char sint8;
typedef signed short int sint16;
typedef signed int sint32;
typedef signed long long int sint64;

typedef uint8 byte;

typedef uint64 Size;
typedef sint64 SignedSize;

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
    struct DoubleListNode {
        T                    data;
        DoubleListNode<T>  * pNext       {nullptr};
        DoubleListNode<T>  * pPrevious   {nullptr};
    };

    template <class T>
    struct SingleListNode {
        T                    data;
        SingleListNode<T>  * pNext       {nullptr};
    };
}

#endif

#endif //CDS_STD_TYPES_H
