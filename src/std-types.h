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

typedef Size AddressValueType;

#endif //CDS_STD_TYPES_H
