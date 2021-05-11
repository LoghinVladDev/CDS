//
// Created by loghin on 10.05.2021.
//

#ifndef CDS_FILE_HPP
#define CDS_FILE_HPP

#include <CDS/Object>
#include <CDS/LinkedList>

#if defined(WIN32)
#elif defined(__linux)

#include <dirent.h>

#endif

class File : public Object {
protected:
#if defined(WIN32)
#elif defined(__linux)
#endif

private:
    enum FileFlag : CDS_uint8 {
        NO_FILE_FLAGS   = 0x00u,
        EXECUTABLE      = 0x01u,
        WRITABLE        = 0x02u,
        READABLE        = 0x04u,

        DIRECTORY       = 0x08u
    };

    typedef CDS_uint8 FileFlags;

protected:
    String      _name;
    FileFlags   _flags  {FileFlag::NO_FILE_FLAGS};

    File () noexcept = default;

public:
    auto toString () const noexcept -> String override { return ""; }
    auto copy () const noexcept -> File * override { return nullptr; }
    auto hash () const noexcept -> Index override { return 0; }

    class Regular;
    class Directory;
    class Link;

    [[nodiscard]] constexpr auto name () const noexcept -> String const & { return this->_name; }
    constexpr auto name () noexcept -> String & { return this->_name; }

    virtual auto load () noexcept -> File & = 0;
    virtual auto save () noexcept -> File & = 0;

    [[nodiscard]] constexpr auto isDirectory () const noexcept -> bool { return (bool)(this->_flags & FileFlag::DIRECTORY); }
    [[nodiscard]] constexpr auto isExecutable () const noexcept -> bool { return (bool)(this->_flags & FileFlag::EXECUTABLE); }
    [[nodiscard]] constexpr auto isReadable () const noexcept -> bool { return (bool)(this->_flags & FileFlag::READABLE); }
    [[nodiscard]] constexpr auto isWritable () const noexcept -> bool { return (bool)(this->_flags & FileFlag::WRITABLE); }

protected:
    enum LoadFlag : CDS_uint8 {
        NO_LOAD_FLAGS   = 0x00u,
        LOAD_RECURSIVE  = 0x01u
    };

    typedef CDS_uint8 LoadFlags;

#if defined(WIN32)
#elif defined(__linux)
    auto static linuxLoadFile(dirent64 const *, LoadFlags = LoadFlag::NO_LOAD_FLAGS) noexcept -> File *;
#else
#error Error: File Static Loading Unsupported
#endif
};

class File::Directory : public File {
private:
    friend class File;

#if defined(WIN32)
#elif defined(__linux)

    Directory ( dirent64 const * pPlatformImplementationStructure ) noexcept;

#else
#error Error: File::Directory::Directory (PlatformImplementationStructure) unsupported
#endif

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
#error Error : File::Directory Construction Unsupported
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
#error Error: File::Directory::open Unsupported
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
#error Error: File::Directory::close Unsupported
#endif

        return * this;
    }

    [[nodiscard]] constexpr auto isOpen () const noexcept -> bool {
#if defined(WIN32)
        return false;
#elif defined(__linux)
        return this->platformDirectoryHandle != nullptr;
#else
#error Error: File::Directory::isOpen Unsupported
#endif
    }

    auto load() noexcept -> File::Directory & override {

#if defined(WIN32)
#elif defined(__linux)
        dirent64 * pEntry = readdir64( this->platformDirectoryHandle );

        while ( pEntry != nullptr ) {
            this->_entries.pushBack(File::linuxLoadFile(pEntry));

            pEntry = readdir64( this->platformDirectoryHandle );
        }
#else
#error Error: File::Directory::load Unsupported
#endif

        return * this;
    }

    auto save () noexcept -> File::Directory & override {
        return * this;
    }
};

#if defined(__linux)
inline auto File::linuxLoadFile(const dirent64 * pEntry, LoadFlags loadFlags) noexcept -> File * {
    switch ( pEntry->d_type ) {
        case DT_BLK:        return nullptr;
        case DT_CHR:        return nullptr;
        case DT_DIR:        return new Directory(pEntry);
        case DT_LNK:        return nullptr;
        case DT_REG:        return nullptr;
        case DT_SOCK:       return nullptr;
        case DT_FIFO:       return nullptr;
        case DT_UNKNOWN:    return nullptr;
    }

    return nullptr;
}
#endif

#endif //CDS_FILE_HPP
