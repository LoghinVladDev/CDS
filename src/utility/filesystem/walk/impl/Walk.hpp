/*
 * Created by loghin on 18/11/22.
 */

#ifndef __CDS_WALK_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_WALK_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#if defined(WIN32)
#include <windows.h>
#elif defined(__linux)
#include <sys/stat.h>   /*NOLINT(llvm-include-order) */
#include <unistd.h>
#include <climits>
#include <dirent.h>
#else
#warning Warning : Path-lib Unsupported
#endif

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace filesystem {      /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                auto __walk (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        StringView                                  osPath, /* NOLINT(bugprone-easily-swappable-parameters) */
                        Size                                        depth,
                        Array < cds :: filesystem :: WalkEntry >  & entries
                ) noexcept -> void {

                    LinkedList < Tuple < String, Size > > rootQueue;    /* NOLINT(cppcoreguidelines-init-variables) */
                    rootQueue.emplace ( osPath, 0ULL );

#if defined(__linux)

                    while ( ! rootQueue.empty() ) {

                        auto rootTuple = rootQueue.front();
                        rootQueue.popFront();

                        Size rootDepth = rootTuple.get <1> ();  /* NOLINT(cppcoreguidelines-init-variables) */
                        if ( rootDepth > depth ) {
                            continue;
                        }

                        String const & root = rootTuple.get <0> ();
                        auto dir = opendir ( root.cStr() );
                        if ( dir == nullptr ) {
                            return;
                        }

                        Array < String > directories;   /* NOLINT(cppcoreguidelines-init-variables) */
                        Array < String > files;         /* NOLINT(cppcoreguidelines-init-variables) */

                        for ( auto entry = readdir64 (dir); entry != nullptr; entry = readdir64(dir) ) {

                            if (
                                    entry->d_type == DT_LNK ||
                                    std :: strcmp ( entry->d_name, "." ) == 0 || std :: strcmp ( entry->d_name, ".." ) == 0
                            ) {
                                /* avoid looping into links, do nothing */
                                /* avoid looping into self, do nothing */
                                continue;
                            }

                            if ( entry->d_type == DT_DIR ) {

                                (void) directories.emplaceBack ( entry->d_name );
                                (void) rootQueue.emplaceBack ( root + Path :: directorySeparator + directories.back(), rootDepth + 1ULL );
                                continue;
                            }

                            (void) files.emplaceBack ( entry->d_name );
                        }

                        (void) closedir (dir);
                        (void) entries.pushBack (
                                WalkEntry (
                                        Path ( std :: move ( root ) ),
                                        std :: move ( directories ),
                                        std :: move ( files )
                                )
                        );
                    }

#endif
                }

            } /* namespace __impl */
        } /* namespace __hidden */

        auto walk (
                Path    const & path,   /* NOLINT(bugprone-easily-swappable-parameters) */
                Size            depth
        ) noexcept -> Array < WalkEntry > {

            if ( ! path.exists() ) {
                return {};
            }

            cds :: Array < WalkEntry > entries;
            __hidden :: __impl :: __walk (
                    path.toString(),
                    depth,
                    entries
            );
            return entries;
        }


        inline WalkEntry :: WalkEntry (
                WalkEntry && entry
        ) noexcept :
                _root ( std :: move ( entry._root ) ),
                _directories ( std :: move ( entry._directories ) ),
                _files ( std :: move ( entry._files ) ) {

        }


        inline WalkEntry :: WalkEntry (
                Path             && path,
                Array < String > && directories,
                Array < String > && files
        ) noexcept :
                _root ( std :: move ( path ) ),
                _directories ( std :: move ( directories ) ),
                _files ( std :: move ( files ) ) {

        }


        constexpr auto WalkEntry :: root () const noexcept -> Path const & {

            return this->_root;
        }


        constexpr auto WalkEntry :: directories () const noexcept -> Array < String > const & {

            return this->_directories;
        }


        constexpr auto WalkEntry :: files () const noexcept -> Array < String > const & {

            return this->_files;
        }


        inline auto WalkEntry :: toString () const noexcept -> String {

            using namespace cds :: literals;
            return "( root: "_s + this->root().toString() + ", directories: " + this->directories() + ", files: " + this->files() + " )";
        }


        inline auto WalkEntry :: equals (
                Object const & object
        ) const noexcept -> bool {

            if ( this == & object ) {
                return true;
            }

            auto pObject = dynamic_cast < decltype(this) > ( & object );
            if ( pObject == nullptr ) {
                return false;
            }

            return this->_root == pObject->_root;
        }


        inline auto WalkEntry :: hash () const noexcept -> Size {

            return this->_root.hash();
        }


        inline auto WalkEntry :: operator == (
                WalkEntry const & entry
        ) const noexcept -> bool {

            if ( this == & entry ) {
                return true;
            }

            return this->_root == entry._root;
        }


        inline auto WalkEntry :: operator != (
                WalkEntry const & entry
        ) const noexcept -> bool {

            return ! this->operator==(entry);
        }


    } /* namespace filesystem */
} /* namespace cds */

#endif /* __CDS_WALK_IMPL_HPP__ */
