/*
 * Created by loghin on 10.05.2021.
 */

#ifndef __CDS_PATH_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_PATH_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace filesystem {

        class WalkEntry;

        class Path : public Object {

        public: /* NOLINT(readability-redundant-access-specifiers) */
            static char const directorySeparator;

        private:    /* NOLINT(readability-redundant-access-specifiers) */
            String _osPath {};

        public: /* NOLINT(readability-redundant-access-specifiers) */
            static auto currentDirectory () noexcept -> Path const &;

        private:    /* NOLINT(readability-redundant-access-specifiers) */
            static auto pathOsConvert (
                    StringView path
            ) noexcept -> String;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            Path () noexcept = default;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_Implicit Path (
                    StringView osPath
            ) noexcept;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            template <
                    typename __ConvertibleType,
                    cds :: meta :: EnableIf <
                            cds :: meta :: isConvertibleToBaseStringView < __ConvertibleType, char > ()
                    > = 0
            > __CDS_Implicit Path (
                    __ConvertibleType && osPath
            ) noexcept;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            Path (
                    Path const & path
            ) noexcept;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            constexpr Path (
                    Path && path
            ) noexcept;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            ~Path () noexcept override = default;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            auto operator = (
                    Path const & path
            ) noexcept -> Path &;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            auto operator = (
                    Path && path
            ) noexcept -> Path &;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            auto operator = (
                    StringView osPath
            ) noexcept -> Path &;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            template <
                    typename __ConvertibleType,
                    cds :: meta :: EnableIf <
                            cds :: meta :: isConvertibleToBaseStringView < __ConvertibleType, char > ()
                    > = 0
            > auto operator = (
                    __ConvertibleType && osPath
            ) noexcept -> Path &;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto parent () const noexcept -> Path;      /* NOLINT(modernize-use-nodiscard) */

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto node () const noexcept -> StringView;  /* NOLINT(modernize-use-nodiscard) */

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto root () const noexcept -> Path;        /* NOLINT(modernize-use-nodiscard) */

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto sanitize () const noexcept -> Path;    /* NOLINT(modernize-use-nodiscard) */

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto asAbsolute () const noexcept (false) -> Path;  /* NOLINT(modernize-use-nodiscard) */

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto operator / (
                    StringView node
            ) const noexcept -> Path;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            auto operator /= (
                    StringView node
            ) noexcept -> Path &;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto operator + (
                    StringView node
            ) const noexcept -> Path;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            auto operator += (
                    StringView node
            ) noexcept -> Path &;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            auto append (
                    StringView node
            ) noexcept -> Path &;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto isRelative () const noexcept -> bool;  /* NOLINT(modernize-use-nodiscard) */

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto isAbsolute () const noexcept -> bool;  /* NOLINT(modernize-use-nodiscard) */

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto exists () const noexcept -> bool;      /* NOLINT(modernize-use-nodiscard) */

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto walk (                                 /* NOLINT(modernize-use-nodiscard) */
                    Size maxDepth = cds :: limits :: U64_MAX
            ) const noexcept -> Array < WalkEntry >;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto operator == (
                    Path const & path
            ) const noexcept -> bool;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto operator != (
                    Path const & path
            ) const noexcept -> bool;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto operator == (
                    StringView path
            ) const noexcept -> bool;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto operator != (
                    StringView path
            ) const noexcept -> bool;

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto toString () const noexcept -> String override; /* NOLINT(modernize-use-nodiscard) */

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto hash () const noexcept -> Size override;       /* NOLINT(modernize-use-nodiscard) */

        public: /* NOLINT(readability-redundant-access-specifiers) */
            __CDS_NoDiscard auto equals (                                       /* NOLINT(modernize-use-nodiscard) */
                    Object const & object
            ) const noexcept -> bool override;
        };

    } /* namespace filesystem */
} /* namespace cds */

#include "../../shared/util/JsonLoad.hpp"
#include "../../shared/util/PathWalk.hpp"
#include "path/impl/Path.hpp"

#endif /* __CDS_PATH_HPP__ */
