//
// Created by loghin on 26.09.2021.
//

#ifndef CDS_OPTIONS_HPP
#define CDS_OPTIONS_HPP

#define CDS_STRING_POSTFIX

#if defined(CDS_NO_POSTFIX_FUNCTIONS)

#undef CDS_INTEGER_POSTFIX
#undef CDS_BOOLEAN_POSTFIX
#undef CDS_STRING_POSTFIX
#undef CDS_LONG_POSTFIX
#undef CDS_FLOAT_POSTFIX
#undef CDS_DOUBLE_POSTFIX

#endif

#endif //CDS_OPTIONS_HPP
