//
// Created by loghin on 10.05.2021.
//

#ifndef CDS_FILE_HPP
#define CDS_FILE_HPP

#include <CDS/Object>
#include <CDS/LinkedList>
#include <CDS/Path>
#include <CDS/HashMap>

#if defined(__linux)
#include <sys/stat.h>
#endif

class File : public Object {
public:

#if defined(__linux)

// region Linux Type Declarations + Definitions

//region Linux File Type Declarations + Definitions
    enum PlatformTypeFlag : CDS_uint8 {
        PTF_NULL_FILE           = 0x00u,
        PTF_REGULAR             = 0x01u,
        PTF_DIRECTORY           = 0x02u,
        PTF_CHARACTER_DEVICE    = 0x04u,
        PTF_BLOCK_DEVICE        = 0x08u,
        PTF_FIFO                = 0x10u,
        PTF_SYMBOLIC_LINK       = 0x20u,
        PTF_SOCKET              = 0x40u,

        PTF_MIN_VALUE           = PTF_REGULAR,
        PTF_MAX_VALUE           = PTF_SOCKET
    };

    constexpr static auto platformFileTypeFlagToString (PlatformTypeFlag f) noexcept -> StringLiteral {
        switch (f) {
            case PTF_NULL_FILE:         return "No Flags";
            case PTF_REGULAR:           return "Regular File";
            case PTF_DIRECTORY:         return "Directory";
            case PTF_CHARACTER_DEVICE:  return "Character Device";
            case PTF_BLOCK_DEVICE:      return "Block Device";
            case PTF_FIFO:              return "FIFO";
            case PTF_SYMBOLIC_LINK:     return "Symbolic Link";
            case PTF_SOCKET:            return "Socket";

            default:
                break;
        }

        return "Undefined";
    }

    using PlatformTypeFlags = CDS_uint8;

    static auto platformTypeFlagsToString ( PlatformTypeFlags ) noexcept -> String;
    static auto platformTypeFlagsToStringList ( PlatformTypeFlags ) noexcept -> LinkedList < String >;
    static auto platformTypeFlagsToList ( PlatformTypeFlags ) noexcept -> LinkedList < PlatformTypeFlag >;

    static auto platformFileType(struct stat64 const *) noexcept -> PlatformTypeFlags;
    static auto platformFileType(Path const &) noexcept -> PlatformTypeFlags;

// endregion

// region Linux Permission Flag Declarations + Definitions
    enum PlatformPermissionFlag : CDS_uint8 {
        PPF_NULL        = 0x00u,
        PPF_EXECUTE     = 0x01u,
        PPF_WRITE       = 0x02u,
        PPF_READ        = 0x04u,

        PPF_MIN_VALUE   = PPF_EXECUTE,
        PPF_MAX_VALUE   = PPF_READ
    };

    constexpr static auto platformPermissionFlagToString ( PlatformPermissionFlag f ) noexcept -> StringLiteral {
        switch ( f ) {
            case PPF_NULL:       return "No Permissions";
            case PPF_EXECUTE:    return "Execute";
            case PPF_WRITE:      return "Write";
            case PPF_READ:       return "Read";
            default:
                break;
        }

        return "Undefined";
    }

    using PlatformPermissionFlags = CDS_uint8;

    static auto platformPermissionFlagsToString ( PlatformPermissionFlags ) noexcept -> String;
    static auto platformPermissionFlagsToStringList ( PlatformPermissionFlags ) noexcept -> LinkedList < String >;
    static auto platformPermissionFlagsToList ( PlatformPermissionFlags ) noexcept -> LinkedList < PlatformPermissionFlag >;

// endregion

// region Linux User Flag Declarations + Definitions

    enum PlatformUserFlag : CDS_uint8 {
        PUF_NO_USER             = 0x00u,
        PUF_USER                = 0x01u,
        PUF_GROUP               = 0x02u,
        PUF_OTHER               = 0x04u,

        PUF_MIN_VALUE           = PUF_USER,
        PUF_MAX_VALUE           = PUF_OTHER,

