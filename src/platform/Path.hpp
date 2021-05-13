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

    Path(StringLiteral path) noexcept : Path(String(path)) {}

    [[nodiscard]] auto toString () const noexcept -> String override { return this->_osPath; }
    [[nodiscard]] auto copy () const noexcept -> Path * override { return new Path(* this); }
    [[nodiscard]] auto hash () const noexcept -> Index override { return this->parent().nodeName().hash(); }

    inline auto parent () const noexcept -> Path { return (*this) / ".."; }
    [[nodiscard]] inline auto previous () const noexcept -> Path { return this->parent(); }

    inline auto nodeName () const noexcept -> String { return this->_osPath.substr(this->_osPath.findLast("/") + 1); }
    [[nodiscard]] inline auto currentName () const noexcept -> String { return this->nodeName(); }

    auto root () const noexcept -> Path {
        auto parent = this->parent();
        if ( this->_osPath == parent._osPath )
            return parent;
        return parent.root();
    }

    auto operator / (String const & f) const noexcept -> Path {
        return Path(this->_osPath + Path::directorySeparator() + f);
    }

    inline auto operator + (String const & f) const noexcept -> Path { return (*this) / f; }
    inline auto append (String const & f) const noexcept -> Path { return (*this) / f; }

    class WalkEntry;

    // walk
    [[nodiscard]] auto walk () const noexcept (false) -> LinkedList < WalkEntry >;
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



inline auto Path::walk() const noexcept (false) -> LinkedList<WalkEntry> {
    WalkEntry currentDirEntry;
    LinkedList < WalkEntry > entries;

    currentDirEntry.root() = * this;

#if defined(WIN32)
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

            auto nestedEntries = Path(this->append(entry->d_name)).walk();
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

#endif //CDS_PATH_H
