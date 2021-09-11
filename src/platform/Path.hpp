//
// Created by loghin on 10.05.2021.
// Please report any bugs to github.com/LoghinVladDev/CDS - Issues
//

#ifndef CDS_PATH_H
#define CDS_PATH_H

#include <CDS/Object>
#include <CDS/LinkedList>

#if defined(WIN32)
#include <windows.h>
#elif defined(__linux)
#include <sys/stat.h>
#include <unistd.h>
#include <linux/limits.h>
#include <dirent.h>
#else
#warning Warning : Path-lib Unsupported
#endif

class Path : public Object {
private:
    explicit Path(bool skipPathCheck __CDS_MaybeUnused) noexcept {}

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_17

    static LinkedList < char > possibleDirectorySeparators;

#else

    LinkedList < char > possibleDirectorySeparators = { '/', '\\' };

#endif

protected:
    String _osPath;

public:
    class InvalidPath : public std::exception {
        __CDS_NoDiscard auto what() const noexcept -> StringLiteral override {
            return "Invalid Path Given";
        }
    };

    class WalkNotADirectory : public std::exception {
        __CDS_NoDiscard auto what () const noexcept -> StringLiteral override {
            return "Walk Error : Path given does not refer to a directory";
        }
    };

    inline auto operator == (Path const & o) const noexcept -> bool {
        return this->_osPath == o._osPath;
    }

    __CDS_NoDiscard auto equals(Object const & o) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype ( this ) > ( & o );
        if ( p == nullptr ) return false;
        return this->operator == (* p);
    }

#if defined(WIN32)
    class WalkIncompleteWin32 : public std::exception {
        __CDS_NoDiscard auto what () const noexcept -> StringLiteral override {
            return "Walk Error : Incomplete";
        }
    };
#endif

    constexpr static StringLiteral CWD = "."; // current working directory

    static auto directorySeparator () noexcept -> char {
#if defined(WIN32)
        return '\\';
#elif defined(__linux)
        return '/';
#else
#warning Unsupported : Path::directorySeparator
#endif
    }

    Path() noexcept : Path(CWD) { }
    Path(String const & path) noexcept (false) { // NOLINT(google-explicit-constructor)
#if defined(WIN32)

        constexpr static uint16 initialPathSize = 256;
        char * resolvedPath = (char *) malloc (initialPathSize);

        auto res = GetFullPathNameA(path.cStr(), initialPathSize, resolvedPath, nullptr);
        if ( res >= initialPathSize ) {
            free ( resolvedPath );
            resolvedPath = (char *) malloc (res + 1);
            if ( GetFullPathNameA ( path.cStr(), res + 1, resolvedPath, nullptr ) == 0 ) {
                free ( resolvedPath );
                throw InvalidPath();
            }
        } else if ( res == 0 )
            throw InvalidPath();

        if ( GetFileAttributesA(resolvedPath) == INVALID_FILE_ATTRIBUTES ) {
            free(resolvedPath);
            throw InvalidPath();
        }

        this->_osPath = resolvedPath;
        free ( resolvedPath );

#elif defined(__linux)

        struct stat64 fileStat {};
        if ( stat64 ( path.cStr(), & fileStat ) != 0 )
            throw InvalidPath();

        char resolvedPath[PATH_MAX];
        realpath(path.cStr(), resolvedPath);
        this->_osPath = resolvedPath;

#else

#warning Warning : Path::Path(String) Unsupported

#endif
    }

    Path(StringLiteral path) noexcept(false) : Path(String(path)) {} // NOLINT(google-explicit-constructor)

    Path & operator = (Path const &) noexcept = default;
    Path & operator = (String const & s) noexcept(false) {
        return ( ( * this ) = Path( s ) );
    }

    Path & operator = (StringLiteral s) noexcept(false) {
        return ( ( * this ) = Path( s ) );
    }

    __CDS_NoDiscard auto toString () const noexcept -> String override { return this->_osPath; }
    __CDS_NoDiscard auto copy () const noexcept -> Path * override { return new Path(* this); }
    __CDS_NoDiscard auto hash () const noexcept -> Index override { return this->parent().nodeName().hash(); }

    __CDS_NoDiscard inline auto parent () const noexcept(false) -> Path { // NOLINT(misc-no-recursion)
        auto parentPath = String (this->_osPath.substr(0, this->_osPath.findLast(Path::directorySeparator())));
        if ( parentPath.empty() ) parentPath = this->root().toString();

        return parentPath;
    }

    __CDS_NoDiscard __CDS_MaybeUnused inline auto previous () const noexcept -> Path { return this->parent(); }

    __CDS_NoDiscard inline auto nodeName () const noexcept -> String { return this->_osPath.substr(this->_osPath.findLast(Path::directorySeparator()) + 1); }
    __CDS_NoDiscard __CDS_MaybeUnused inline auto currentName () const noexcept -> String { return this->nodeName(); }

    __CDS_NoDiscard auto root () const noexcept -> Path { // NOLINT(misc-no-recursion)
        auto parent = this->parent();
        if ( this->_osPath == parent._osPath )
            return parent;
        return parent.root();
    }

    auto operator / (String const & f) const noexcept (false) -> Path {
        auto delimFiltered = [
#if __CDS_cpplang_core_version < __CDS_cpplang_core_version_17
                this,
#endif
                & f
        ]() -> String { String c(f); c.forEach([
#if __CDS_cpplang_core_version < __CDS_cpplang_core_version_17
                this
#endif
        ](String::ElementType & e){if (Path::possibleDirectorySeparators.contains(e)) e = Path::directorySeparator(); }); return c; };
        return {this->_osPath + Path::directorySeparator() + delimFiltered()};
    }

    inline auto operator + (String const & f) const noexcept (false) -> Path { return (*this) / f; }
    __CDS_NoDiscard inline auto append (String const & f) const noexcept (false) -> Path { return (*this) / f; }

    class WalkEntry;

    __CDS_NoDiscard auto walk (int = INT32_MAX) const noexcept (false) -> LinkedList < WalkEntry >;

    __CDS_NoDiscard static auto walk (Path const & path, int = INT32_MAX) noexcept (false) -> LinkedList < WalkEntry >;
    __CDS_NoDiscard static auto walk (String const & path, int = INT32_MAX) noexcept (false) -> LinkedList < WalkEntry >;