        PUF_POLICY_MATCH_ONE    = PUF_NO_USER, // reason : when checking, check what can user do from user/group/other on the file, best is chosen
        PUF_POLICY_MATCH_ALL    = 0x20u
    };

    constexpr static auto platformUserFlagToString ( PlatformUserFlag f ) noexcept -> StringLiteral {
        switch ( f ) {
            case PUF_NO_USER:   return "No User";
            case PUF_USER:      return "Current User";
            case PUF_GROUP:     return "Group";
            case PUF_OTHER:     return "Others";
            default:
                break;
        }

        return "Undefined";
    }

    using PlatformUserFlags = CDS_uint8;

    static auto platformUserFlagsToString ( PlatformUserFlags ) noexcept -> String;
    static auto platformUserFlagsToStringList ( PlatformUserFlags ) noexcept -> LinkedList < String >;
    static auto platformUserFlagsToList ( PlatformUserFlags ) noexcept -> LinkedList < PlatformUserFlag >;

// endregion

    static auto platformPermissions ( Path const &, PlatformUserFlags = PUF_USER | PUF_POLICY_MATCH_ONE ) noexcept -> PlatformPermissionFlags;
    static auto platformPermissionsGrouped ( Path const & ) noexcept -> HashMap < PlatformUserFlag, PlatformPermissionFlags >;
    static auto platformPermissions ( struct stat64 const *, PlatformUserFlags = PUF_USER | PUF_POLICY_MATCH_ONE ) noexcept -> PlatformPermissionFlags;
    static auto platformPermissionsGrouped ( struct stat64 const * ) noexcept -> HashMap < PlatformUserFlag, PlatformPermissionFlags >;

// endregion

#endif

    enum TypeFlag : CDS_uint8 {
        TF_NULL_FILE            = PlatformTypeFlag::PTF_NULL_FILE,
        TF_REGULAR              = PlatformTypeFlag::PTF_REGULAR,
        TF_DIRECTORY            = PlatformTypeFlag::PTF_DIRECTORY
    };

    using TypeFlags = PlatformTypeFlags;

    enum PermissionFlag : CDS_uint8 {
        PF_NULL      = PlatformPermissionFlag::PPF_NULL,
        PF_EXECUTE   = PlatformPermissionFlag::PPF_EXECUTE,
        PF_WRITE     = PlatformPermissionFlag::PPF_WRITE,
        PF_READ      = PlatformPermissionFlag::PPF_READ
    };

    using PermissionFlags = PlatformPermissionFlags;

protected:

#if defined(__linux)

    struct stat64 _linuxFileData;

#endif

    Path _path;

    explicit File ( Path const & p ) noexcept : _path(p) {
        this->reload();
    }

    virtual auto reload () noexcept -> File & {

#if defined(__linux)
        lstat64(this->_path.toString().cStr(), & this->_linuxFileData);
#endif

        return * this;
    }

public:
    [[nodiscard]] auto toString () const noexcept -> String override { return ""; }

#if defined(__linux)

    constexpr auto linuxFileInformation () const noexcept -> struct stat64 const & { return this->_linuxFileData; }
    constexpr auto linuxDeviceID () const noexcept -> __dev_t { return this->_linuxFileData.st_dev; }
    constexpr auto linuxINode () const noexcept -> __ino64_t { return this->_linuxFileData.st_ino; }
    inline auto linuxFileType () const noexcept -> PlatformTypeFlags { return File::platformFileType(& this->_linuxFileData); }
    inline auto linuxPermissions () const noexcept -> PlatformPermissionFlags { return File::platformPermissions(& this->_linuxFileData); }
    constexpr auto linuxModeFlags () const noexcept -> __mode_t { return this->_linuxFileData.st_mode; }
    constexpr auto linuxHardLinkCount () const noexcept -> __nlink_t { return this->_linuxFileData.st_nlink; }
    constexpr auto linuxOwnerUserID () const noexcept -> __uid_t { return this->_linuxFileData.st_uid; }
    constexpr auto linuxOwnerGroupID () const noexcept -> __gid_t { return this->_linuxFileData.st_gid; }
    constexpr auto linuxSpecialFileDeviceID () const noexcept -> __dev_t { return this->_linuxFileData.st_rdev; }
    constexpr auto linuxTotalSize () const noexcept -> __off_t { return this->_linuxFileData.st_size; }
    constexpr auto linuxBlockSize () const noexcept -> __blksize_t { return this->_linuxFileData.st_blksize; }
    constexpr auto linuxBlockCount () const noexcept -> __blkcnt64_t { return this->_linuxFileData.st_blocks; }
    constexpr auto linuxLastAccess () const noexcept -> struct timespec const & { return this->_linuxFileData.st_atim; };
    constexpr auto linuxLastModification () const noexcept -> struct timespec const & { return this->_linuxFileData.st_mtim; };
    constexpr auto linuxLastStatusChange () const noexcept -> struct timespec const & { return this->_linuxFileData.st_ctim; };

