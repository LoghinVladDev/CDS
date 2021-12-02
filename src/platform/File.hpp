//
// Created by loghin on 10.05.2021.
//

#ifndef CDS_FILE_HPP
#define CDS_FILE_HPP

//#warning Warning: Library Functions Unstable

#include <CDS/Object>
#include <CDS/LinkedList>
#include <CDS/Path>
#include <CDS/HashMap>
#include <CDS/Pointer>
#include <CDS/Memory>

#if defined(__linux)
#include <sys/stat.h>
#include <ctime>
#endif

namespace cds {

    class File : public Object {
    public:

    #if defined(__linux)

    // region Linux Type Declarations + Definitions

    // region Linux File Type Declarations + Definitions
        enum PlatformTypeFlag : uint8 {
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

        __CDS_cpplang_ConstexprConditioned static auto platformFileTypeFlagToString (PlatformTypeFlag f) noexcept -> StringLiteral {
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

        using PlatformTypeFlags = uint8;

        static auto platformTypeFlagsToString ( PlatformTypeFlags ) noexcept -> String;
        __CDS_MaybeUnused static auto platformTypeFlagsToStringList ( PlatformTypeFlags ) noexcept -> LinkedList < String >;
        __CDS_MaybeUnused static auto platformTypeFlagsToList ( PlatformTypeFlags ) noexcept -> LinkedList < PlatformTypeFlag >;

        static auto platformFileType(struct stat64 const *) noexcept -> PlatformTypeFlags;
        static auto platformFileType(Path const &) noexcept -> PlatformTypeFlags;

    // endregion

    // region Linux Permission Flag Declarations + Definitions
        enum PlatformPermissionFlag : uint8 {
            PPF_NULL        = 0x00u,
            PPF_EXECUTE     = 0x01u,
            PPF_WRITE       = 0x02u,
            PPF_READ        = 0x04u,

            PPF_MIN_VALUE   = PPF_EXECUTE,
            PPF_MAX_VALUE   = PPF_READ
        };

        __CDS_cpplang_ConstexprConditioned static auto platformPermissionFlagToString ( PlatformPermissionFlag f ) noexcept -> StringLiteral {
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

        using PlatformPermissionFlags = uint8;

        __CDS_MaybeUnused static auto platformPermissionFlagsToString ( PlatformPermissionFlags ) noexcept -> String;
        static auto platformPermissionFlagsToStringList ( PlatformPermissionFlags ) noexcept -> LinkedList < String >;
        __CDS_MaybeUnused static auto platformPermissionFlagsToList ( PlatformPermissionFlags ) noexcept -> LinkedList < PlatformPermissionFlag >;

    // endregion

    // region Linux User Flag Declarations + Definitions

        enum PlatformUserFlag : uint8 {
            PUF_NO_USER             = 0x00u,
            PUF_USER                = 0x01u,
            PUF_GROUP               = 0x02u,
            PUF_OTHER               = 0x04u,

            PUF_MIN_VALUE           = PUF_USER,
            PUF_MAX_VALUE           = PUF_OTHER,

            PUF_POLICY_MATCH_ONE    = PUF_NO_USER, // reason : when checking, check what can user do from user/group/other on the file, best is chosen
            PUF_POLICY_MATCH_ALL    = 0x20u
        };

        __CDS_cpplang_ConstexprConditioned static auto platformUserFlagToString ( PlatformUserFlag f ) noexcept -> StringLiteral {
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

        using PlatformUserFlags = uint8;

        static auto platformUserFlagsToString ( PlatformUserFlags ) noexcept -> String;
        __CDS_MaybeUnused static auto platformUserFlagsToStringList ( PlatformUserFlags ) noexcept -> LinkedList < String >;
        __CDS_MaybeUnused static auto platformUserFlagsToList ( PlatformUserFlags ) noexcept -> LinkedList < PlatformUserFlag >;

    // endregion

        __CDS_MaybeUnused static auto platformPermissions ( Path const &, PlatformUserFlags = PUF_USER | PUF_POLICY_MATCH_ONE ) noexcept -> PlatformPermissionFlags;
        __CDS_MaybeUnused static auto platformPermissionsGrouped ( Path const & ) noexcept -> HashMap < PlatformUserFlag, PlatformPermissionFlags >;
        static auto platformPermissions ( struct stat64 const *, PlatformUserFlags = PUF_USER | PUF_POLICY_MATCH_ONE ) noexcept -> PlatformPermissionFlags;
        static auto platformPermissionsGrouped ( struct stat64 const * ) noexcept -> HashMap < PlatformUserFlag, PlatformPermissionFlags >;

    // endregion

    #endif

        // region platform independent file flags

        enum TypeFlag : uint8 {
            TF_NULL_FILE            = PlatformTypeFlag::PTF_NULL_FILE,
            TF_REGULAR              = PlatformTypeFlag::PTF_REGULAR,
            TF_DIRECTORY            = PlatformTypeFlag::PTF_DIRECTORY
        };

        using TypeFlags __CDS_MaybeUnused = PlatformTypeFlags;

        enum PermissionFlag : uint8 {
            PF_NULL      = PlatformPermissionFlag::PPF_NULL,
            PF_EXECUTE   = PlatformPermissionFlag::PPF_EXECUTE,
            PF_WRITE     = PlatformPermissionFlag::PPF_WRITE,
            PF_READ      = PlatformPermissionFlag::PPF_READ
        };

        using PermissionFlags __CDS_MaybeUnused = PlatformPermissionFlags;

        // endregion

        // region diagnostic data types

        enum DiagnosticLogLevel : uint8 {
            DLL_NONE     = 0x00u,
            DLL_ERROR    = 0x01u,
            DLL_WARNING  = 0x02u,
            DLL_INFO     = 0x03u,

            DLL_ALL      = DLL_INFO
        };

        enum DiagnosticOptionFlag : uint16 {
            DO_NO_AUTOMATIC_FIXES       = 0x0000u,
            DO_BASIC_AUTOMATIC_FIXES    = 0x0001u,
            DO_COMPLEX_AUTOMATIC_FIXES  = 0x0002u,

            DO_BROKEN_SYMBOLIC_LINKS    = 0x0004u
        };

        using DiagnosticOptionFlags = uint16;

        __CDS_cpplang_ConstexprConditioned static auto diagnosticLogLevelToString (DiagnosticLogLevel l) noexcept -> StringLiteral {
            switch (l) {
                case DLL_NONE:      return "None";
                case DLL_ERROR:     return "Error";
                case DLL_WARNING:   return "Warning";
                case DLL_INFO:      return "Info";
            }

            return "Undefined";
        }

        // endregions

    protected:

        // region diagnostic variables

    #if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_17

        static std::ostream *           _diagnosticOutput;

        static DiagnosticLogLevel       _diagnosticLogLevel;
        static DiagnosticOptionFlags    _diagnosticFixesFlags;

    #else

        std::ostream *           _diagnosticOutput {& std::cerr};

        DiagnosticLogLevel       _diagnosticLogLevel {File::DiagnosticLogLevel::DLL_ALL};
        DiagnosticOptionFlags    _diagnosticFixesFlags {File::DiagnosticOptionFlag::DO_NO_AUTOMATIC_FIXES};

    #endif


        // endregion

        // region linux variables

    #if defined(__linux)

        struct stat64 _linuxFileData;

    #endif

        // endregion

        // region platform independent variables

        Path _path;

        // endregion

        // region ctor + dtor + reload

        explicit File ( Path const & p ) noexcept : _path(p) { // NOLINT(cppcoreguidelines-pro-type-member-init)
            this->File::reload();
        }

        File ( File const & o ) noexcept : _path(o._path) { // NOLINT(cppcoreguidelines-pro-type-member-init)
            this->File::reload();
        }

        virtual auto reload () noexcept -> File & {

    #if defined(__linux)
            stat64(this->_path.toString().cStr(), & this->_linuxFileData);
    #endif

            return * this;
        }

    public:
        ~File () noexcept override = default;

    protected:

        // endregion

    public:

        // region diagnostic functions

        __CDS_MaybeUnused static constexpr auto setDiagnosticLogLevel ( DiagnosticLogLevel l ) noexcept -> void {
            File::_diagnosticLogLevel = l;
        }

        static inline auto diagnosticLogLevel () noexcept -> DiagnosticLogLevel {
            return File::_diagnosticLogLevel;
        }

        __CDS_MaybeUnused static constexpr auto setDiagnosticOutputStream ( std::ostream & os ) noexcept -> void {
            File::_diagnosticOutput = & os;
        }

        static auto diagnosticOutputStream () noexcept -> std::ostream & {
            return * File::_diagnosticOutput;
        }

        __CDS_MaybeUnused static inline auto diagnosticFlags () noexcept -> DiagnosticOptionFlags {
            return File::_diagnosticFixesFlags;
        }

        __CDS_MaybeUnused static constexpr auto setDiagnosticFlags ( DiagnosticOptionFlags f ) noexcept -> void {
            File::_diagnosticFixesFlags = f;
        }

        __CDS_MaybeUnused static auto setDiagnosticFlag ( DiagnosticOptionFlag f, bool enable ) noexcept -> void {
            if (enable)
                File::_diagnosticFixesFlags |= f;
            else
                File::_diagnosticFixesFlags &= ~f;
        }

        // endregion

        // region linux stat64 utility

    #if defined(__linux)

        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto linuxFileInformation () const noexcept -> struct stat64 const & { return this->_linuxFileData; }
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto linuxDeviceID () const noexcept -> __dev_t { return this->_linuxFileData.st_dev; }
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto linuxINode () const noexcept -> __ino64_t { return this->_linuxFileData.st_ino; }
        __CDS_NoDiscard __CDS_MaybeUnused inline auto linuxFileType () const noexcept -> PlatformTypeFlags { return File::platformFileType(& this->_linuxFileData); }
        __CDS_NoDiscard __CDS_MaybeUnused inline auto linuxPermissions () const noexcept -> PlatformPermissionFlags { return File::platformPermissions(& this->_linuxFileData); }
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto linuxModeFlags () const noexcept -> __mode_t { return this->_linuxFileData.st_mode; }
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto linuxHardLinkCount () const noexcept -> __nlink_t { return this->_linuxFileData.st_nlink; }
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto linuxOwnerUserID () const noexcept -> __uid_t { return this->_linuxFileData.st_uid; }
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto linuxOwnerGroupID () const noexcept -> __gid_t { return this->_linuxFileData.st_gid; }
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto linuxSpecialFileDeviceID () const noexcept -> __dev_t { return this->_linuxFileData.st_rdev; }
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto linuxTotalSize () const noexcept -> __off_t { return this->_linuxFileData.st_size; }
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto linuxBlockSize () const noexcept -> __blksize_t { return this->_linuxFileData.st_blksize; }
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto linuxBlockCount () const noexcept -> __blkcnt64_t { return this->_linuxFileData.st_blocks; }
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto linuxLastAccess () const noexcept -> struct timespec const & { return this->_linuxFileData.st_atim; };
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto linuxLastModification () const noexcept -> struct timespec const & { return this->_linuxFileData.st_mtim; };
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto linuxLastStatusChange () const noexcept -> struct timespec const & { return this->_linuxFileData.st_ctim; };

        __CDS_NoDiscard __CDS_MaybeUnused inline auto isLinuxRegularFile () const noexcept -> bool { return this->linuxFileType() & PTF_REGULAR;  }
        __CDS_NoDiscard __CDS_MaybeUnused inline auto isLinuxDirectory () const noexcept -> bool { return this->linuxFileType() & PTF_DIRECTORY; }
        __CDS_NoDiscard __CDS_MaybeUnused inline auto isLinuxCharacterDevice () const noexcept -> bool { return this->linuxFileType() & PTF_CHARACTER_DEVICE; }
        __CDS_NoDiscard __CDS_MaybeUnused inline auto isLinuxBlockDevice () const noexcept -> bool { return this->linuxFileType() & PTF_BLOCK_DEVICE; }
        __CDS_NoDiscard __CDS_MaybeUnused inline auto isLinuxFIFO () const noexcept -> bool { return this->linuxFileType() & PTF_FIFO; }
        __CDS_NoDiscard __CDS_MaybeUnused inline auto isLinuxSymbolicLink () const noexcept -> bool { return this->linuxFileType() & PTF_SYMBOLIC_LINK; }
        __CDS_NoDiscard __CDS_MaybeUnused inline auto isLinuxSocket () const noexcept -> bool { return this->linuxFileType() & PTF_SOCKET; }

        __CDS_NoDiscard auto platformInfoToString () const noexcept -> String {
            String permissionsAsString;
            auto grouped = File::platformPermissionsGrouped (& this->_linuxFileData);

            grouped.forEach ([& permissionsAsString](auto & e){
                permissionsAsString +=
                        File::platformUserFlagsToString(e.getFirst()) +
                        " : " +
                        File::platformPermissionFlagsToStringList (e.getSecond()).toString() +
                        ", ";
            });

            permissionsAsString.rtrim(", ");

            auto _atime = String(ctime(&this->_linuxFileData.st_atime)).rtrim('\n');
            auto _ctime = String(ctime(&this->_linuxFileData.st_ctime)).rtrim('\n');
            auto _mtime = String(ctime(&this->_linuxFileData.st_mtime)).rtrim('\n');

            return
                String("Linux File {") +
                " permissions = " + permissionsAsString +
                ", size (bytes) = " + static_cast < sint64 > (this->linuxTotalSize()) +
                ", deviceID = " + static_cast < uint64 > (this->linuxDeviceID ()) +
                ", inode = " + static_cast < uint64 > (this->linuxINode()) +
                ", modeFlags = " + this->linuxModeFlags () +
                ", hardLinkCount = " + static_cast < uint64 > (this->linuxHardLinkCount ()) +
                ", ownerUserID = " + this->linuxOwnerUserID () +
                ", groupUserID = " + this->linuxOwnerGroupID () +
                ", specialFileDeviceID = " + static_cast < uint64 > (this->linuxSpecialFileDeviceID ()) +
                ", blockSize = " + static_cast < sint64 > (this->linuxBlockSize ()) +
                ", blockCount = " + static_cast < sint64 > (this->linuxBlockCount ()) +
                ", lastAccess = " + _atime +
                ", lastModify = " + _mtime +
                ", lastChange = " + _ctime +
                " }";
        }

    #endif

        // endregion

        // region linux File Subclasses

    #if defined(__linux)

        class LinuxRegular;
        class LinuxDirectory;
        class LinuxCharacterDevice;
        class LinuxBlockDevice;
        class LinuxFIFO;
        class LinuxSymbolicLink;
        class LinuxSocket;

    #endif

        // endregion

        // region exceptions
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

            __CDS_NoDiscard auto what () const noexcept -> StringLiteral override {
                return this->_message.cStr();
            }
        };
        // endregion

        // region utility functions
        __CDS_NoDiscard constexpr auto path () const noexcept -> Path const & { return this->_path; }
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto path () noexcept -> Path & { return this->_path; }

        __CDS_NoDiscard inline auto name () const noexcept -> String { return this->path().nodeName(); }

        __CDS_NoDiscard static auto at (Path const &) noexcept -> UniquePointer < File >;

        __CDS_NoDiscard auto copy () const noexcept -> File * override = 0;

        __CDS_NoDiscard auto toString () const noexcept -> String override {
            return
                    String("File {") +
                    " path = " + this->_path.toString() +
                    ", platformInfo = " + this->platformInfoToString ()
                    + " }";
        }

        // endregion
    };

}

#if defined(__linux)

// region Linux Platform Flags Impl.

// region Linux Platform File Type Impl.

namespace cds {

