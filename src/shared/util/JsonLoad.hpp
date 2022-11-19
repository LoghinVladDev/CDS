/*
 * Created by loghin on 17/11/22.
 */

#if defined (__CDS_JSON_HPP__) && defined (__CDS_PATH_HPP__) && ! defined (__CDS_SHARED_UTIL_JSON_LOAD_HPP__)
#define __CDS_SHARED_UTIL_JSON_LOAD_HPP__

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace json {

        __CDS_NoDiscard auto loadJson (
                filesystem :: Path const & path
        ) noexcept (false) -> JsonObject {

            return JsonObject (
                    ( std :: stringstream () << std :: ifstream ( path.toString().cStr() ).rdbuf() ).str()
            );
        }

        __CDS_NoDiscard auto loadJsonArray (
                filesystem :: Path const & path
        ) noexcept (false) -> JsonArray {

            return JsonArray (
                    ( std :: stringstream () << std :: ifstream ( path.toString().cStr() ).rdbuf() ).str()
            );
        }

    }
}

#endif /* __CDS_SHARED_UTIL_JSON_LOAD_HPP__ */