    inline auto isLinuxRegularFile () const noexcept -> bool { return this->linuxFileType() & PTF_REGULAR;  }
    inline auto isLinuxDirectory () const noexcept -> bool { return this->linuxFileType() & PTF_DIRECTORY; }
    inline auto isLinuxCharacterDevice () const noexcept -> bool { return this->linuxFileType() & PTF_CHARACTER_DEVICE; }
    inline auto isLinuxBlockDevice () const noexcept -> bool { return this->linuxFileType() & PTF_BLOCK_DEVICE; }
    inline auto isLinuxFIFO () const noexcept -> bool { return this->linuxFileType() & PTF_FIFO; }
    inline auto isLinuxSymbolicLink () const noexcept -> bool { return this->linuxFileType() & PTF_SYMBOLIC_LINK; }
    inline auto isLinuxSocket () const noexcept -> bool { return this->linuxFileType() & PTF_SOCKET; }

#endif

#if defined(__linux)

    class LinuxRegular;
    class LinuxDirectory;
    class LinuxCharacterDevice;
    class LinuxBlockDevice;
    class LinuxFIFO;
    class LinuxSymbolicLink;
    class LinuxSocket;

#endif

    class InvalidFileType : public std::exception {
    private:
        String _message;

    public:
        InvalidFileType (PlatformTypeFlags requested, PlatformTypeFlags actual) noexcept : std::exception() {
            this->_message =
                    String("Invalid File Type. Requested : ") +
                    File::platformTypeFlagsToString(requested) +
                    ", Actual : " +
                    File::platformTypeFlagsToString(actual);
        }

        [[nodiscard]] auto what () const noexcept -> StringLiteral override {
            return this->_message.cStr();
        }
    };

    virtual ~File () noexcept = default;

    [[nodiscard]] constexpr auto path () const noexcept -> Path const & { return this->_path; }
    [[nodiscard]] constexpr auto path () noexcept -> Path & { return this->_path; }
};

#if defined(__linux)

// region Linux Platform Flags Impl.

// region Linux Platform File Type Impl.

inline auto File::platformTypeFlagsToString ( File::PlatformTypeFlags flags ) noexcept -> String {
    String rep = "";

    for ( CDS_uint8 f = PTF_MIN_VALUE; f <= PTF_MAX_VALUE; f <<= 1u )
        if ( f & flags )
            rep += String(File::platformFileTypeFlagToString ( static_cast < PlatformTypeFlag > (f) )) + ", ";

    return rep.rtrim(", ");
}

inline auto File::platformTypeFlagsToStringList ( File::PlatformTypeFlags flags ) noexcept -> LinkedList < String > {
    LinkedList < String > l;

    for ( CDS_uint8 f = PTF_MIN_VALUE; f <= PTF_MAX_VALUE; f <<= 1u )
        if ( f & flags )
            l.pushBack ( File::platformFileTypeFlagToString ( static_cast < File::PlatformTypeFlag > (f) ) );

    return l;
}

inline auto File::platformTypeFlagsToList ( File::PlatformTypeFlags flags ) noexcept -> LinkedList < File::PlatformTypeFlag > {
    LinkedList < File::PlatformTypeFlag > l;

    for ( CDS_uint8 f = PTF_MIN_VALUE; f <= PTF_MAX_VALUE; f <<= 1u )
        if ( f & flags )
            l.pushBack ( static_cast < File::PlatformTypeFlag > (f) );

    return l;
}

