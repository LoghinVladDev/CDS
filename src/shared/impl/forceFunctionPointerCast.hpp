/*
 * Created by loghin on 12/5/2022.
 *
 * Dirtiest workaround I have ever written.
 * Cause: MSVC does not allow / allows inconsistently cast of function pointers between related classes
 *
 * In individual tests it works, but in case of complicated templates, SFINAE is too tough for MSVC
 * Workaround: Use C union
 */

#ifndef __CDS_SHARED_FORCED_FUNCTION_POINTER_CAST_HPP__
#define __CDS_SHARED_FORCED_FUNCTION_POINTER_CAST_HPP__

namespace cds {
    namespace __hidden {
        namespace __impl {

            template < typename __To, typename __From >
            constexpr auto __forceFunctionPointerCast ( __From from ) noexcept -> __To {

                union {
                    __From __original;
                    __To   __casted;
                } caster;

                caster.__original = from;
                return caster.__casted;
            }

        }
    }
}

#endif /* __CDS_SHARED_FORCED_FUNCTION_POINTER_CAST_HPP__ */
