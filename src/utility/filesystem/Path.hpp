/*
 * Created by loghin on 10.05.2021.
 */

#ifndef __CDS_PATH_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_PATH_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/LinkedList>

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace filesystem {

        class WalkEntry;

        class Path : public Object {

        public:
            static char const directorySeparator;

        private:
            String _osPath;

        public:
            Path () noexcept = default;

        public:
            Path (
                    StringView osPath
            ) noexcept;

        public:
            Path (
                    Path const & path
            ) noexcept;

        public:
            Path (
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
            __CDS_NoDiscard auto parent () const noexcept -> Path;

        public:
            __CDS_NoDiscard auto node () const noexcept -> StringView;

        public:
            __CDS_NoDiscard auto root () const noexcept -> Path;

        public:
            __CDS_NoDiscard auto operator / (
                    StringView node
            ) const noexcept -> Path;

        public:
            __CDS_NoDiscard auto operator /= (
                    StringView node
            ) noexcept -> Path &;

        public:
            __CDS_NoDiscard auto operator + (
                    StringView node
            ) const noexcept -> Path;

        public:
            __CDS_NoDiscard auto operator += (
                    StringView node
            ) noexcept -> Path &;

        public:
            __CDS_NoDiscard auto append (
                    StringView node
            ) noexcept -> Path &;

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
        };

    } /* namespace filesystem */
} /* namespace cds */

#endif /* __CDS_PATH_HPP__ */