inline auto File::platformFileType(Path const & p) noexcept -> PlatformTypeFlags {
    struct stat64 st;
    lstat64(p.toString().cStr(), & st);

    return File::platformFileType(& st);
}

inline auto File::platformFileType(struct stat64 const * st) noexcept -> PlatformTypeFlags {
    PlatformTypeFlags flags = PTF_NULL_FILE;

    if ( S_ISREG(st->st_mode) )     flags |= PTF_REGULAR;
    if ( S_ISDIR(st->st_mode) )     flags |= PTF_DIRECTORY;
    if ( S_ISCHR(st->st_mode) )     flags |= PTF_CHARACTER_DEVICE;
    if ( S_ISBLK(st->st_mode) )     flags |= PTF_BLOCK_DEVICE;
    if ( S_ISFIFO(st->st_mode) )    flags |= PTF_FIFO;
    if ( S_ISLNK(st->st_mode) )     flags |= PTF_SYMBOLIC_LINK;
    if ( S_ISSOCK(st->st_mode) )    flags |= PTF_SOCKET;

    return flags;
}

// endregion

// region Linux Platform Permission Flags Impl.

inline auto File::platformPermissionFlagsToString ( PlatformPermissionFlags flags ) noexcept -> String {
    String rep = "";

    for ( CDS_uint8 f = PPF_MIN_VALUE; f <= PPF_MAX_VALUE; f <<= 1u )
        if ( f & flags )
            rep += String(File::platformPermissionFlagToString ( static_cast < PlatformPermissionFlag > (f) )) + ", ";

    return rep.rtrim(", ");
}

inline auto File::platformPermissionFlagsToStringList ( PlatformPermissionFlags flags ) noexcept -> LinkedList < String > {
    LinkedList < String > l;

    for ( CDS_uint8 f = PPF_MIN_VALUE; f <= PPF_MAX_VALUE; f <<= 1u )
        if ( f & flags )
            l.pushBack(File::platformPermissionFlagToString ( static_cast < PlatformPermissionFlag > (f) ));

    return l;
}

inline auto File::platformPermissionFlagsToList ( PlatformPermissionFlags flags ) noexcept -> LinkedList < PlatformPermissionFlag > {
    LinkedList < PlatformPermissionFlag > l;

    for ( CDS_uint8 f = PPF_MIN_VALUE; f <= PPF_MAX_VALUE; f <<= 1u )
        if ( f & flags )
            l.pushBack( static_cast < PlatformPermissionFlag > (f) );

    return l;
}

// endregion

// region Linux Platform User Flags Impl.

inline auto File::platformUserFlagsToString ( PlatformUserFlags flags ) noexcept -> String {
    String rep = "";

    for ( CDS_uint8 f = PUF_MIN_VALUE; f <= PUF_MAX_VALUE; f <<= 1u )
        if ( f & flags )
            rep += String(File::platformUserFlagToString ( static_cast < PlatformUserFlag > (f) )) + ", ";

    return rep.rtrim(", ");
}

inline auto File::platformUserFlagsToStringList ( PlatformUserFlags flags ) noexcept -> LinkedList < String > {
    LinkedList < String > l;

    for ( CDS_uint8 f = PUF_MIN_VALUE; f <= PUF_MAX_VALUE; f <<= 1u )
        if ( f & flags )
            l.append(File::platformUserFlagToString ( static_cast < PlatformUserFlag > (f) ));

    return l;
}

inline auto File::platformUserFlagsToList ( PlatformUserFlags flags ) noexcept -> LinkedList < PlatformUserFlag > {
    LinkedList < PlatformUserFlag > l;

    for ( CDS_uint8 f = PUF_MIN_VALUE; f <= PUF_MAX_VALUE; f <<= 1u )
        if ( f & flags )
            l.append( static_cast < PlatformUserFlag > (f) );

    return l;
}

// endregion

// region Linux Platform Permissions Impl.

