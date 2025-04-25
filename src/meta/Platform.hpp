//
// Created by loghin on 19.04.2025.
//

#ifndef CDS_META_PLATFORM_HPP
#define CDS_META_PLATFORM_HPP

#ifdef WIN32
#define CDS_ATTR_win32 true
#else
#define CDS_ATTR_win32 false
#endif

#ifdef __linux
#define CDS_ATTR_linux true
#else
#define CDS_ATTR_linux false
#endif

#ifdef __APPLE__
#define CDS_ATTR_apple true
#else
#define CDS_ATTR_appl false
#endif

#endif // CDS_META_PLATFORM_HPP
