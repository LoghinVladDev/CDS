/*
 * Created by loghin on 19/11/22.
 */

#if defined (__CDS_WALK_HPP__) && defined (__CDS_PATH_HPP__) && ! defined(__CDS_SHARED_PATH_WALK_HPP__) /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_PATH_WALK_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {
    namespace filesystem {

        inline auto Path :: walk (
                Size maxDepth
        ) const noexcept -> Array < WalkEntry > {

            return cds :: filesystem :: walk ( this->_osPath, maxDepth );
        }

    }
}

#endif /* __CDS_SHARED_PATH_WALK_HPP__ */