inline auto File::platformPermissions ( Path const & path, PlatformUserFlags flags ) noexcept -> PlatformPermissionFlags {
    struct stat64 st;
    lstat64 ( path.toString().cStr(), & st );
    return File::platformPermissions ( &st, flags );
}

inline auto File::platformPermissionsGrouped ( Path const & path ) noexcept -> HashMap < PlatformUserFlag, PlatformPermissionFlags > {
    struct stat64 st;
    lstat64 ( path.toString().cStr(), & st );
    return File::platformPermissionsGrouped ( & st );
}

inline auto File::platformPermissions (
        struct stat64 const * pStat,
        PlatformUserFlags flags
) noexcept -> PlatformPermissionFlags {
    if ( flags & PUF_POLICY_MATCH_ALL ) {
        PlatformPermissionFlags permissionFlags = UINT8_MAX;
        constexpr static PlatformPermissionFlags mask =
                PlatformPermissionFlag::PPF_READ       |
                PlatformPermissionFlag::PPF_WRITE      |
                PlatformPermissionFlag::PPF_EXECUTE;

        if (flags & PlatformUserFlag::PUF_USER) {
            if (pStat->st_mode & S_IRUSR) permissionFlags &= ~PlatformPermissionFlag::PPF_READ;
            if (pStat->st_mode & S_IWUSR) permissionFlags &= ~PlatformPermissionFlag::PPF_WRITE;
            if (pStat->st_mode & S_IXUSR) permissionFlags &= ~PlatformPermissionFlag::PPF_EXECUTE;
        }

        if (flags & PlatformUserFlag::PUF_GROUP) {
            if (pStat->st_mode & S_IRGRP) permissionFlags &= ~PlatformPermissionFlag::PPF_READ;
            if (pStat->st_mode & S_IWGRP) permissionFlags &= ~PlatformPermissionFlag::PPF_WRITE;
            if (pStat->st_mode & S_IXGRP) permissionFlags &= ~PlatformPermissionFlag::PPF_EXECUTE;
        }

        if (flags & PlatformUserFlag::PUF_OTHER) {
            if (pStat->st_mode & S_IROTH) permissionFlags &= ~PlatformPermissionFlag::PPF_READ;
            if (pStat->st_mode & S_IWOTH) permissionFlags &= ~PlatformPermissionFlag::PPF_WRITE;
            if (pStat->st_mode & S_IXOTH) permissionFlags &= ~PlatformPermissionFlag::PPF_EXECUTE;
        }

        return permissionFlags & mask;
    } else {
        PlatformPermissionFlags permissionFlags = PPF_NULL;

        if (flags & PlatformUserFlag::PUF_USER) {
            if (pStat->st_mode & S_IRUSR) permissionFlags |= PlatformPermissionFlag::PPF_READ;
            if (pStat->st_mode & S_IWUSR) permissionFlags |= PlatformPermissionFlag::PPF_WRITE;
            if (pStat->st_mode & S_IXUSR) permissionFlags |= PlatformPermissionFlag::PPF_EXECUTE;
        }

        if (flags & PlatformUserFlag::PUF_GROUP) {
            if (pStat->st_mode & S_IRGRP) permissionFlags |= PlatformPermissionFlag::PPF_READ;
            if (pStat->st_mode & S_IWGRP) permissionFlags |= PlatformPermissionFlag::PPF_WRITE;
            if (pStat->st_mode & S_IXGRP) permissionFlags |= PlatformPermissionFlag::PPF_EXECUTE;
        }

        if (flags & PlatformUserFlag::PUF_OTHER) {
            if (pStat->st_mode & S_IROTH) permissionFlags |= PlatformPermissionFlag::PPF_READ;
            if (pStat->st_mode & S_IWOTH) permissionFlags |= PlatformPermissionFlag::PPF_WRITE;
            if (pStat->st_mode & S_IXOTH) permissionFlags |= PlatformPermissionFlag::PPF_EXECUTE;
        }

        return permissionFlags;
    }
}