    inline auto File::platformTypeFlagsToString ( File::PlatformTypeFlags flags ) noexcept -> String {
        String rep = "";

        for ( uint8 f = PTF_MIN_VALUE; f <= PTF_MAX_VALUE; f <<= 1u )
            if ( f & flags )
                rep += String(File::platformFileTypeFlagToString ( static_cast < PlatformTypeFlag > (f) )) + ", ";

        return rep.rtrim(", ");
    }

    __CDS_MaybeUnused inline auto File::platformTypeFlagsToStringList ( File::PlatformTypeFlags flags ) noexcept -> LinkedList < String > {
        LinkedList < String > l;

        for ( uint8 f = PTF_MIN_VALUE; f <= PTF_MAX_VALUE; f <<= 1u )
            if ( f & flags )
                l.pushBack ( File::platformFileTypeFlagToString ( static_cast < File::PlatformTypeFlag > (f) ) );

        return l;
    }

    __CDS_MaybeUnused inline auto File::platformTypeFlagsToList ( File::PlatformTypeFlags flags ) noexcept -> LinkedList < File::PlatformTypeFlag > {
        LinkedList < File::PlatformTypeFlag > l;

        for ( uint8 f = PTF_MIN_VALUE; f <= PTF_MAX_VALUE; f <<= 1u )
            if ( f & flags )
                l.pushBack ( static_cast < File::PlatformTypeFlag > (f) );

        return l;
    }

