/* NOLINT(llvm-header-guard)
 * Created by loghin on 24/10/22.
 */

#ifndef __CDS_THREAD_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_THREAD_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    inline Thread :: Thread ( /* NOLINT(*-member-init) */
            Thread && thread
    ) noexcept {

        (void) std :: memcpy (
                & this->_handle,
                & thread._handle,
                sizeof ( cds :: __hidden :: __impl :: __ThreadPlatformHandleType )
        );

        (void) std :: memset (
                & thread._handle,
                0,
                sizeof ( cds :: __hidden :: __impl :: __ThreadPlatformHandleType )
        );
    }


    inline Thread :: ~Thread () noexcept {

        cds :: __hidden :: __impl :: __threadPlatformKill ( & this->_handle );
    }


    inline auto Thread :: launch (
            void * pArgument
    ) noexcept (false) -> cds :: __hidden :: __impl :: __ThreadPlatformFunctionReturnType {

        auto * pThread = reinterpret_cast < Thread * > ( pArgument ); /* NOLINT(clion-misra-cpp2008-5-2-8, *-reinterpret-cast) */
        pThread->run();
        return cds :: __hidden :: __impl :: __threadPlatformFunctionReturn;
    }


    inline auto Thread :: hardwareConcurrency () noexcept -> Size {

        return cds :: __hidden :: __impl :: __threadPlatformHardwareConcurrency();
    }


    inline auto Thread :: start () noexcept -> void {

        cds :: __hidden :: __impl :: __threadPlatformLaunch (
                & this->_handle,
                & Thread :: launch,
                reinterpret_cast < void * > ( this )    /* NOLINT(clion-misra-cpp2008-5-2-8, *-reinterpret-cast) */
        );
    }


    inline auto Thread :: kill () noexcept -> void {

        cds :: __hidden :: __impl :: __threadPlatformKill (
                & this->_handle
        );
    }


    inline auto Thread :: join () noexcept -> void {

        cds :: __hidden :: __impl :: __threadPlatformJoin (
                & this->_handle
        );
    }


    inline auto Thread :: currentThreadID () noexcept -> cds :: __hidden :: __impl :: __ThreadPlatformIdType {

        return cds :: __hidden :: __impl :: __threadPlatformCurrentId ();
    }


    inline auto Thread :: toString () const noexcept -> String {

        std :: stringstream oss;
        oss << "Thread at " << std::hex << reinterpret_cast < Size > ( this );  /* NOLINT(clion-misra-cpp2008-5-2-8, *-reinterpret-cast, clion-misra-cpp2008-5-2-5, clion-misra-cpp2008-5-2-9) */
        return oss.str();
    }


    inline auto Thread :: equals (
            Object const & object
    ) const noexcept -> bool {

        if ( this == & object ) {
            return true;
        }

        auto const * pThread = reinterpret_cast < decltype (this) > ( & object );   /* NOLINT(clion-misra-cpp2008-5-2-8, *-reinterpret-cast) */
        if ( pThread == nullptr ) {
            return false;
        }

        return std :: memcmp (
                & this->_handle,
                & pThread->_handle,
                sizeof ( cds :: __hidden :: __impl :: __ThreadPlatformHandleType )
        ) == 0;
    }


    inline auto Thread :: hash () const noexcept -> Size {

#if defined(__APPLE__)
        cds::uint64 id;
        pthread_threadid_np(this->currentThreadID(), &id);
        return id;
#else
        return cds :: hash ( static_cast < Size > ( this->currentThreadID() ) );
#endif
    }


    template < typename __ThreadFunction >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto Runnable < __ThreadFunction > :: run () noexcept (false) -> void {

        this->_function ();
    }


    template < typename __ThreadFunction >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline Runnable < __ThreadFunction > :: Runnable (
            Runnable && runnable
    ) noexcept :
            Thread ( std :: move ( runnable ) ) {

    }


    template < typename __ThreadFunction >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline Runnable < __ThreadFunction > :: Runnable (
            __ThreadFunction threadFunction
    ) noexcept :
            Thread (),
            _function ( threadFunction ) {

    }


    template < typename __ThreadFunction >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto Runnable < __ThreadFunction > :: toString () const noexcept -> String {

        std :: stringstream oss;
        oss << "Runnable Thread at " << std::hex << reinterpret_cast < Size > ( this ); /* NOLINT(clion-misra-cpp2008-5-2-8, *-reinterpret-cast, clion-misra-cpp2008-5-2-5, clion-misra-cpp2008-5-2-9) */
        return oss.str();
    }

} /* namespace cds */

#endif /* __CDS_THREAD_IMPL_HPP__ */
