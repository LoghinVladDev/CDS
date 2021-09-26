//
// Created by loghin on 26.09.2021.
//

#ifndef CDS_DEBUG_HPP
#define CDS_DEBUG_HPP

#if defined(NDEBUG)

#if defined(CDS_DEBUG)
#undef CDS_DEBUG
#endif

#endif

#ifdef CDS_DEBUG

#if ! defined(_MSC_VER)
#warning CDS Object Debug Enabled
#endif

#ifndef debug_private
#define debug_private public
#endif

#else

#ifndef debug_private
#define debug_private private
#endif

#endif

#endif //CDS_DEBUG_HPP