    inline auto File::platformFileType(Path const & p) noexcept -> PlatformTypeFlags {
        struct stat64 st; // NOLINT(cppcoreguidelines-pro-type-member-init)
        if ( -1 == lstat64(p.toString().cStr(), & st) ) {
            std::cout << "Ok?\n" << p.toString().cStr() << '\n';
        }

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

}

// endregion

// region Linux Platform Permission Flags Impl.

namespace cds {

    __CDS_MaybeUnused inline auto File::platformPermissionFlagsToString ( PlatformPermissionFlags flags ) noexcept -> String {
        String rep = "";

        for ( uint8 f = PPF_MIN_VALUE; f <= PPF_MAX_VALUE; f <<= 1u )
            if ( f & flags )
                rep += String(File::platformPermissionFlagToString ( static_cast < PlatformPermissionFlag > (f) )) + ", ";

        return rep.rtrim(", ");
    }

    inline auto File::platformPermissionFlagsToStringList ( PlatformPermissionFlags flags ) noexcept -> LinkedList < String > {
        LinkedList < String > l;

        for ( uint8 f = PPF_MIN_VALUE; f <= PPF_MAX_VALUE; f <<= 1u )
            if ( f & flags )
                l.pushBack(File::platformPermissionFlagToString ( static_cast < PlatformPermissionFlag > (f) ));

        return l;
    }

