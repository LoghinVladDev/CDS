//
// Created by loghin on 10.05.2021.
//

#ifndef CDS_PATH_H
#define CDS_PATH_H

#include <CDS/Object>
#include <CDS/LinkedList>

#include <CDS/File>

//#if defined(WIN32)
//#include <CDS/WindowsFile>
//#elif defined(__linux)
//#include <CDS/LinuxFile>
//#endif

#if defined(WIN32)
class WindowsFile;
class WindowsPath;
#elif defined(__linux)
class LinuxFile;
class LinuxPath;
#endif

class Path : public Object {
protected:
    String _osPath;

    Path(Path const &) noexcept;
    Path(String const &) noexcept;

public:
#if defined(WIN32)
    typedef WindowsFile PlatformFile;
    typedef WindowsPath PlatformPath;
#elif defined(__linux)
    typedef LinuxFile PlatformFile;
    typedef LinuxPath PlatformPath;
#endif

    auto toString () const noexcept -> String override;
    auto copy () const noexcept -> Path * override = 0;
    auto hash () const noexcept -> Index override;

    auto file () const noexcept -> File;
    auto parent () const noexcept -> PlatformPath;
    auto previous () const noexcept -> PlatformPath;
    auto root () const noexcept -> PlatformPath;
    auto current () const noexcept -> String;

    // walk ()
//#if defined(WIN32)
//    static auto walk (File::Directory const &, int = 0) noexcept -> LinkedList < WindowsFile >;
//    auto walk (int = 0) const noexcept(false) -> LinkedList < WindowsFile >;
//#elif defined(__linux)
//    static auto walk (File::Directory const &, int = 0) noexcept -> LinkedList < LinuxFile >;
//    auto walk (int = 0) const noexcept(false) -> LinkedList < LinuxFile >;
//#endif
    static auto walk (File::Directory const &, int = 0) noexcept -> LinkedList < PlatformFile >;
    auto walk (int = 0) const noexcept(false) -> LinkedList < PlatformFile >;
};


#endif //CDS_PATH_H
