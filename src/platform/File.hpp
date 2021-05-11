//
// Created by loghin on 10.05.2021.
//

#ifndef CDS_FILE_HPP
#define CDS_FILE_HPP

#include <CDS/Object>
#include <CDS/LinkedList>


class File : public Object {
private:
    enum FileFlag : CDS_uint8 {
        NONE        = 0x00u,
        EXECUTABLE  = 0x01u,
        WRITABLE    = 0x02u,
        READABLE    = 0x04u,

        DIRECTORY   = 0x08u
    };

    typedef CDS_uint8 FileFlags;

protected:
    String      _name;
    FileFlags   _flags  {FileFlag::NONE};

    File () noexcept = default;

public:
    auto toString () const noexcept -> String override;
    auto copy () const noexcept -> File * override;
    auto hash () const noexcept -> Index override;

    class Regular;
    class Directory;
    class Link;

    constexpr auto name () const noexcept -> String const & { return this->_name; }
    constexpr auto name () noexcept -> String & { return this->_name; }

    virtual auto load () noexcept -> File & = 0;
    virtual auto save () noexcept -> File & = 0;

    constexpr auto isDirectory () const noexcept -> bool { return (bool)(this->_flags & FileFlag::DIRECTORY); }
    constexpr auto isExecutable () const noexcept -> bool { return (bool)(this->_flags & FileFlag::EXECUTABLE); }
    constexpr auto isReadable () const noexcept -> bool { return (bool)(this->_flags & FileFlag::READABLE); }
    constexpr auto isWritable () const noexcept -> bool { return (bool)(this->_flags & FileFlag::WRITABLE); }
};

#if defined(WIN32)
#elif defined(__linux)

#include <dirent.h>

#endif

class File::Directory : public File {
public:
    class InvalidDirectory : public std::exception {
    public:
        [[nodiscard]] auto what() const noexcept -> StringLiteral override {
            return "Invalid Path / File not a Directory";
        }
    };

    constexpr static StringLiteral CURRENT_DIRECTORY_HANDLE = ".";

private:
    LinkedList < File * > _entries;

#if defined(WIN32)
#elif defined(__linux)

    typedef DIR PlatformDirectory;
    constexpr static PlatformDirectory * NULL_HANDLE = nullptr;

    PlatformDirectory * platformDirectoryHandle {NULL_HANDLE};

#endif

public:
    Directory() noexcept = default;

    explicit Directory ( String const & path ) noexcept (false) : File() {
#if defined (WIN32)
#elif defined(__linux)
        this->platformDirectoryHandle = NULL_HANDLE;
#else
#error "Error : File::Directory Unsupported"
#endif
        this->open( path );
    }

    auto toString () const noexcept -> String override;
    auto copy () const noexcept -> File::Directory * override;
    auto hash () const noexcept -> Index override;

    [[nodiscard]] inline auto entries () const noexcept -> LinkedList < File * > const & { return this->_entries; }
    inline auto entries () noexcept -> LinkedList < File * > & { return this->_entries; }

//    static auto open ( String const & ) noexcept (false) -> Directory;
    auto open ( String const & path ) noexcept (false) -> File::Directory & {
        if ( this->isOpen() )
            this->close();

#if defined(WIN32)
#elif defined(__linux)
        auto p = opendir(path.cStr());
        if ( p == nullptr )
            throw InvalidDirectory();

        this->platformDirectoryHandle = p;
#else
#error Error: File::Directory Unsupported
#endif

        this->load();

        return * this;
    }

    auto close () noexcept -> File::Directory & {
        for ( auto & p : this->_entries )
            delete p;

        this->_entries.clear();

#if defined(WIN32)
#elif defined(__linux)
        closedir(this->platformDirectoryHandle);
#else
#error Error: File::Directory Unsupported
#endif

        return * this;
    }

    [[nodiscard]] constexpr auto isOpen () const noexcept -> bool {
#if defined(WIN32)
#elif defined(__linux)
        return this->platformDirectoryHandle != nullptr;
#else
#error Error: File::Directory Unsupported
#endif
    }

    auto load() noexcept -> File::Directory & override {

#if defined(WIN32)
#elif defined(__linux)
        dirent64 * pEntry = readdir64( this->platformDirectoryHandle );

        while ( pEntry != nullptr ) {
            this->_entries.pushBack(linuxLoadFile(pEntry));

            pEntry = readdir64( this->platformDirectoryHandle );
        }
#else
#error Error: File::Directory Unsupported
#endif

        return * this;
    }

#if defined(WIN32)
#elif defined(__linux)
    auto static linuxLoadFile(dirent64 const *) noexcept -> File *;
#else
#error Error: File::Directory Unsupported
#endif
};

#if defined(__linux)
inline auto File::Directory::linuxLoadFile(const dirent64 * pEntry) noexcept -> File * {

}
#endif

#endif //CDS_FILE_HPP