    __CDS_MaybeUnused inline auto File::platformPermissionFlagsToList ( PlatformPermissionFlags flags ) noexcept -> LinkedList < PlatformPermissionFlag > {
        LinkedList < PlatformPermissionFlag > l;

        for ( uint8 f = PPF_MIN_VALUE; f <= PPF_MAX_VALUE; f <<= 1u )
            if ( f & flags )
                l.pushBack( static_cast < PlatformPermissionFlag > (f) );

        return l;
    }

}

// endregion

// region Linux Platform User Flags Impl.

namespace cds {

    inline auto File::platformUserFlagsToString ( PlatformUserFlags flags ) noexcept -> String {
        String rep = "";

        for ( uint8 f = PUF_MIN_VALUE; f <= PUF_MAX_VALUE; f <<= 1u )
            if ( f & flags )
                rep += String(File::platformUserFlagToString ( static_cast < PlatformUserFlag > (f) )) + ", ";

        return rep.rtrim(", ");
    }

    __CDS_MaybeUnused inline auto File::platformUserFlagsToStringList ( PlatformUserFlags flags ) noexcept -> LinkedList < String > {
        LinkedList < String > l;

        for ( uint8 f = PUF_MIN_VALUE; f <= PUF_MAX_VALUE; f <<= 1u )
            if ( f & flags )
                l.append(File::platformUserFlagToString ( static_cast < PlatformUserFlag > (f) ));

        return l;
    }

