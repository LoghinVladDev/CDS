/*
 * Created by loghin on 10.05.2021.
 */

#ifndef __CDS_PATH_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_PATH_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace filesystem {

        class WalkEntry;

        class Path : public Object {

        public:
            static char const directorySeparator;

        private:
            String _osPath;

        public:
            static auto currentDirectory () noexcept -> Path const &;

        private:
            static auto pathOsConvert (
                    StringView path
            ) noexcept -> String;

        public:
            Path () noexcept = default;

        public:
            __CDS_Implicit Path (
                    StringView osPath
            ) noexcept;

        public:
            template <
                    typename __ConvertibleType,
                    cds :: meta :: EnableIf <
                            cds :: meta :: isConvertibleToBaseStringView < __ConvertibleType, char > ()
                    > = 0
            > __CDS_Implicit Path (
                    __ConvertibleType && osPath
            ) noexcept;

        public:
            Path (
                    Path const & path
            ) noexcept;

        public:
            constexpr Path (
                    Path && path
            ) noexcept;

        public:
            ~Path () noexcept override = default;

        public:
            auto operator = (
                    Path const & path
            ) noexcept -> Path &;

        public:
            auto operator = (
                    Path && path
            ) noexcept -> Path &;

        public:
            auto operator = (
                    StringView osPath
            ) noexcept -> Path &;

        public:
            template <
                    typename __ConvertibleType,
                    cds :: meta :: EnableIf <
                            cds :: meta :: isConvertibleToBaseStringView < __ConvertibleType, char > ()
                    > = 0
            > auto operator = (
                    __ConvertibleType && osPath
            ) noexcept -> Path &;

        public:
            __CDS_NoDiscard auto parent () const noexcept -> Path;

        public:
            __CDS_NoDiscard auto node () const noexcept -> StringView;

        public:
            __CDS_NoDiscard auto root () const noexcept -> Path;

        public:
            __CDS_NoDiscard auto sanitize () const noexcept -> Path;

        public:
            __CDS_NoDiscard auto asAbsolute () const noexcept (false) -> Path;

        public:
            __CDS_NoDiscard auto operator / (
                    StringView node
            ) const noexcept -> Path;

        public:
            auto operator /= (
                    StringView node
            ) noexcept -> Path &;

        public:
            __CDS_NoDiscard auto operator + (
                    StringView node
            ) const noexcept -> Path;

        public:
            auto operator += (
                    StringView node
            ) noexcept -> Path &;

        public:
            auto append (
                    StringView node
            ) noexcept -> Path &;

        public:
            __CDS_NoDiscard auto isRelative () const noexcept -> bool;

        public:
            __CDS_NoDiscard auto isAbsolute () const noexcept -> bool;

        public:
            __CDS_NoDiscard auto exists () const noexcept -> bool;

        public:
            __CDS_NoDiscard auto walk (
                    Size maxDepth = cds :: limits :: U64_MAX
            ) const noexcept -> Array < WalkEntry >;

        public:
            __CDS_NoDiscard auto operator == (
                    Path const & path
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard auto operator != (
                    Path const & path
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard auto operator == (
                    StringView path
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard auto operator != (
                    StringView path
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard auto toString () const noexcept -> String override;

        public:
            __CDS_NoDiscard auto hash () const noexcept -> Size override;

        public:
            __CDS_NoDiscard auto equals (
                    Object const & object
            ) const noexcept -> bool override;
        };

    } /* namespace filesystem */
} /* namespace cds */

#include "../../shared/util/PathWalk.hpp"
#include "../../shared/util/JsonLoad.hpp"
#include "path/impl/Path.hpp"

#endif /* __CDS_PATH_HPP__ */