inline auto File::platformPermissionsGrouped (
        struct stat64 const * pStat
) noexcept -> HashMap < PlatformUserFlag, PlatformPermissionFlags > {
    HashMap < PlatformUserFlag, PlatformPermissionFlags > permissions = {
            { PUF_USER, PPF_NULL },
            { PUF_GROUP, PPF_NULL },
            { PUF_OTHER, PPF_NULL }
    };

    if ( pStat->st_mode & S_IRUSR ) permissions [ PUF_USER ] |= PPF_READ;
    if ( pStat->st_mode & S_IWUSR ) permissions [ PUF_USER ] |= PPF_WRITE;
    if ( pStat->st_mode & S_IXUSR ) permissions [ PUF_USER ] |= PPF_EXECUTE;

    if ( pStat->st_mode & S_IRGRP ) permissions [ PUF_GROUP ] |= PPF_READ;
    if ( pStat->st_mode & S_IWGRP ) permissions [ PUF_GROUP ] |= PPF_WRITE;
    if ( pStat->st_mode & S_IXGRP ) permissions [ PUF_GROUP ] |= PPF_EXECUTE;

    if ( pStat->st_mode & S_IROTH ) permissions [ PUF_OTHER ] |= PPF_READ;
    if ( pStat->st_mode & S_IWOTH ) permissions [ PUF_OTHER ] |= PPF_WRITE;
    if ( pStat->st_mode & S_IXOTH ) permissions [ PUF_OTHER ] |= PPF_EXECUTE;

    return permissions;
}

// endregion

// endregion

#endif

#if defined(__linux)

class File::LinuxRegular : public File {
public:
    explicit LinuxRegular (Path const & path) noexcept (false) : File (path) {
        if ( ! this->isLinuxRegularFile () )
            throw InvalidFileType ( PTF_REGULAR, this->linuxFileType() );
    }

    ~LinuxRegular () noexcept override = default;
};

class File::LinuxDirectory : public File {
public:
    explicit LinuxDirectory (Path const & path) noexcept (false) : File (path) {
        if ( ! this->isLinuxDirectory () )
            throw InvalidFileType ( PTF_DIRECTORY, this->linuxFileType() );
    }

    ~LinuxDirectory () noexcept override = default;
};

class File::LinuxCharacterDevice : public File {
public:
    explicit LinuxCharacterDevice (Path const & path) noexcept (false) : File (path) {
        if ( ! this->isLinuxCharacterDevice () )
            throw InvalidFileType ( PTF_CHARACTER_DEVICE, this->linuxFileType() );
#warning Warning : Linux Character Device Partial Support
    }

    ~LinuxCharacterDevice () noexcept override = default;
};

class File::LinuxBlockDevice : public File {
public:
    explicit LinuxBlockDevice (Path const & path) noexcept (false) : File (path) {
        if ( ! this->isLinuxBlockDevice () )
            throw InvalidFileType ( PTF_BLOCK_DEVICE, this->linuxFileType () );
#warning Warning : Linux Block Device Partial Support
    }

    ~LinuxBlockDevice () noexcept override = default;
};

class File::LinuxFIFO : public File {
public:
    explicit LinuxFIFO (Path const & path) noexcept (false) : File (path) {
        if ( ! this->isLinuxFIFO() )
            throw InvalidFileType ( PTF_FIFO, this->linuxFileType() );
    }

    ~LinuxFIFO () noexcept override = default;
};

class File::LinuxSymbolicLink : public File {
public:
    explicit LinuxSymbolicLink (Path const & path) noexcept (false) : File (path) {
        if ( ! this->isLinuxSymbolicLink () )
            throw InvalidFileType ( PTF_SYMBOLIC_LINK, this->linuxFileType () );
    }

    ~LinuxSymbolicLink () noexcept override = default;
};

class File::LinuxSocket : public File {
public:
    explicit LinuxSocket (Path const & path) noexcept (false) : File (path) {
        if ( ! this->isLinuxSocket () )
            throw InvalidFileType ( PTF_SOCKET, this->linuxFileType () );
    }

    ~LinuxSocket () noexcept override = default;
};

#endif

#endif //CDS_FILE_HPP