    __CDS_MaybeUnused inline auto File::platformUserFlagsToList ( PlatformUserFlags flags ) noexcept -> LinkedList < PlatformUserFlag > {
        LinkedList < PlatformUserFlag > l;

        for ( uint8 f = PUF_MIN_VALUE; f <= PUF_MAX_VALUE; f <<= 1u )
            if ( f & flags )
                l.append( static_cast < PlatformUserFlag > (f) );

        return l;
    }

}

// endregion

// region Linux Platform Permissions Impl.

namespace cds {

    __CDS_MaybeUnused inline auto File::platformPermissions ( Path const & path, PlatformUserFlags flags ) noexcept -> PlatformPermissionFlags {
        struct stat64 st; // NOLINT(cppcoreguidelines-pro-type-member-init)
        lstat64 ( path.toString().cStr(), & st );
        return File::platformPermissions ( &st, flags );
    }

    __CDS_MaybeUnused inline auto File::platformPermissionsGrouped ( Path const & path ) noexcept -> HashMap < PlatformUserFlag, PlatformPermissionFlags > {
        struct stat64 st; // NOLINT(cppcoreguidelines-pro-type-member-init)
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

}

// endregion

// endregion

#endif

// region linux File Subclasses

#if defined(__linux)

namespace cds {

    class File::LinuxRegular : public File {
    private:
        __CDS_MaybeUnused int fd;

