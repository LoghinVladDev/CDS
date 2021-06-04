//
// Created by vladl on 3/29/2021.
//

#ifndef CDS_PREPRO_H
#define CDS_PREPRO_H

#include "std-types.h"

# if defined(__GNUC__) && !defined (GCC_VERSION)

# define GCC_VERSION ( __GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__ )

# else

# define GCC_VERSION 0

# endif


#endif //CDS_PREPRO_H
