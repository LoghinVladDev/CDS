set(
    CDS_UNIT_TEST_SOURCES

    valid/bindings/ContainsOfStaticBinding.cpp
    valid/bindings/FindStaticBinding.cpp
    valid/bindings/FindOfStaticBinding.cpp

    valid/ds/HashTableBase.cpp

    valid/iterator/AddressIterator.cpp
    valid/iterator/HashTableIterator.cpp

    valid/functional/Comparator.cpp
    valid/functional/FunctionalInterface.cpp
    valid/functional/Hash.cpp
    valid/functional/Transformer.cpp

    valid/meta/MetaStdLib.cpp
    valid/meta/MetaBase.cpp
    valid/meta/MetaCompilerLinuxClang.test.cpp
    valid/meta/MetaCompilerLinuxGcc.test.cpp
    valid/meta/MetaFunctionTraits.cpp
    valid/meta/MetaIteratorTraits.cpp
    valid/meta/MetaObjectTraits.cpp
    valid/meta/MetaStringTraits.cpp
    valid/meta/MetaTypeTraits.cpp
    valid/meta/Utility.cpp

    valid/memory/Allocator.cpp
    valid/memory/ByteStorage.cpp

    valid/policy/RehashPolicy.cpp

    valid/primitive/StringUtils.cpp
    valid/primitive/StringView.cpp

    PARENT_SCOPE
)

set(
    CDS_UNIT_TEST_OPTIONS_MACROS
    CDS_OPTION_COMPAT_STD
    PARENT_SCOPE
)