    public:
        explicit LinuxRegular (Path const & path) noexcept (false) : File (path) { // NOLINT(cppcoreguidelines-pro-type-member-init)
            if ( ! this->isLinuxRegularFile () )
                throw InvalidFileType ( PTF_REGULAR, this->linuxFileType() );
        }

        __CDS_NoDiscard auto toString () const noexcept -> String override {
            return
                String("Linux Regular File {") +
                " file = " + File::toString() +
                " }";
        }

        ~LinuxRegular () noexcept override = default;

        __CDS_NoDiscard auto copy () const noexcept -> LinuxRegular * override {
            return Memory :: instance().create < LinuxRegular > (* this);
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto open (String const & = "rw") noexcept -> LinuxRegular & {
    #warning File Encoding Read/Write Not Implemented
            return * this;
        }

        __CDS_MaybeUnused auto close () noexcept -> LinuxRegular & {
    #warning Not Implemented
            return * this;
        }
    };

}

#include <unistd.h>
#include <sys/wait.h>

namespace cds {

    class File::LinuxDirectory : public File {
    private:
        LinkedList < File * > _entries;
        bool                  _reloadRequired {true};

    public:
        explicit LinuxDirectory (Path const & path) noexcept (false) : File (path) {
            if ( ! this->isLinuxDirectory () )
                throw InvalidFileType ( PTF_DIRECTORY, this->linuxFileType() );
        }

        __CDS_NoDiscard auto toString () const noexcept -> String override {
            return
                    String("Linux Directory {") +
                    " file = " + File::toString() +
                    " }";
        }

        auto reload () noexcept -> LinuxDirectory & override {
            if ( ! this->_reloadRequired )
                return * this;
            this->_reloadRequired = false;

            File::reload();

            if ( ! this->_entries.empty() ) {
                for ( auto * p : this->_entries )
                    Memory :: instance().destroy ( p );
                this->_entries.clear();
            }

            for ( auto & e : this->path().walk(1) ) {
                for ( auto & f : e.files() ) {
                    try {
                        auto p = File::at(e.root() / f);
                        this->_entries.append(p->copy());
                    } catch ( Path::InvalidPath const & ) {
                        // region do nothing, broken symbolic link

                        if ( static_cast < int > (DLL_WARNING) <= static_cast < int > (File::diagnosticLogLevel()) )
                            File::diagnosticOutputStream () << "[" << File::diagnosticLogLevelToString(DLL_WARNING) << "] : Symbolic Link '" << (e.root().toString() + "/" + f ) << "' broken" << '\n';

                        if ( File::_diagnosticFixesFlags & ( DO_BASIC_AUTOMATIC_FIXES | DO_BROKEN_SYMBOLIC_LINKS ) ) {
                            if (fork() == 0)
                                execl("rm", "rm", (e.root().toString() + "/" + f).cStr(), NULL);
                            else
                                wait(nullptr);
                        }
                        // endregion
                    }
                }
                for ( auto & d : e.directories() ) {
                    auto p = File::at(e.root() / d);
                    this->_entries.append(p->copy());
                }
            }

            return * this;
        }

