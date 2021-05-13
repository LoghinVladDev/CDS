//
// Created by loghin on 10.05.2021.
//

#ifndef CDS_FILE_HPP
#define CDS_FILE_HPP

#include <CDS/Object>
#include <CDS/LinkedList>
#include <CDS/Path>

#if defined(__linux)
#include <sys/stat.h>
#endif

class File : public Object {
public:

#if defined(__linux)

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

    static auto platformFileTypeFlagsToString ( PlatformTypeFlags ) noexcept -> String;
    static auto platformFileTypeFlagsToStringList ( PlatformTypeFlags ) noexcept -> LinkedList < String >;
    static auto platformFileTypeFlagsToList ( PlatformTypeFlags ) noexcept -> LinkedList < PlatformTypeFlag >;

    static auto platformFileType(struct stat64 const *) noexcept -> PlatformTypeFlags;
    static auto platformFileType(Path const &) noexcept -> PlatformTypeFlags;

//endregion

    enum PlatformProtectionFlag : CDS_uint8 {
        PPF_NULL_PERMISSION     = 0x00u,
        PPF_EXECUTE_PERMISSION  = 0x01u,
        PPF_WRITE_PERMISSION    = 0x02u,
        PPF_READ_PERMISSION     = 0x04u,

        PPF_MAX_VALUE           = PPF_READ_PERMISSION
    };

    constexpr static auto platformProtectionFlagToString ( PlatformProtectionFlag f ) noexcept -> StringLiteral {
        switch ( f ) {
            case PPF_NULL_PERMISSION:       return "No Permissions";
            case PPF_EXECUTE_PERMISSION:    return "Execute";
            case PPF_WRITE_PERMISSION:      return "Write";
            case PPF_READ_PERMISSION:       return "Read";
            default:
                break;
        }

        return "Undefined";
    }

    using PlatformProtectionFlags = CDS_uint8;

    static auto platformProtectionFlagsToString ( PlatformProtectionFlags ) noexcept -> String;
    static auto platformProtectionFlagsToStringList ( PlatformProtectionFlags ) noexcept -> LinkedList < String >;
    static auto platformProtectionFlagsToList ( PlatformProtectionFlags ) noexcept -> LinkedList < PlatformProtectionFlag >;

    enum PlatformUserFlag : CDS_uint8 {
        PUF_NO_USER             = 0x00u,
        PUF_USER                = 0x01u,
        PUF_GROUP               = 0x02u,
        PUF_OTHER               = 0x04u,

        PUF_MAX_VALUE           = PUF_OTHER
    };

    using PlatformUserFlags = CDS_uint8;

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

#endif

    enum TypeFlag : CDS_uint8 {
        TF_NULL_FILE            = PlatformTypeFlag::PTF_NULL_FILE,
        TF_REGULAR              = PlatformTypeFlag::PTF_REGULAR,
        TF_DIRECTORY            = PlatformTypeFlag::PTF_DIRECTORY
    };

    using TypeFlags = PlatformTypeFlags;

    enum ProtectionFlag : CDS_uint8 {
        PF_NULL_PERMISSION      = PlatformProtectionFlag::PPF_NULL_PERMISSION,
        PF_EXECUTE_PERMISSION   = PlatformProtectionFlag::PPF_EXECUTE_PERMISSION,
        PF_WRITE_PERMISSION     = PlatformProtectionFlag::PPF_WRITE_PERMISSION,
        PF_READ_PERMISSION      = PlatformProtectionFlag::PPF_READ_PERMISSION
    };

    using ProtectionFlags = PlatformProtectionFlags;

protected:

public:
    [[nodiscard]] auto toString () const noexcept -> String override { return ""; }
};

#if defined(__linux)

inline auto File::platformFileTypeFlagsToString ( File::PlatformTypeFlags flags ) noexcept -> String {
    String rep = "";

    for ( CDS_uint8 f = PTF_REGULAR; f <= PTF_MAX_VALUE; f <<= 1u ) {
        if ( f & flags )
            rep += String(File::platformFileTypeFlagToString ( static_cast < PlatformTypeFlag > (f) )) + ", ";
    }

    return rep.rtrim(", ");
}

inline auto File::platformFileTypeFlagsToStringList ( File::PlatformTypeFlags flags ) noexcept -> LinkedList < String > {
    LinkedList < String > l;

    for ( CDS_uint8 f = PTF_REGULAR; f <= PTF_MAX_VALUE; f <<= 1u ) {
        if ( f & flags )
            l.pushBack ( File::platformFileTypeFlagToString ( static_cast < File::PlatformTypeFlag > (f) ) );
    }

    return l;
}

inline auto File::platformFileTypeFlagsToList ( File::PlatformTypeFlags flags ) noexcept -> LinkedList < File::PlatformTypeFlag > {
    LinkedList < File::PlatformTypeFlag > l;

    for ( CDS_uint8 f = PTF_REGULAR; f <= PTF_MAX_VALUE; f <<= 1u ) {
        if ( f & flags )
            l.pushBack ( static_cast < File::PlatformTypeFlag > (f) );
    }

    return l;
}

inline auto File::platformFileType(Path const & p) noexcept -> PlatformTypeFlags {
    struct stat64 st;
    lstat64(p.toString().cStr(), & st);

    return File::platformFileType(& st);
}

inline auto File::platformFileType(struct stat64 const * st) noexcept -> PlatformTypeFlags {
    PlatformTypeFlags flags = PTF_NULL_FILE;

    if ( S_ISREG(st->st_mode) ) flags |= PTF_REGULAR;
    if ( S_ISDIR(st->st_mode) ) flags |= PTF_DIRECTORY;
    if ( S_ISCHR(st->st_mode) ) flags |= PTF_CHARACTER_DEVICE;
    if ( S_ISBLK(st->st_mode) ) flags |= PTF_BLOCK_DEVICE;
    if ( S_ISFIFO(st->st_mode) ) flags |= PTF_FIFO;
    if ( S_ISLNK(st->st_mode) ) flags |= PTF_SYMBOLIC_LINK;
    if ( S_ISSOCK(st->st_mode) ) flags |= PTF_SOCKET;

    return flags;
}

#endif

#endif //CDS_FILE_HPP
