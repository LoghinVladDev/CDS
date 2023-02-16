/*
 * Created by loghin on 18/11/22.
 */

#ifndef __CDS_PATH_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_PATH_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#if defined(WIN32)
#include <windows.h>
#elif defined(__linux)
#include <climits>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#else
#warning Warning : Path-lib Unsupported
#endif

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace filesystem {

        namespace __hidden {
            namespace __impl {

                constexpr auto __directorySeparator () noexcept -> char {

#if defined(WIN32)
                    return '\\';
#elif defined(__linux)
                    return '/';
#endif
                }

            }
        }

        inline auto Path :: pathOsConvert (
                StringView path
        ) noexcept -> String {

            constexpr StringView const directorySeparators ("/\\", 2);

            String osPath;
            bool   prevDirSeparator = false;
            for ( auto character : path ) {

                if ( directorySeparators.contains ( character ) ) {

                    if ( prevDirSeparator ) {
                        continue;
                    }

                    osPath += __hidden :: __impl :: __directorySeparator();
                    prevDirSeparator = true;
                } else {
                    osPath += character;
                    prevDirSeparator = false;
                }
            }

            return osPath;
        }


        inline Path :: Path (
                StringView osPath
        ) noexcept :
                _osPath ( pathOsConvert ( osPath ) ) {

        }


        template <
                typename __ConvertibleType,
                cds :: meta :: EnableIf <
                        cds :: meta :: isConvertibleToBaseStringView < __ConvertibleType, char > ()
                >
        > inline Path :: Path (
                __ConvertibleType && osPath
        ) noexcept :
                Path ( StringView ( std :: forward < __ConvertibleType > ( osPath ) ) ) {

        }


        inline Path :: Path (
                Path const & path
        ) noexcept :
                _osPath ( path._osPath ) {

        }


        constexpr Path :: Path (
                Path && path
        ) noexcept :
                _osPath ( std :: move ( path._osPath ) ) {

        }


        inline auto Path :: operator = (
                Path const & path
        ) noexcept -> Path & {

            if ( this == & path ) {
                return * this;
            }

            this->_osPath = path._osPath;
            return * this;
        }


        inline auto Path :: operator = (
                Path && path
        ) noexcept -> Path & {

            if ( this == & path ) {
                return * this;
            }

            this->_osPath = std :: move ( path._osPath );
            return * this;
        }


        inline auto Path :: operator = (
                StringView osPath
        ) noexcept -> Path & {

            this->_osPath = pathOsConvert ( osPath );
            return * this;
        }


        template <
                typename __ConvertibleType,
                cds :: meta :: EnableIf <
                        cds :: meta :: isConvertibleToBaseStringView < __ConvertibleType, char > ()
                >
        > inline auto Path :: operator = (
                __ConvertibleType && osPath
        ) noexcept -> Path & {

            return * this = StringView ( std :: forward < __ConvertibleType > ( osPath ) );
        }


        inline auto Path :: parent () const noexcept -> Path {

            auto location = this->_osPath.findLast ( __hidden :: __impl :: __directorySeparator() );
            if ( location == 0 || location == String :: invalidIndex ) {
                return * this;
            }

            return StringView ( this->_osPath.substr (0, location) );
        }


        inline auto Path :: node () const noexcept -> StringView {

            auto location = this->_osPath.findLast ( __hidden :: __impl :: __directorySeparator() );
            if ( location == String :: invalidIndex ) {
                return this->_osPath;
            }

            return { this->_osPath.cStr() + location + 1, this->_osPath.length() - location - 1 };
        }


        inline auto Path :: root () const noexcept -> Path {

            auto location = this->_osPath.findFirst ( __hidden :: __impl :: __directorySeparator() );
            if ( location == 0 || location == String :: invalidIndex ) {
                return * this;
            }

            return StringView ( this->_osPath.cStr(), location );
        }


        inline auto Path :: sanitize () const noexcept -> Path {

            String newPath;
            bool dotSequenceValid = false;
            int dotSequenceCount = 0;

            for ( char character : this->_osPath ) {

                if ( character == '.' ) {
                    ++ dotSequenceCount;
                    continue;
                } else {

                    if ( dotSequenceValid && dotSequenceCount > 0 && character == __hidden :: __impl :: __directorySeparator() ) {

                        if ( dotSequenceCount == 1 ) {

                            dotSequenceValid = true;
                            dotSequenceCount = 0;
                            continue;
                        } else if ( dotSequenceCount == 2 ) {

                            auto lastSeparator = newPath.findLast ( __hidden :: __impl :: __directorySeparator() );
                            if ( lastSeparator == 0 || lastSeparator == String :: invalidIndex ) {
                                /* nothing */
                            } else {
                                newPath = newPath.substr ( 0, lastSeparator );
                            }
                        }
                    }

                    dotSequenceValid = false;
                    dotSequenceCount = 0;
                }

                newPath += character;
                if ( character == __hidden :: __impl :: __directorySeparator() ) {
                    dotSequenceValid = true;
                }
            }

            return StringView ( newPath );
        }


        inline auto Path :: operator / (
                StringView node
        ) const noexcept -> Path {

            return { this->_osPath + __hidden :: __impl :: __directorySeparator() + std :: move ( Path :: pathOsConvert ( node ) ) };
        }


        inline auto Path :: operator /= (
                StringView node
        ) noexcept -> Path & {

            this->_osPath += __hidden :: __impl :: __directorySeparator();
            this->_osPath += std :: move ( Path :: pathOsConvert ( node ) );
            return * this;
        }


        inline auto Path :: operator + (
                StringView node
        ) const noexcept -> Path {

            return * this / node;
        }


        inline auto Path :: operator += (
                StringView node
        ) noexcept -> Path & {

            return * this /= node;
        }


        inline auto Path :: append (
                StringView node
        ) noexcept -> Path & {

            return * this /= node;
        }


        inline auto Path :: isRelative () const noexcept -> bool {

            return
                    this->_osPath.length() > 0 &&
                    this->_osPath.cStr() [0] == '.' ||
                    ! this->isAbsolute();
        }


        inline auto Path :: isAbsolute () const noexcept -> bool {

            return
#if (__linux)
                    this->_osPath.length() >= 1 &&
                    __hidden :: __impl :: __directorySeparator() == this->_osPath.cStr()[0];
#elif defined(WIN32)
                    this->_osPath.length() > 2 && (
                            StringUtils < char > :: isLetter ( this->_osPath.cStr()[0] ) &&
                            this->_osPath.cStr()[1] == ':'
                    );
#endif
        }


        inline auto Path :: exists () const noexcept -> bool {

#if defined(__linux)

            struct stat64 fileStatistics {};
            if ( stat64 ( this->_osPath.cStr(), & fileStatistics ) != 0 ) {
                return false;
            }

#elif defined(WIN32)

            constexpr static uint16 initialPathSize = 8192;
            char * resolvedPath = (char *) malloc (initialPathSize);

            auto actualLength = GetFullPathNameA (
                    this->_osPath.cStr(),
                    initialPathSize,
                    resolvedPath,
                    nullptr
            );

            if ( actualLength >= initialPathSize ) {
                free ( resolvedPath );
                resolvedPath = (char *) malloc (actualLength + 1);

                if (
                        GetFullPathNameA (
                                this->_osPath.cStr(),
                                actualLength + 1,
                                resolvedPath,
                                nullptr
                        ) == 0
                ) {
                    free ( resolvedPath );
                    return false;
                }
            } else if ( actualLength == 0 ) {
                free ( resolvedPath );
                return false;
            }

            free (resolvedPath);

#endif

            return true;
        }


        inline auto Path :: operator == (
                Path const & path
        ) const noexcept -> bool {

            return this->_osPath == path._osPath;
        }


        inline auto Path :: operator != (
                Path const & path
        ) const noexcept -> bool {

            return this->_osPath != path._osPath;
        }


        inline auto Path :: operator == (
                StringView path
        ) const noexcept -> bool {

            return this->_osPath == Path :: pathOsConvert ( path );
        }


        inline auto Path :: operator != (
                StringView path
        ) const noexcept -> bool {

            return this->_osPath != Path :: pathOsConvert ( path );
        }


        inline auto Path :: toString () const noexcept -> String {

            return this->_osPath;
        }


        inline auto Path :: hash () const noexcept -> Size {

            return this->_osPath.hash();
        }


        inline auto Path :: equals (
                Object const & object
        ) const noexcept -> bool {

            if ( this == & object ) {
                return true;
            }

            auto pPath = dynamic_cast < decltype (this) > ( & object );
            if ( pPath == nullptr ) {
                return false;
            }

            return this->_osPath == pPath->_osPath;
        }


        inline auto Path :: currentDirectory () noexcept -> Path const & {

            static Path const currentDir = Path (".");
            return currentDir;
        }


        inline auto Path :: asAbsolute () const noexcept (false) -> Path {

            if ( ! this->exists() ) {
                throw IllegalArgumentException ("Cannot Resolve Absolute path of '" + this->_osPath + "'");
            }

#if defined(__linux)

            char resolvedPath [PATH_MAX];
            (void) realpath (this->_osPath.cStr(), resolvedPath);

            return StringView (resolvedPath);

#elif defined(WIN32)

            constexpr static uint16 initialPathSize = 8192;
            char * resolvedPath = (char *) malloc (initialPathSize);

            auto actualLength = GetFullPathNameA (
                    this->_osPath.cStr(),
                    initialPathSize,
                    resolvedPath,
                    nullptr
            );

            if ( actualLength >= initialPathSize ) {
                free ( resolvedPath );
                resolvedPath = (char *) malloc (actualLength + 1);

                if (
                        GetFullPathNameA (
                                this->_osPath.cStr(),
                                actualLength + 1,
                                resolvedPath,
                                nullptr
                        ) == 0
                ) {
                    free ( resolvedPath );
                    throw IllegalArgumentException ("Cannot Resolve Absolute path of '" + this->_osPath + "'");
                }
            } else if ( actualLength == 0 ) {
                free ( resolvedPath );
                throw IllegalArgumentException ("Cannot Resolve Absolute path of '" + this->_osPath + "'");
            }

            if ( GetFileAttributesA(resolvedPath) == INVALID_FILE_ATTRIBUTES ) {
                free(resolvedPath);
                throw IllegalArgumentException ("Cannot Resolve Absolute path of '" + this->_osPath + "'");
            }

            String resolvedPathAsStr = resolvedPath;
            free ( resolvedPath );
            return StringView (resolvedPathAsStr);

#else

            return * this;

#endif
        }

    } /* namespace filesystem */
} /* namespace cds */

#endif /* __CDS_PATH_IMPL_HPP__ */