        __CDS_NoDiscard constexpr auto entries () const noexcept -> LinkedList < File * > const & { return this->_entries; }
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto entries () noexcept -> LinkedList < File * > & { this->reload(); return this->_entries; }

        __CDS_NoDiscard auto files () const noexcept -> LinkedList < File::LinuxRegular * > {
            LinkedList < File::LinuxRegular * > l;
            for ( auto & e : this->entries () )
                if ( e->isLinuxRegularFile() )
                    l.append(reinterpret_cast <File::LinuxRegular *>(e));

            return l;
        }

        __CDS_NoDiscard auto directories () const noexcept -> LinkedList < File::LinuxDirectory * > {
            LinkedList < File::LinuxDirectory * > l;
            for ( auto & e : this->entries () )
                if ( e->isLinuxDirectory() )
                    l.append(reinterpret_cast <File::LinuxDirectory *>(e));

            return l;
        }

        __CDS_NoDiscard auto files () noexcept -> LinkedList < File::LinuxRegular * > {
            LinkedList < File::LinuxRegular * > l;
            for ( auto & e : this->entries () )
                if ( e->isLinuxRegularFile() )
                    l.append(reinterpret_cast <File::LinuxRegular *>(e));

            return l;
        }

        __CDS_NoDiscard auto directories () noexcept -> LinkedList < File::LinuxDirectory * > {
            LinkedList < File::LinuxDirectory * > l;
            for ( auto & e : this->entries () )
                if ( e->isLinuxDirectory() )
                    l.append(reinterpret_cast <File::LinuxDirectory *>(e));

            return l;
        }

        ~LinuxDirectory () noexcept override {
            for ( auto * p : this->_entries )
                Memory :: instance().destroy ( p );
            this->_entries.clear();
        }

        __CDS_NoDiscard auto copy () const noexcept -> LinuxDirectory * override {
            return Memory :: instance().create < LinuxDirectory >(* this);
        }
    };

    class File::LinuxCharacterDevice : public File {
    public:
        explicit LinuxCharacterDevice (Path const & path) noexcept (false) : File (path) {
            if ( ! this->isLinuxCharacterDevice () )
                throw InvalidFileType ( PTF_CHARACTER_DEVICE, this->linuxFileType() );
    #warning Warning : Linux Character Device Partial Support
        }

        __CDS_NoDiscard auto toString () const noexcept -> String override {
            return
                    String("Linux Character Device {") +
                    " file = " + File::toString() +
                    " }";
        }

        ~LinuxCharacterDevice () noexcept override = default;

        __CDS_NoDiscard auto copy () const noexcept -> LinuxCharacterDevice * override {
            return Memory :: instance().create < LinuxCharacterDevice > (* this);
        }
    };

    class File::LinuxBlockDevice : public File {
    public:
        explicit LinuxBlockDevice (Path const & path) noexcept (false) : File (path) {
            if ( ! this->isLinuxBlockDevice () )
                throw InvalidFileType ( PTF_BLOCK_DEVICE, this->linuxFileType () );
    #warning Warning : Linux Block Device Partial Support
        }

        __CDS_NoDiscard auto toString () const noexcept -> String override {
            return
                    String("Linux Block Device {") +
                    " file = " + File::toString() +
                    " }";
        }

        ~LinuxBlockDevice () noexcept override = default;

