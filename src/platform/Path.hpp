//
// Created by loghin on 10.05.2021.
// Please report any bugs to github.com/LoghinVladDev/CDS - Issues
//

#ifndef CDS_PATH_H
#define CDS_PATH_H

#include <CDS/Object>
#include <CDS/LinkedList>

#include <CDS/File>

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
    friend class WalkEntry;
    explicit Path(bool noCheck) noexcept {}

    static LinkedList < char > possibleDirectorySeparators;

protected:
    String _osPath;

public:
    class InvalidPath : public std::exception {
        [[nodiscard]] auto what() const noexcept -> StringLiteral override {
            return "Invalid Path Given";
        }
    };

    class WalkNotADirectory : public std::exception {
        [[nodiscard]] auto what () const noexcept -> StringLiteral override {
            return "Walk Error : Path given does not refer to a directory";
        }
    };

#if defined(WIN32)
    class WalkIncompleteWin32 : public std::exception {
        [[nodiscard]] auto what () const noexcept -> StringLiteral override {
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

    Path(String const & path = CWD) noexcept (false) {
#if defined(WIN32)
//        if ( GetFileAttributesA ( path.cStr() ) != INVALID_FILE_ATTRIBUTES )
//            throw InvalidPath();

        constexpr static CDS_uint16 initialPathSize = 256;
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
        if ( lstat64 ( path.cStr(), & fileStat ) != 0 )
            throw InvalidPath();

        char resolvedPath[PATH_MAX];
        realpath(path.cStr(), resolvedPath);
        this->_osPath = resolvedPath;
#else
#warning Warning : Path::Path(String) Unsupported
#endif
    }

    Path(StringLiteral path) noexcept(false) : Path(String(path)) {}

    [[nodiscard]] auto toString () const noexcept -> String override { return this->_osPath; }
    [[nodiscard]] auto copy () const noexcept -> Path * override { return new Path(* this); }
    [[nodiscard]] auto hash () const noexcept -> Index override { return this->parent().nodeName().hash(); }

    [[nodiscard]] inline auto parent () const noexcept(false) -> Path { return (*this) / ".."; }
    [[nodiscard]] inline auto previous () const noexcept -> Path { return this->parent(); }

    [[nodiscard]] inline auto nodeName () const noexcept -> String { return this->_osPath.substr(this->_osPath.findLast(this->directorySeparator()) + 1); }
    [[nodiscard]] inline auto currentName () const noexcept -> String { return this->nodeName(); }

    [[nodiscard]] auto root () const noexcept -> Path {
        auto parent = this->parent();
        if ( this->_osPath == parent._osPath )
            return parent;
        return parent.root();
    }

    auto operator / (String const & f) const noexcept (false) -> Path {
        auto delimFiltered = [& f]() -> String { String c(f); c.forEach([](auto & e){if (Path::possibleDirectorySeparators.contains(e)) e = Path::directorySeparator(); }); return c; };
        return Path(this->_osPath + Path::directorySeparator() + delimFiltered());
    }

    inline auto operator + (String const & f) const noexcept (false) -> Path { return (*this) / f; }
    [[nodiscard]] inline auto append (String const & f) const noexcept (false) -> Path { return (*this) / f; }

    class WalkEntry;

    // walk
    [[nodiscard]] auto walk (int = INT32_MAX) const noexcept (false) -> LinkedList < WalkEntry >;

    [[nodiscard]] static auto walk (Path const & path, int = INT32_MAX) noexcept (false) -> LinkedList < WalkEntry >;
    [[nodiscard]] static auto walk (String const & path, int = INT32_MAX) noexcept (false) -> LinkedList < WalkEntry >;

#if defined(WIN32)
    class Win32RootPath;

    [[nodiscard]] static auto platformDependantRoots () noexcept -> LinkedList < Win32RootPath >;
#elif defined(__linux)
#else
#warning Warning : Path::rootsPlatform () Undefined
#endif
    [[nodiscard]] static auto roots () noexcept -> LinkedList < Path >;
};

class Path::WalkEntry : public Object {
private:
    Path _root {false};
    LinkedList < String > _directories;
    LinkedList < String > _files;

public:
    WalkEntry () noexcept = default;
    WalkEntry ( WalkEntry const & ) noexcept = default;
//    WalkEntry ( WalkEntry && o ) noexcept :
//            _root(std::move(o._root)),
//            _directories(std::move(o._directories)),
//            _files(std::move(o._files)){ }

    [[nodiscard]] auto toString() const noexcept -> String override {
        return String("WalkEntry {") +
               " root = " + this->_root.toString() +
               ", directories = " + this->_directories.toString() +
               ", files = " + this->_files.toString() +
               "}";
    }

    [[nodiscard]] constexpr auto root () const noexcept -> Path const & { return this->_root; }
    constexpr auto root () noexcept -> Path & { return this->_root; }

    [[nodiscard]] constexpr auto directories () const noexcept -> LinkedList < String > const & { return this->_directories; }
    constexpr auto directories () noexcept -> LinkedList < String > & { return this->_directories; }

    [[nodiscard]] constexpr auto files () const noexcept -> LinkedList < String > const & { return this->_files; }
    constexpr auto files () noexcept -> LinkedList < String > & { return this->_files; }

    [[nodiscard]] auto copy() const noexcept -> WalkEntry * override {
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

    [[nodiscard]] auto toString() const noexcept -> String override {
        return String("Win32RootPath {") +
            " path = " + this->path.toString() +
            ", deviceName = " + this->deviceName +
            ", volumeName = " + this->volumeName +
            " }";
    }
};
#endif

inline auto Path::walk(int depth) const noexcept (false) -> LinkedList<WalkEntry> {
    if ( depth <= 0 )
        return {};

    WalkEntry currentDirEntry;
    LinkedList < WalkEntry > entries;

    currentDirEntry.root() = * this;

#if defined(WIN32)

    WIN32_FIND_DATA win32FindData {};

    HANDLE fileHandle = FindFirstFileA ( (this->_osPath + Path::directorySeparator() + "*").cStr(), & win32FindData );
    if ( fileHandle == INVALID_HANDLE_VALUE ) {
//        throw WalkNotADirectory();
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

[[nodiscard]] inline auto Path::roots () noexcept -> LinkedList < Path > {
    LinkedList < Path > paths;
#if defined(WIN32)
   auto pDRList = Path::platformDependantRoots();

   for ( auto & p : pDRList )
       paths.pushBack(p.path);
#elif defined(__linux)
#else
#warning Warning: Path::roots undefined
#endif
   return paths;
}

#if defined(WIN32)
[[nodiscard]] inline auto Path::platformDependantRoots () noexcept -> LinkedList < Win32RootPath > {
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

inline LinkedList < char > Path::possibleDirectorySeparators = {'/', '\\'};

#endif //CDS_PATH_H
