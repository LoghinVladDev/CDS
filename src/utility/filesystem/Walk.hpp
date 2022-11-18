/*
 * Created by loghin on 18/11/22.
 */

#ifndef __CDS_WALK_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_WALK_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/filesystem/Path>

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace filesystem {      /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                auto __walk (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        StringView                                  osPath,
                        Size                                        depth,
                        Size                                        current,
                        Array < cds :: filesystem :: WalkEntry >  & entries
                ) noexcept -> void;

            } /* namespace __impl */
        } /* namespace __hidden */

        auto walk (
                Path    const & path,
                Size            depth = limits :: U64_MAX
        ) noexcept -> Array < WalkEntry >;

        auto walk (
                StringView      osPath,
                Size            depth = limits :: U64_MAX
        ) noexcept -> Array < WalkEntry >;

        class WalkEntry : public Object {

        private:    /* NOLINT(readability-redundant-access-specifiers) */
            friend auto cds :: filesystem :: __hidden :: __impl :: __walk ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    StringView                                  osPath,
                    Size                                        depth,
                    Size                                        current,
                    Array < cds :: filesystem :: WalkEntry >  & entries
            ) noexcept -> void;

        private:    /* NOLINT(readability-redundant-access-specifiers) */
            Path                _root;

        private:    /* NOLINT(readability-redundant-access-specifiers) */
            Array < String >    _directories;

        private:    /* NOLINT(readability-redundant-access-specifiers) */
            Array < String >    _files;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            WalkEntry () noexcept = delete;

        private:    /* NOLINT(readability-redundant-access-specifiers) */
            WalkEntry (
                    Path             && path,
                    Array < String > && directories,
                    Array < String > && files
            ) noexcept;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            WalkEntry (
                    WalkEntry const & entry
            ) noexcept = default;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            WalkEntry (
                    WalkEntry && entry
            ) noexcept;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            ~WalkEntry() noexcept override = default;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            auto operator = (
                    WalkEntry const & /* entry */
            ) noexcept -> WalkEntry & = delete;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            auto operator = (
                    WalkEntry && /* entry */
            ) noexcept -> WalkEntry & = delete;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard constexpr auto root () const noexcept -> Path const &;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard constexpr auto directories () const noexcept -> Array < String > const &;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard constexpr auto files () const noexcept -> Array < String > const &;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto toString () const noexcept -> String override;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto equals (
                    Object const & object
            ) const noexcept -> bool override;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto hash () const noexcept -> Size override;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto operator == (
                    WalkEntry const & entry
            ) const noexcept -> bool;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto operator != (
                    WalkEntry const & entry
            ) const noexcept -> bool;
        };

    } /* namespace filesystem */
} /* namespace cds */

#include "walk/impl/Walk.hpp"

#endif /* __CDS_WALK_HPP__ */