        __CDS_NoDiscard auto copy () const noexcept -> LinuxBlockDevice * override {
            return Memory :: instance().create < LinuxBlockDevice > (* this);
        }
    };

    class File::LinuxFIFO : public File {
    public:
        explicit LinuxFIFO (Path const & path) noexcept (false) : File (path) {
            if ( ! this->isLinuxFIFO() )
                throw InvalidFileType ( PTF_FIFO, this->linuxFileType() );
        }

        __CDS_NoDiscard auto toString () const noexcept -> String override {
            return
                    String("Linux FIFO {") +
                    " file = " + File::toString() +
                    " }";
        }

        ~LinuxFIFO () noexcept override = default;

        __CDS_NoDiscard auto copy () const noexcept -> LinuxFIFO * override {
            return Memory :: instance().create < LinuxFIFO > (* this);
        }
    };

    class File::LinuxSymbolicLink : public File {
    public:
        explicit LinuxSymbolicLink (Path const & path) noexcept (false) : File (path) {
            if ( ! this->isLinuxSymbolicLink () )
                throw InvalidFileType ( PTF_SYMBOLIC_LINK, this->linuxFileType () );
        }

        __CDS_NoDiscard auto toString () const noexcept -> String override {
            return
                    String("Linux Symbolic Link {") +
                    " file = " + File::toString() +
                    " }";
        }

        ~LinuxSymbolicLink () noexcept override = default;

        __CDS_NoDiscard auto copy () const noexcept -> LinuxSymbolicLink * override {
            return Memory :: instance().create < LinuxSymbolicLink > (* this);
        }
    };

    class File::LinuxSocket : public File {
    public:
        explicit LinuxSocket (Path const & path) noexcept (false) : File (path) {
            if ( ! this->isLinuxSocket () )
                throw InvalidFileType ( PTF_SOCKET, this->linuxFileType () );
        }

        __CDS_NoDiscard auto toString () const noexcept -> String override {
            return
                    String("Linux Socket {") +
                    " file = " + File::toString() +
                    " }";
        }

        ~LinuxSocket () noexcept override = default;

        __CDS_NoDiscard auto copy () const noexcept -> LinuxSocket * override {
            return Memory :: instance().create < LinuxSocket > (* this);
        }
    };

}

#endif

//endregion

// region File factory function

namespace cds {

    __CDS_NoDiscard inline auto File::at (Path const & p) noexcept -> UniquePointer < File > {

    #if defined(__linux)

        auto flags = File::platformFileType(p);

        if ( flags & PTF_REGULAR )          return {Memory :: instance().create < LinuxRegular > (p)};
        if ( flags & PTF_DIRECTORY )        return {Memory :: instance().create < LinuxDirectory > (p)};
        if ( flags & PTF_CHARACTER_DEVICE ) return {Memory :: instance().create < LinuxCharacterDevice > (p)};
        if ( flags & PTF_BLOCK_DEVICE )     return {Memory :: instance().create < LinuxBlockDevice > (p)};
        if ( flags & PTF_FIFO )             return {Memory :: instance().create < LinuxFIFO > (p)};
        if ( flags & PTF_SYMBOLIC_LINK )    return {Memory :: instance().create < LinuxSymbolicLink > (p)};
        if ( flags & PTF_SOCKET )           return {Memory :: instance().create < LinuxSocket > (p)};

    #endif

        return { Memory :: instance().create < LinuxSymbolicLink > (p) };
    }

}

// endregion

// region File inline static vars

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_17

#include <iostream>

namespace cds {

    inline std::ostream *                   File::_diagnosticOutput = & std::cerr; // NOLINT(cppcoreguidelines-interfaces-global-init)
    inline File::DiagnosticLogLevel         File::_diagnosticLogLevel = File::DiagnosticLogLevel::DLL_ALL;
    inline File::DiagnosticOptionFlags      File::_diagnosticFixesFlags = File::DiagnosticOptionFlag::DO_NO_AUTOMATIC_FIXES;

}

#else

#endif

// endregion

__CDS_RegisterParseType(File)

#endif //CDS_FILE_HPP