#if defined(WIN32)
    class Win32RootPath;

    __CDS_NoDiscard static auto platformDependantRoots () noexcept -> LinkedList < Win32RootPath >;
#elif defined(__linux)
#else
#warning Warning : Path::platformDependantRoots () Undefined
#endif
    __CDS_NoDiscard static auto roots () noexcept -> LinkedList < Path >;
};

class Path::WalkEntry : public Object {
private:
    Path _root {false};
    LinkedList < String > _directories;
    LinkedList < String > _files;

public:
    inline auto operator == (WalkEntry const & o) const noexcept -> bool {
        return this->_root == o._root && this->_files == o._files && this->_directories == o._directories;
    }

    __CDS_NoDiscard auto equals(Object const & o) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype (this) > ( & o );
        if ( p == nullptr ) return false;

        return this->operator==(* p);
    }

    WalkEntry () noexcept = default;
    WalkEntry ( WalkEntry const & ) noexcept = default;

    __CDS_NoDiscard auto toString() const noexcept -> String override {
        return String("WalkEntry {") +
               " root = " + this->_root.toString() +
               ", directories = " + this->_directories.toString() +
               ", files = " + this->_files.toString() +
               "}";
    }

    __CDS_NoDiscard __CDS_MaybeUnused constexpr auto root () const noexcept -> Path const & { return this->_root; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto root () noexcept -> Path & { return this->_root; }

    __CDS_NoDiscard constexpr auto directories () const noexcept -> LinkedList < String > const & { return this->_directories; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto directories () noexcept -> LinkedList < String > & { return this->_directories; }

    __CDS_NoDiscard constexpr auto files () const noexcept -> LinkedList < String > const & { return this->_files; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto files () noexcept -> LinkedList < String > & { return this->_files; }

    __CDS_NoDiscard auto copy() const noexcept -> WalkEntry * override {
        return new WalkEntry (* this);
    }

    [[nodiscard]] auto hash () const noexcept -> Index override {
        return this->_root.hash() + this->_directories.hash() + this->_files.hash();
    }
};

#if defined(WIN32)
class Path::Win32RootPath : public Object {
public:
    Path    path;
    String  deviceName;
    String  volumeName;

    __CDS_NoDiscard auto toString() const noexcept -> String override {
        return String("Win32RootPath {") +
            " path = " + this->path.toString() +
            ", deviceName = " + this->deviceName +
            ", volumeName = " + this->volumeName +
            " }";
    }

    inline auto operator == (Win32RootPath const & o) const noexcept -> bool {
        if ( this == & o ) return true;

        return this->path == o.path && this->deviceName == o.deviceName && this->volumeName == o.volumeName;
    }

    __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype ( this ) > ( & o );
        if ( p == nullptr ) return false;
        return this->operator == (*p);
    }
};
#endif

inline auto Path::walk(int depth) const noexcept (false) -> LinkedList<WalkEntry> { // NOLINT(misc-no-recursion)
    if ( depth <= 0 )
        return {};

    WalkEntry currentDirEntry;
    LinkedList < WalkEntry > entries;

    currentDirEntry.root() = * this;

#if defined(WIN32)

    WIN32_FIND_DATAA win32FindData {};

    HANDLE fileHandle = FindFirstFileA ( (this->_osPath + Path::directorySeparator() + "*").cStr(), & win32FindData );
    if ( fileHandle == INVALID_HANDLE_VALUE ) {
        return {};
    }

    do {
        if ( std::strcmp ( win32FindData.cFileName, "." ) == 0 || std::strcmp ( win32FindData.cFileName, ".." ) == 0 ) {
            // do nothing
        } else if ( (bool)(win32FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
            currentDirEntry.directories().pushBack(win32FindData.cFileName);

            auto nestedEntries = Path(this->append(win32FindData.cFileName)).walk(depth - 1);
            for ( auto & e : nestedEntries )
                entries.pushBack ( e );
        } else {
            currentDirEntry.files().pushBack(win32FindData.cFileName);
        }
    } while ( FindNextFileA ( fileHandle, & win32FindData ) != FALSE );

    DWORD errorID = GetLastError();
    if ( errorID != ERROR_NO_MORE_FILES ) {
        FindClose(fileHandle);
        throw WalkIncompleteWin32();
    }

    FindClose(fileHandle);

    entries.pushFront(currentDirEntry);

#elif defined(__linux)

    auto dir = opendir ( this->_osPath.cStr() );
    if ( dir == nullptr )
        throw WalkNotADirectory();

    auto entry = readdir64(dir);
    while ( entry != nullptr ) {
        if ( entry->d_type == DT_LNK ) {
            // do nothing
        }
        if ( std::strcmp ( entry->d_name, "." ) == 0 || std::strcmp ( entry->d_name, ".." ) == 0 ) {
            // do nothing
        } else if ( entry->d_type == DT_DIR ) {
            currentDirEntry.directories().pushBack(entry->d_name);

            auto nestedEntries = Path(this->append(entry->d_name)).walk(depth - 1);
            for ( auto & e : nestedEntries )
                entries.pushFront( e );
        } else {
            currentDirEntry.files().pushBack(entry->d_name);
        }

        entry = readdir64(dir);
    }

    closedir ( dir );
    entries.pushBack(currentDirEntry);

#else

#warning Warning : Path::walk Unsupported

#endif

    return entries;
}

inline auto Path::walk(const Path &path, int depth) noexcept(false) -> LinkedList< WalkEntry > { return path.walk(depth); }
inline auto Path::walk(const String &path, int depth) noexcept(false) -> LinkedList< WalkEntry > { return Path(path).walk(depth); }

__CDS_NoDiscard inline auto Path::roots () noexcept -> LinkedList < Path > {
    LinkedList < Path > paths;
#if defined(WIN32)
    auto pDRList = Path::platformDependantRoots();

    for ( auto & p : pDRList )
        paths.pushBack(p.path);
#elif defined(__linux)

    return { "/" };

#else

#warning Warning: Path::roots undefined

#endif
}

#if defined(WIN32)

__CDS_NoDiscard inline auto Path::platformDependantRoots () noexcept -> LinkedList < Win32RootPath > {
    LinkedList < Win32RootPath > rootElements;

    char volumeName [MAX_PATH];
    char deviceName [MAX_PATH];
    char * names;

    HANDLE firstVolumeHandle = FindFirstVolumeA ( volumeName, MAX_PATH );

    if ( firstVolumeHandle == INVALID_HANDLE_VALUE )  return rootElements;

    do {
        if ( strstr(volumeName, "\\\\?\\") != volumeName || volumeName[strlen(volumeName) - 1] != '\\' )
            continue;

        Win32RootPath current;

        char * actualName = volumeName + strlen("\\\\?\\");
        * strrchr(actualName, '\\') = 0;

        DWORD charCount = QueryDosDeviceA( actualName, deviceName, MAX_PATH );

        current.deviceName = deviceName;
        current.volumeName = actualName;

        names = (char *)malloc(MAX_PATH + 1);
        DWORD reqSize = 0;

        if ( GetVolumePathNamesForVolumeNameA ( actualName, names, MAX_PATH + 1, & reqSize ) == FALSE ) {
            free (names);

//            if ( GetLastError() != ERROR_MORE_DATA )
//                continue;

            names = (char *) malloc (reqSize + 1);
            GetVolumePathNamesForVolumeNameA ( actualName, names, reqSize + 1, nullptr );
        }

        for ( auto * p = names; p[0] != '\0'; p += strlen(p) + 1 )
            printf("%s\n", p);

        try {
            current.path = Path(names);
        } catch (std::exception const & e) {
            free (names);
            continue;
        }

        free (names);

        std::cout << current.toString() << '\n';

    } while ( FindNextVolumeA (firstVolumeHandle, volumeName, MAX_PATH) != FALSE );

    FindVolumeClose(firstVolumeHandle);

    return rootElements;
}

#endif

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_17

inline LinkedList < char > Path::possibleDirectorySeparators = {'/', '\\'};

#endif

#endif //CDS_PATH_H
