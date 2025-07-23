if (CMAKE_SIZEOF_VOID_P EQUAL 4)
  set(
      CDS_UNIT_TEST_SOURCES

      valid/algorithm/GenericContains.cpp
      valid/algorithm/GenericFind.cpp
      valid/algorithm/GenericLoop.cpp

      valid/bindings/ContainsOfStaticBinding.cpp
      valid/bindings/FindStaticBinding.cpp
      valid/bindings/FindOfStaticBinding.cpp
      valid/bindings/GenericLoopBinding.cpp

      valid/ds/SingleLinkedListBase_x86.cpp
      valid/ds/HashTableBase_x86.cpp

      valid/exception/ExceptionTest.cpp
      valid/exception/NoSuchElementExceptionTest.cpp
      valid/exception/RuntimeExceptionTest.cpp
      valid/exception/UnionTypeExceptionTest.cpp

      valid/functional/Comparator.cpp
      valid/functional/FunctionalInterface.cpp
      valid/functional/Hash_x86.cpp
      valid/functional/Invoke.cpp
      valid/functional/Transformer.cpp

      valid/iterator/Iterator_x86.cpp
      valid/iterator/AddressIterator_x86.cpp
      valid/iterator/FwdNodeIterator.cpp
      valid/iterator/HashTableIterator_x86.cpp

      valid/memory/Allocator_x86.cpp
      valid/memory/ByteStorage_x86.cpp

      valid/meta/MetaBase_x86.cpp
      valid/meta/MetaCompilerAppleClang.test.cpp
      valid/meta/MetaCompilerLinuxClang_x86.test.cpp
      valid/meta/MetaCompilerLinuxGcc_x86.test.cpp
      valid/meta/MetaFunctionTraits_x86.cpp
      valid/meta/MetaIteratorTraits.cpp
      valid/meta/MetaObjectTraits.cpp
      valid/meta/MetaSemantics.cpp
      valid/meta/MetaStdLib.cpp
      valid/meta/MetaStringTraits_x86.cpp
      valid/meta/MetaTypeTraits_x86.cpp
      valid/meta/Utility_x86.cpp

      valid/policy/RehashPolicy_x86.cpp

      valid/primitive/OptionalTest.cpp
      valid/primitive/StringAbstract_x86.cpp
      valid/primitive/StringUtils_x86.cpp
      valid/primitive/string/String_char_Allocator_x86.cpp
      valid/primitive/string/String_wchar_t_Allocator_x86.cpp
      valid/primitive/string/String_char8_t_Allocator_x86.cpp
      valid/primitive/string/String_char16_t_Allocator_x86.cpp
      valid/primitive/string/String_char32_t_Allocator_x86.cpp
      valid/primitive/string/String_char_TrackerAllocator_x86.cpp
      valid/primitive/string/String_wchar_t_TrackerAllocator_x86.cpp
      valid/primitive/string/String_char8_t_TrackerAllocator_x86.cpp
      valid/primitive/string/String_char16_t_TrackerAllocator_x86.cpp
      valid/primitive/string/String_char32_t_TrackerAllocator_x86.cpp
      valid/primitive/string_view/StringView_char_x86.cpp
      valid/primitive/string_view/StringView_wchar_t_x86.cpp
      valid/primitive/string_view/StringView_char8_t_x86.cpp
      valid/primitive/string_view/StringView_char16_t_x86.cpp
      valid/primitive/string_view/StringView_char32_t_x86.cpp
      valid/primitive/UnionTest.cpp
      valid/primitive/TupleTest.cpp

      valid/stdlib/StringViewStdLibCompatNone_x86.cpp
      valid/stdlib/StringViewStdLibCompatSafe_x86.cpp
      valid/stdlib/StringViewStdLibCompatUnsafe_x86.cpp

      valid/utils/TrackerAllocator.cpp

      PARENT_SCOPE
  )
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(CDS_ALGORITHM_UNIT_TEST_SOURCES
      valid/algorithm/GenericContains.cpp
      valid/algorithm/GenericFind.cpp
      valid/algorithm/GenericLoop.cpp)

  set(CDS_BINDINGS_UNIT_TEST_SOURCES
      valid/bindings/ContainsOfStaticBinding.cpp
      valid/bindings/FindStaticBinding.cpp
      valid/bindings/FindOfStaticBinding.cpp
      valid/bindings/GenericLoopBinding.cpp)

  set(CDS_COLLECTION_UNIT_TEST_SOURCES
      valid/collection/HashMapBaseTest.cpp
      valid/collection/HashMapTest.cpp
      valid/collection/LinkedHashMapTest.cpp
      valid/collection/VectorTest.cpp
      valid/collection/VectorViewTest.cpp)

  set(CDS_DATA_STRUCTURES_UNIT_TEST_SOURCES
      valid/ds/ArrayBaseTest.cpp
      valid/ds/ArrayDynamicBackScalingBaseTest.cpp
      valid/ds/ArrayTraitsTest.cpp
      valid/ds/SingleLinkedListBase.cpp
      valid/ds/HashTableBase.cpp
      valid/ds/MapBaseTest.cpp
      valid/ds/MapEntryTest.cpp
      valid/ds/JsonArrayParserTest.cpp
      valid/ds/JsonArrayTest.cpp
      valid/ds/JsonArrayPrinterTest.cpp
      valid/ds/JsonCommonParsersTest.cpp
      valid/ds/JsonNodeParserTest.cpp
      valid/ds/JsonNodePrinterTest.cpp
      valid/ds/JsonNodeTest.cpp
      valid/ds/JsonObjectParserTest.cpp
      valid/ds/JsonObjectPrinterTest.cpp
      valid/ds/JsonObjectTest.cpp
      valid/ds/JsonPrinterBaseTest.cpp
      valid/ds/JsonPrinterContextTest.cpp
      valid/ds/JsonPrinterIndenterTest.cpp
      valid/ds/JsonPrinterOutputStreamTest.cpp
      valid/ds/JsonPrinterOutputStringTest.cpp
      valid/ds/JsonPrinterTest.cpp
      valid/ds/JsonElementPresenterTest.cpp)

  set(CDS_EXCEPTION_UNIT_TEST_SOURCES
      valid/exception/ExceptionTest.cpp
      valid/exception/NoSuchElementExceptionTest.cpp
      valid/exception/RuntimeExceptionTest.cpp
      valid/exception/UnionTypeExceptionTest.cpp)

  set(CDS_FILESYSTEM_UNIT_TEST_SOURCES
      valid/filesystem/PathPosixTest.cpp)

  set(CDS_FORMAT_UNIT_TEST_SOURCES
      valid/format/FormatStringIteratorTest.cpp
      valid/format/FormatTest.cpp
      valid/format/RangeFormatTest.cpp
      valid/format/StandardFormatSpecificationExtTest.cpp
      valid/format/StandardFormatSpecificationTest.cpp
      valid/format/TupleFormatTest.cpp)

  set(CDS_FUNCTIONAL_UNIT_TEST_SOURCES
      valid/functional/Comparator.cpp
      valid/functional/FunctionalInterface.cpp
      valid/functional/Hash.cpp
      valid/functional/Invoke.cpp
      valid/functional/Transformer.cpp)

  set(CDS_ITERATOR_UNIT_TEST_SOURCES
      valid/iterator/Iterator.cpp
      valid/iterator/AddressIterator.cpp
      valid/iterator/FwdNodeIterator.cpp
      valid/iterator/HashTableIterator.cpp)

  set(CDS_MEMORY_UNIT_TEST_SOURCES
      valid/memory/Allocator.cpp
      valid/memory/ByteStorage.cpp
      valid/memory/SharedPtrTest.cpp
      valid/memory/UniquePtrTest.cpp)

  set(CDS_META_UNIT_TEST_SOURCES
      valid/meta/MetaBase.cpp
      valid/meta/MetaCompilerAppleClang.test.cpp
      valid/meta/MetaCompilerLinuxClang.test.cpp
      valid/meta/MetaCompilerLinuxGcc.test.cpp
      valid/meta/MetaFunctionTraits.cpp
      valid/meta/MetaIteratorTraits.cpp
      valid/meta/MetaObjectTraits.cpp
      valid/meta/MetaSemantics.cpp
      valid/meta/MetaStdLib.cpp
      valid/meta/MetaStringTraits.cpp
      valid/meta/MetaTypeTraits.cpp
      valid/meta/Utility.cpp)

  set(CDS_POLICY_UNIT_TEST_SOURCES
      valid/policy/RehashPolicy.cpp)

  set(CDS_PRIMITIVE_UNIT_TEST_SOURCES
      valid/primitive/OptionalTest.cpp
      valid/primitive/StringAbstract.cpp
      valid/primitive/StringUtils.cpp
      valid/primitive/string/String_char_Allocator.cpp
      valid/primitive/string/String_wchar_t_Allocator.cpp
      valid/primitive/string/String_char8_t_Allocator.cpp
      valid/primitive/string/String_char16_t_Allocator.cpp
      valid/primitive/string/String_char32_t_Allocator.cpp
      valid/primitive/string/String_char_TrackerAllocator.cpp
      valid/primitive/string/String_wchar_t_TrackerAllocator.cpp
      valid/primitive/string/String_char8_t_TrackerAllocator.cpp
      valid/primitive/string/String_char16_t_TrackerAllocator.cpp
      valid/primitive/string/String_char32_t_TrackerAllocator.cpp
      valid/primitive/string_view/StringView_char.cpp
      valid/primitive/string_view/StringView_wchar_t.cpp
      valid/primitive/string_view/StringView_char8_t.cpp
      valid/primitive/string_view/StringView_char16_t.cpp
      valid/primitive/string_view/StringView_char32_t.cpp
      valid/primitive/UnionTest.cpp
      valid/primitive/TupleTest.cpp)

  set(CDS_STDLIB_UNIT_TEST_SOURCES
      valid/stdlib/StringViewStdLibCompatNone.cpp
      valid/stdlib/StringViewStdLibCompatSafe.cpp
      valid/stdlib/StringViewStdLibCompatUnsafe.cpp)

  set(CDS_THREADING_UNIT_TEST_SOURCES
      valid/threading/AtomicTest.cpp)

  set(CDS_UTILS_UNIT_TEST_SOURCES
      valid/utils/TrackerAllocator.cpp)

  set(CDS_DEFAULT_UNIT_TEST_SOURCES
      ${CDS_ALGORITHM_UNIT_TEST_SOURCES}
      ${CDS_BINDINGS_UNIT_TEST_SOURCES}
      ${CDS_COLLECTION_UNIT_TEST_SOURCES}
      ${CDS_DATA_STRUCTURES_UNIT_TEST_SOURCES}
      ${CDS_EXCEPTION_UNIT_TEST_SOURCES}
      ${CDS_FILESYSTEM_UNIT_TEST_SOURCES}
      ${CDS_FORMAT_UNIT_TEST_SOURCES}
      ${CDS_FUNCTIONAL_UNIT_TEST_SOURCES}
      ${CDS_ITERATOR_UNIT_TEST_SOURCES}
      ${CDS_MEMORY_UNIT_TEST_SOURCES}
      ${CDS_META_UNIT_TEST_SOURCES}
      ${CDS_POLICY_UNIT_TEST_SOURCES}
      ${CDS_PRIMITIVE_UNIT_TEST_SOURCES}
      ${CDS_STDLIB_UNIT_TEST_SOURCES}
      ${CDS_THREADING_UNIT_TEST_SOURCES}
      ${CDS_UTILS_UNIT_TEST_SOURCES})

  set(CDS_UNIT_TEST_SOURCES
      ${CDS_DEFAULT_UNIT_TEST_SOURCES}
      PARENT_SCOPE)
endif()

set(
    CDS_UNIT_TEST_OPTIONS_MACROS
    CDS_OPTION_COMPAT_STD
    PARENT_SCOPE
)
