#if !defined(_MSC_VER)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-macro-parentheses"
#endif
//
// Created by loghin on 05.04.2021.
//

#include "StringTest.h"

#include <CDS/String>
#include <CDS/Range>

auto StringTest::execute() noexcept -> bool {
    bool allOk = true;
    this->logBold("Start of test String....");

    this->executeSubtest("Constructor Tests", [this, & allOk] {
        String empty;
        this->log("Empty String Constructed : %s, %s", empty.cStr(), empty.diag().cStr());
        if (!empty.empty()) {
            this->logWarning("Empty String Unexpected Error");
            allOk = false;
        }

        String b = "Test String to be copied";
        String copy(b);
        this->log("String Constructed with Copy Constructor : Original : '%s', Copy : '%s'. Copy Diag : %s",
                  b.cStr(), copy.cStr(), copy.diag().cStr());
        if (b != copy) {
            this->logWarning("Copy String Unexpected Error");
            allOk = false;
        }

        const char *literal = "Test StringLiteral to be copied";
        String literalCopy(literal);
        this->log("String Constructed with StringLiteral : Original : '%s', String : '%s'. Diag : '%s'",
                  literal,
                  literalCopy.cStr(),
                  literalCopy.diag().cStr()
        );

        if (literalCopy != literal) {
            this->logWarning("StringLiteral Constructor Error");
            allOk = false;
        }

        std::string stdString = "std::string to be copied";
        String stdCopy(stdString);
        this->log("String Constructed with std::string : Original : '%s', String : '%s'. Diag : %s",
                  stdString.c_str(),
                  stdCopy.cStr(),
                  stdCopy.diag().cStr()
        );

        if (stdCopy != stdString) {
            this->logWarning("std::string construction Error");
            allOk = false;
        }

        String defaultedString(10, 'a');
        this->log("String Constructed with default values : '%s'. Diag : %s", defaultedString.cStr(),
                  defaultedString.diag().cStr());

        if (defaultedString != "aaaaaaaaaa") {
            this->logWarning("String with default values construction Error");
            allOk = false;
        }

        std::string stdStringIt = "String that will be iterated. Should not appear";
        String iteratedStd(stdStringIt.begin(), stdStringIt.end().operator-=(strlen(" Should not appear")));
        this->log("String Constructed with std::string iterators : Intended : '%s'. Result : '%s'. Diag : %s",
                  std::string(stdStringIt.begin(), stdStringIt.end().operator-=(strlen(" Should not appear"))).c_str(),
                  iteratedStd.cStr(),
                  iteratedStd.diag().cStr()
        );

        if (iteratedStd !=
            std::string(stdStringIt.begin(), stdStringIt.end().operator-=(strlen(" Should not appear")))) {
            this->logWarning("String from std::string iterators construction Error");
            allOk = false;
        }

        String stringIt = "String that will be iterated";
        String iterated(stringIt.begin(), stringIt.end());
        this->log("String Constructed with String iterators : Intended : '%s', Result : '%s'. Diag : %s",
                  stringIt.cStr(),
                  iterated.cStr(),
                  iterated.diag().cStr()
        );

        if (iterated != stringIt) {
            this->logWarning("String from String iterators construction Error");
            allOk = false;
        }

        iterated = String(stringIt.cbegin(), stringIt.cend());
        this->log("String Constructed with String const iterators : Intended : '%s', Result : '%s'. Diag : %s",
                  stringIt.cStr(),
                  iterated.cStr(),
                  iterated.diag().cStr()
        );

        if (iterated != stringIt) {
            this->logWarning("String from String const iterators construction Error");
            allOk = false;
        }

        iterated = String(stringIt.rbegin(), stringIt.rend());
        this->log("String Constructed with String reverse iterators : Intended : '%s', Result : '%s'. Diag : %s",
                  stringIt.reversed().cStr(),
                  iterated.cStr(),
                  iterated.diag().cStr()
        );

        if (iterated != stringIt.reversed()) {
            this->logWarning("String from String reverse iterators construction Error");
            allOk = false;
        }

        iterated = String(stringIt.crbegin(), stringIt.crend());
        this->log(
                "String Constructed with String const reverse iterators : Intended : '%s', Result : '%s'. Diag : %s",
                stringIt.reversed().cStr(),
                iterated.cStr(),
                iterated.diag().cStr()
        );

        if (iterated != stringIt.reversed()) {
            this->logWarning("String from String const reverse iterators construction Error");
            allOk = false;
        }

        String initialized = {'S', 'a', 'm', 'p', 'l', 'e', ' ', 'S', 't', 'r', 'i', 'n', 'g'};
        this->log("String Constructed from std::initializer list. Intended : '%s', Result : '%s'. Diag : %s",
                  "Sample String",
                  initialized.cStr(),
                  initialized.diag().cStr()
        );

        if (initialized != "Sample String") {
            this->logWarning("String from Initializer List construction Error");
            allOk = false;
        }

    });

    this->executeSubtest("Iterator Tests", [this, & allOk] {

        String toIterate = "2345678";

        this->log("Iterating : %s", toIterate.cStr());
        std::cout << this->getDepthString() << "Regular Iteration : ";
        for (auto e : toIterate) std::cout << e << ' ';
        std::cout << "\n";

        std::cout << this->getDepthString() << "Reverse Iteration : ";
        for (auto e = toIterate.rbegin(); e != toIterate.rend(); e++) std::cout << e.value() << ' ';
        std::cout << '\n';

        std::cout << this->getDepthString() << "Regular Const Iteration : ";
        for (const auto e : toIterate) std::cout << e << ' ';
        std::cout << "\n";

        std::cout << this->getDepthString() << "Reverse Const Iteration : ";
        for (auto e = toIterate.crbegin(); e != toIterate.crend(); e++) std::cout << e.value() << ' ';
        std::cout << '\n';

        std::cout << this->getDepthString() << "Reference Iteration : ";
        for (auto &e : toIterate) std::cout << e << ' ';
        std::cout << "\n";

        std::cout << this->getDepthString() << "Const Reference Iteration : ";
        for (auto const &e : toIterate) std::cout << e << ' ';
        std::cout << "\n";

        std::cout << this->getDepthString() << "Const Reference Iteration with modification : ";
        for (auto &e : toIterate) std::cout << ++e << ' ';
        std::cout << "\n";

        this->log("New String : %s", toIterate.cStr());

        std::cout << "Reverse Iteration with modification : ";
        for (auto e = toIterate.rbegin(); e != toIterate.rend(); e++) std::cout << --e.value() << ' ';
        std::cout << '\n';

        this->log("New String : %s", toIterate.cStr());

    });

    this->executeSubtest("Property Tests", [this, &allOk] {

        Array<String> strings = {
                "Some", "strings", "to test the", "properties", "on"
        };

        for (auto const &s : strings) {
            this->log("String : '%s'. Properties : "
                      "\tlength/size : %u"
                      "\tcapacity/maxSize : %u", s.cStr(), s.size(), s.capacity());
        }

    });

    this->executeSubtest("Memory Tests", [this, &allOk] {

        String memoryOperated = "This is a sample string";

        this->log("Original String : '%s'. Diag : %s", memoryOperated.cStr(), memoryOperated.diag().cStr());
        auto memOpCopy = memoryOperated;
        memOpCopy.resize(10);
        this->log("Original shrunk to 10 with resize : '%s'. Diag : %s", memOpCopy.cStr(), memOpCopy.diag().cStr());

        auto memOpCopy2 = memoryOperated;
        memOpCopy2.resize(100);
        this->log("Original enlarged to 100 with resize : '%s'. Diag : %s", memOpCopy2.cStr(),
                  memOpCopy2.diag().cStr());


        auto memOpCopy3 = memoryOperated;
        memOpCopy3.reserve(10);
        this->log("Original attempt shrink to 10 with reserve : '%s'. Diag : %s", memOpCopy3.cStr(),
                  memOpCopy3.diag().cStr());

        auto memOpCopy4 = memoryOperated;
        memOpCopy4.reserve(100);
        this->log("Original enlarged to 100 with reserve : '%s'. Diag : %s", memOpCopy4.cStr(),
                  memOpCopy4.diag().cStr());


        auto memOpCopy5 = memoryOperated;
        memOpCopy5.shrink(10);
        this->log("Original shrunk to 10 with shrink : '%s'. Diag : %s", memOpCopy5.cStr(), memOpCopy5.diag().cStr());

        auto memOpCopy6 = memoryOperated;
        memOpCopy6.shrink(100);
        this->log("Original attepted to enlarge to 100 with shrink : '%s'. Diag : %s", memOpCopy6.cStr(),
                  memOpCopy6.diag().cStr());

    });

    this->executeSubtest("Content Functions Tests", [this, &allOk]{
        String original = "The quick brown fox jumped over the lazy dog";
        String toBeEmptied = original;

        this->log("Original String : '%s'. Diag : %s", toBeEmptied.cStr(), toBeEmptied.diag().cStr());
        toBeEmptied.clear();
        this->log("Emptied String : '%s'. Diag : %s", toBeEmptied.cStr(), toBeEmptied.diag().cStr());

        if ( ! toBeEmptied.empty() ) {
            this->logWarning("String clearing failure");
            allOk = false;
        }

        this->log("Is Original String '%s' empty: %s", original.cStr(), original.empty() ? "true" : "false" );
        this->log("Is Cleared String '%s' empty : %s", toBeEmptied.cStr(), toBeEmptied.empty() ? "true" : "false" );

        if ( ! toBeEmptied.empty() || original.empty() ) {
            this->logWarning("Empty Error");
            allOk = false;
        }

        String indexed = "abcd";
        this->log("String to be looked up : '%s'", indexed.cStr());

        Array < Index > indices = { -7, -4, -2, 0, 1, 3, 5, 8, 11, 24 };
        this->log("Indices to be accessed : %s", indices.toString().cStr());

        for ( auto i : indices )
            this->log("Index : %d, Value : %c", i, indexed[i]);

        this->log("Modification based on indices, doing ++. Original String : %s, Indices : %s", indexed.cStr(), indices.toString().cStr());
        for ( auto i : indices )
            indexed[i] ++;

        this->log("New String : %s", indexed.cStr());

        indexed = "abcd";

        this->log("Original String : '%s'", indexed.cStr());
        this->log("String's first char : %c", indexed.front());
        this->log("String's last char : %c", indexed.back());


        String container = "Test String";

        this->log("String '%s' contains '%s' : %s", container.cStr(), String("String").cStr(), container.contains(String("String")) ? "true" : "false");
        this->log("String '%s' contains '%s' : %s", container.cStr(), String("Integer").cStr(), container.contains(String("Integer")) ? "true" : "false");
        this->log("String '%s' contains '%s' : %s", container.cStr(), "String", container.contains("String") ? "true" : "false");
        this->log("String '%s' contains '%s' : %s", container.cStr(), "Integer", container.contains("Integer") ? "true" : "false");
        this->log("String '%s' contains '%s' : %s", container.cStr(), std::string("String").c_str(), container.contains(std::string("String")) ? "true" : "false");
        this->log("String '%s' contains '%s' : %s", container.cStr(), std::string("Integer").c_str(), container.contains(std::string("Integer")) ? "true" : "false");
        this->log("String '%s' contains '%c' : %s", container.cStr(), 'S', container.contains('S') ? "true" : "false");
        this->log("String '%s' contains '%c' : %s", container.cStr(), 'x', container.contains('x') ? "true" : "false");

        if ( !container.contains(String("String")) ) {
            this->logWarning("Contains Error");
            allOk = false;
        }

        if ( container.contains(String("Integer")) ) {
            this->logWarning("Contains Error");
            allOk = false;
        }

        if ( !container.contains("String") ) {
            this->logWarning("Contains Error");
            allOk = false;
        }

        if ( container.contains("Integer") ) {
            this->logWarning("Contains Error");
            allOk = false;
        }

        if ( !container.contains(std::string("String")) ) {
            this->logWarning("Contains Error");
            allOk = false;
        }

        if ( container.contains(std::string("Integer")) ) {
            this->logWarning("Contains Error");
            allOk = false;
        }

        if ( !container.contains('S') ) {
            this->logWarning("Contains Error");
            allOk = false;
        }

        if ( container.contains('x') ) {
            this->logWarning("Contains Error");
            allOk = false;
        }
    });

    this->executeSubtest("Append/Prepend Tests", [this, &allOk] {
        String original = "test string,";
        String sa = "appended string";
        std::string stdsa = "appended std::string";
        char ca = '\\';
        StringLiteral sla = "appended string literal";
        sint16 s16a = 12413;
        sint32 s32a = 21415523;
        sint64 s64a = 9142153423243612;
        uint8 u8a = 144;
        uint16 u16a = 35235;
        uint32 u32a = 2999999123;
        uint64 u64a = (uint64)INT64_MAX + 1412312;
        float fa = 512.3532467f;
        double da = 512.3532467;

        String operated = original;
        this->log("Operator + :");

        this->log("String(%s) + String(%s) = '%s'", operated.cStr(), sa.cStr(), (operated + sa).cStr());
        this->log("String(%s) + char(%c) = '%s'", operated.cStr(), ca, (operated + ca).cStr());
        this->log("String(%s) + std::string(%s) = '%s'", operated.cStr(), stdsa.c_str(), (operated + stdsa).cStr());
        this->log("String(%s) + StringLiteral(%s) = '%s'", operated.cStr(), sla, (operated + sla).cStr());
        this->log("String(%s) + int16(%d) = '%s'", operated.cStr(), s16a, (operated + s16a).cStr());
        this->log("String(%s) + int32(%ld) = '%s'", operated.cStr(), s32a, (operated + s32a).cStr());
        this->log("String(%s) + int64(%lld) = '%s'", operated.cStr(), s64a, (operated + s64a).cStr());
        this->log("String(%s) + uint8(%u) = '%s'", operated.cStr(), u8a, (operated + u8a).cStr());
        this->log("String(%s) + uint16(%u) = '%s'", operated.cStr(), u16a, (operated + u16a).cStr());
        this->log("String(%s) + uint32(%lu) = '%s'", operated.cStr(), u32a, (operated + u32a).cStr());
        this->log("String(%s) + uint64(%llu) = '%s'", operated.cStr(), u64a, (operated + u64a).cStr());
        this->log("String(%s) + float(%f) = '%s'", operated.cStr(), fa, (operated + fa).cStr());
        this->log("String(%s) + double(%lf) = '%s'", operated.cStr(), da, (operated + da).cStr());

        if ( operated + sa != "test string,appended string" ) {
            this->logWarning("String + String Error");
            allOk = false;
        }
        if ( operated + stdsa != "test string,appended std::string" ) {
            this->logWarning("String + std::string Error");
            allOk = false;
        }
        if ( operated + sla != "test string,appended string literal" ) {
            this->logWarning("String + StringLiteral Error");
            allOk = false;
        }
        if ( operated + ca != "test string,\\" ) {
            this->logWarning("String + char Error");
            allOk = false;
        }
        if ( operated + s16a != "test string,12413" ) {
            this->logWarning("String + String Error");
            allOk = false;
        }
        if ( operated + s32a != "test string,21415523" ) {
            this->logWarning("String + String Error");
            allOk = false;
        }
        if ( operated + s64a != "test string,9142153423243612" ) {
            this->logWarning("String + String Error");
            allOk = false;
        }
        if ( operated + u8a != "test string,144" ) {
            this->logWarning("String + String Error");
            allOk = false;
        }
        if ( operated + u16a != "test string,35235" ) {
            this->logWarning("String + String Error");
            allOk = false;
        }
        if ( operated + u32a != "test string,2999999123" ) {
            this->logWarning("String + String Error");
            allOk = false;
        }
        if ( operated + u64a != "test string,9223372036856188119" ) {
            this->logWarning("String + String Error");
            allOk = false;
        }

        this->log("Operator += :");

        operated = original;
        this->log("String(%s) += String(%s) = '%s'", operated.cStr(), sa.cStr(), (operated += sa).cStr());
        operated = original;
        this->log("String(%s) += char(%c) = '%s'", operated.cStr(), ca, (operated += ca).cStr());
        operated = original;
        this->log("String(%s) += std::string(%s) = '%s'", operated.cStr(), stdsa.c_str(), (operated += stdsa).cStr());
        operated = original;
        this->log("String(%s) += StringLiteral(%s) = '%s'", operated.cStr(), sla, (operated += sla).cStr());
        operated = original;
        this->log("String(%s) += int16(%d) = '%s'", operated.cStr(), s16a, (operated += s16a).cStr());
        operated = original;
        this->log("String(%s) += int32(%ld) = '%s'", operated.cStr(), s32a, (operated += s32a).cStr());
        operated = original;
        this->log("String(%s) += int64(%lld) = '%s'", operated.cStr(), s64a, (operated += s64a).cStr());
        operated = original;
        this->log("String(%s) += uint8(%u) = '%s'", operated.cStr(), u8a, (operated += u8a).cStr());
        operated = original;
        this->log("String(%s) += uint16(%u) = '%s'", operated.cStr(), u16a, (operated += u16a).cStr());
        operated = original;
        this->log("String(%s) += uint32(%lu) = '%s'", operated.cStr(), u32a, (operated += u32a).cStr());
        operated = original;
        this->log("String(%s) += uint64(%llu) = '%s'", operated.cStr(), u64a, (operated += u64a).cStr());
        operated = original;
        this->log("String(%s) += float(%f) = '%s'", operated.cStr(), fa, (operated += fa).cStr());
        operated = original;
        this->log("String(%s) += double(%lf) = '%s'", operated.cStr(), da, (operated += da).cStr());
        operated = original;

        if ( (operated += sa) != "test string,appended string" ) {
            this->logWarning("String += String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated += stdsa) != "test string,appended std::string" ) {
            this->logWarning("String += std::string Error");
            allOk = false;
        }
        operated = original;
        if ( (operated += sla) != "test string,appended string literal" ) {
            this->logWarning("String += StringLiteral Error");
            allOk = false;
        }
        operated = original;
        if ( (operated += ca) != "test string,\\" ) {
            this->logWarning("String += char Error");
            allOk = false;
        }
        operated = original;
        if ( (operated += s16a) != "test string,12413" ) {
            this->logWarning("String += String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated += s32a) != "test string,21415523" ) {
            this->logWarning("String += String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated += s64a) != "test string,9142153423243612" ) {
            this->logWarning("String += String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated += u8a) != "test string,144" ) {
            this->logWarning("String += String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated += u16a) != "test string,35235" ) {
            this->logWarning("String += String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated += u32a) != "test string,2999999123" ) {
            this->logWarning("String += String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated += u64a) != "test string,9223372036856188119" ) {
            this->logWarning("String += String Error");
            allOk = false;
        }

        this->log("Append :");

        operated = original;
        this->log("String(%s) append String(%s) = '%s'", operated.cStr(), sa.cStr(), (operated.append(sa)).cStr());
        operated = original;
        operated = original;
        this->log("String(%s) append char(%c) = '%s'", operated.cStr(), ca, (operated.append(ca)).cStr());
        operated = original;
        this->log("String(%s) append std::string(%s) = '%s'", operated.cStr(), stdsa.c_str(), (operated.append(stdsa)).cStr());
        operated = original;
        this->log("String(%s) append StringLiteral(%s) = '%s'", operated.cStr(), sla, (operated.append(sla)).cStr());
        operated = original;
        this->log("String(%s) append int16(%d) = '%s'", operated.cStr(), s16a, (operated.append(s16a)).cStr());
        operated = original;
        this->log("String(%s) append int32(%ld) = '%s'", operated.cStr(), s32a, (operated.append(s32a)).cStr());
        operated = original;
        this->log("String(%s) append int64(%lld) = '%s'", operated.cStr(), s64a, (operated.append(s64a)).cStr());
        operated = original;
        this->log("String(%s) append uint8(%u) = '%s'", operated.cStr(), u8a, (operated.append(u8a)).cStr());
        operated = original;
        this->log("String(%s) append uint16(%u) = '%s'", operated.cStr(), u16a, (operated.append(u16a)).cStr());
        operated = original;
        this->log("String(%s) append uint32(%lu) = '%s'", operated.cStr(), u32a, (operated.append(u32a)).cStr());
        operated = original;
        this->log("String(%s) append uint64(%llu) = '%s'", operated.cStr(), u64a, (operated.append(u64a)).cStr());
        operated = original;
        this->log("String(%s) append float(%f) = '%s'", operated.cStr(), fa, (operated.append(fa)).cStr());
        operated = original;
        this->log("String(%s) append double(%lf) = '%s'", operated.cStr(), da, (operated.append(da)).cStr());

        operated = original;
        if ( (operated.append(sa)) != "test string,appended string" ) {
            this->logWarning("String append String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.append(stdsa)) != "test string,appended std::string" ) {
            this->logWarning("String append std::string Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.append(sla)) != "test string,appended string literal" ) {
            this->logWarning("String append StringLiteral Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.append(ca)) != "test string,\\" ) {
            this->logWarning("String append char Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.append(s16a)) != "test string,12413" ) {
            this->logWarning("String append String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.append(s32a)) != "test string,21415523" ) {
            this->logWarning("String append String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.append(s64a)) != "test string,9142153423243612" ) {
            this->logWarning("String append String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.append(u8a)) != "test string,144" ) {
            this->logWarning("String append String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.append(u16a)) != "test string,35235" ) {
            this->logWarning("String append String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.append(u32a)) != "test string,2999999123" ) {
            this->logWarning("String append String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.append(u64a)) != "test string,9223372036856188119" ) {
            this->logWarning("String append String Error");
            allOk = false;
        }

        this->log("Prepend :");

        operated = original;
        this->log("String(%s) prepend String(%s) = '%s'", operated.cStr(), sa.cStr(), (operated.prepend(sa)).cStr());
        operated = original;
        operated = original;
        this->log("String(%s) prepend char(%c) = '%s'", operated.cStr(), ca, (operated.prepend(ca)).cStr());
        operated = original;
        this->log("String(%s) prepend std::string(%s) = '%s'", operated.cStr(), stdsa.c_str(), (operated.prepend(stdsa)).cStr());
        operated = original;
        this->log("String(%s) prepend StringLiteral(%s) = '%s'", operated.cStr(), sla, (operated.prepend(sla)).cStr());
        operated = original;
        this->log("String(%s) prepend int16(%d) = '%s'", operated.cStr(), s16a, (operated.prepend(s16a)).cStr());
        operated = original;
        this->log("String(%s) prepend int32(%ld) = '%s'", operated.cStr(), s32a, (operated.prepend(s32a)).cStr());
        operated = original;
        this->log("String(%s) prepend int64(%lld) = '%s'", operated.cStr(), s64a, (operated.prepend(s64a)).cStr());
        operated = original;
        this->log("String(%s) prepend uint8(%u) = '%s'", operated.cStr(), u8a, (operated.prepend(u8a)).cStr());
        operated = original;
        this->log("String(%s) prepend uint16(%u) = '%s'", operated.cStr(), u16a, (operated.prepend(u16a)).cStr());
        operated = original;
        this->log("String(%s) prepend uint32(%lu) = '%s'", operated.cStr(), u32a, (operated.prepend(u32a)).cStr());
        operated = original;
        this->log("String(%s) prepend uint64(%llu) = '%s'", operated.cStr(), u64a, (operated.prepend(u64a)).cStr());
        operated = original;
        this->log("String(%s) prepend float(%f) = '%s'", operated.cStr(), fa, (operated.prepend(fa)).cStr());
        operated = original;
        this->log("String(%s) prepend double(%lf) = '%s'", operated.cStr(), da, (operated.prepend(da)).cStr());

        operated = original;
        if ( (operated.prepend(sa)) != "appended stringtest string," ) {
            this->logWarning("String prepend String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.prepend(stdsa)) != "appended std::stringtest string," ) {
            this->logWarning("String prepend std::string Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.prepend(sla)) != "appended string literaltest string," ) {
            this->logWarning("String prepend StringLiteral Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.prepend(ca)) != "\\test string," ) {
            this->logWarning("String prepend char Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.prepend(s16a)) != "12413test string," ) {
            this->logWarning("String prepend String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.prepend(s32a)) != "21415523test string," ) {
            this->logWarning("String prepend String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.prepend(s64a)) != "9142153423243612test string," ) {
            this->logWarning("String prepend String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.prepend(u8a)) != "144test string," ) {
            this->logWarning("String prepend String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.prepend(u16a)) != "35235test string," ) {
            this->logWarning("String prepend String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.prepend(u32a)) != "2999999123test string," ) {
            this->logWarning("String prepend String Error");
            allOk = false;
        }
        operated = original;
        if ( (operated.prepend(u64a)) != "9223372036856188119test string," ) {
            this->logWarning("String prepend String Error");
            allOk = false;
        }

    });

    this->executeSubtest("Find Tests", [this, &allOk] {
        String str = "This is a sample string";
        this->log("Original String : '%s'", str.cStr());

        this->log("Find of char 'a' : %s", str.find('a').toString().cStr());
        if ( str.find('a') != LinkedList < Index > { 8, 11 } ) {
            this->logWarning("Find char error");
            allOk = false;
        }

        this->log("Find of string 'is' : %s", str.find("is").toString().cStr());
        if ( str.find("is") != LinkedList < Index > { 2, 5 } ) {
            this->logWarning("Find string error");
            allOk = false;
        }

        this->log("Find of characters 'a', ' ', 's' : %s", str.findOf("as ").toString().cStr());
        if ( str.findOf("as ") != LinkedList < Index > { 3, 4, 6, 7, 8, 9, 10, 11, 16, 17 } ) {
            this->logWarning("Find of String error");
            allOk = false;
        }

        this->log("Find characters not 'a' 's' ' ' : %s", str.findNotOf("as ").toString().cStr());
        if ( str.findNotOf("as ") != LinkedList < Index > { 0, 1, 2, 5, 12, 13, 14, 15, 18, 19, 20, 21, 22 } ) {
            this->logWarning("Find not of String error");
            allOk = false;
        }

        this->log("First 'm' index : %d", str.findFirst('m'));
        if ( str.findFirst('m') != 12 ) {
            this->logWarning("Find First error");
            allOk = false;
        }

        this->log("First 'x' index : %d", str.findFirst('x'));
        if ( str.findFirst('x') != String::INVALID_POS ) {
            this->logWarning("Find First non-existent error");
            allOk = false;
        }

        this->log("First 'is' index : %d", str.findFirst("is"));
        if ( str.findFirst("is") != 2 ) {
            this->logWarning("Find First Error");
            allOk = false;
        }

        this->log("First 'isn't' index : %d", str.findFirst("isn't"));
        if ( str.findFirst("isn't") != String::INVALID_POS ) {
            this->logWarning("Find First Error");
            allOk = false;
        }

        this->log("Last 'a' index : %d", str.findLast('a'));
        if ( str.findLast('a') != 11 ) {
            this->logWarning("Find Last Char error");
            allOk = false;
        }

        this->log("Last 'x' index : %d", str.findLast('x'));
        if ( str.findLast('x') != String::INVALID_POS ) {
            this->logWarning("Find Last Char error");
            allOk = false;
        }

        this->log("Last 'is' index : %d", str.findLast("is"));
        if ( str.findLast("is") != 5 ) {
            this->logWarning("Find Last String error");
            allOk = false;
        }

        this->log("Last 'isn't' index : %d", str.findLast("isn't"));
        if ( str.findLast("isn't") != String::INVALID_POS ) {
            this->logWarning("Find Last String error");
            allOk = false;
        }

        this->log("First of 'a', 's', ' ' : %d", str.findFirstOf("as "));
        if ( str.findFirstOf("as ") != 3 ) {
            this->logWarning("Find First Of error");
            allOk = false;
        }

        this->log("First of 'x', 'y' : %d", str.findFirstOf("xy"));
        if ( str.findFirstOf("xy") != String::INVALID_POS ) {
            this->logWarning("Find First Of error");
            allOk = false;
        }

        this->log("First not of 'T', 'h', 'i', 's' : %d", str.findFirstNotOf("This"));
        if ( str.findFirstNotOf("This") != 4 ) {
            this->logWarning("Find First not Of error");
            allOk = false;
        }

        this->log("Last of 'a', 's', ' ' : %d", str.findLastOf("as "));
        if ( str.findLastOf("as ") != 17 ) {
            this->logWarning("Find Last Of Error");
            allOk = false;
        }

        this->log("First of 'x', 'y' : %d", str.findLastOf("xy"));
        if ( str.findLastOf("xy") != String::INVALID_POS ) {
            this->logWarning("Find Last Of error");
            allOk = false;
        }

        this->log("Last not of 'i', 'n', 'g' : %d", str.findLastNotOf("ing"));
        if ( str.findLastNotOf("ing") != 19 ) {
            this->logWarning("Find Last Not Of error");
            allOk = false;
        }
    });

    this->executeSubtest("Substring Tests", [this, & allOk] {
        String original = "This is a sample string";

        this->log("Original String : '%s'", original.cStr());

        this->log("Second Word : '%s'", original.substr(5, 7).cStr());
        if ( original.substr(5, 7) != "is" ) {
            this->logWarning("Substr error");
            allOk = false;
        }

        this->log("String until first word : '%s'", original.substr(0, 4).cStr());
        if ( original.substr(0, 4) != "This" ) {
            this->logWarning("Substr error");
            allOk = false;
        }

        this->log("String after second word : '%s'", original.substr(8).cStr());
        if ( original.substr(8) != "a sample string" ) {
            this->logWarning("Substr error");
            allOk = false;
        }

        this->log("String until first word, invalid start index (<0) : '%s'", original.substr(-200, 4).cStr());
        if ( original.substr(-200, 4) != "This" ) {
            this->logWarning("Substr error");
            allOk = false;
        }

        this->log("String after second word, invalid end index (>len) : '%s'", original.substr(8, 2000).cStr());
        if ( original.substr(8, 2000) != "a sample string" ) {
            this->logWarning("Substr error");
            allOk = false;
        }

        this->log("String with indices start > end : '%s'", original.substr(4, 2).cStr());
        if ( !original.substr(4, 2).empty() ) {
            this->logWarning("Substr error");
            allOk = false;
        }

        this->log("String with indices < 0 : '%s'", original.substr(-7, -3).cStr());
        if ( !original.substr(-7, -3).empty() ) {
            this->logWarning("Substr error");
            allOk = false;
        }

        this->log("String with indices > length : '%s'", original.substr(100, 200).cStr());
        if( ! original.substr(100, 200).empty() ){
            this->logWarning("Substr error");
            allOk = false;
        }
    });

    this->executeSubtest("Comparison Tests", [this, &allOk]{
        this->log("String(Test String) == String(Test String) : %s", String("Test String") == String("Test String") ? "true" : "false");
        if ( String("Test String") != String("Test String") ) {
            this->logWarning("String == String error");
            allOk = false;
        }

        this->log("String(Test String) == String(Not Test String) : %s", String("Test String") == String("Not Test String") ? "true" : "false");
        if ( String("Test String") == String("Not Test String") ) {
            this->logWarning("String == String error");
            allOk = false;
        }

        this->log("String(a) == 'a' (char) : %s", String("a") == 'a' ? "true" : "false");
        if ( String("a") != 'a' ) {
            this->logWarning("String == char error");
            allOk = false;
        }

        this->log("String(a) == 'b' (char) : %s", String("a") == 'b' ? "true" : "false");
        if ( String("a") == 'b' ) {
            this->logWarning("String == char error");
            allOk = false;
        }

        constexpr uint8 comparableCount = 8;

        const char * leftComparable [comparableCount] = { "abcd", "ABCD", "abc", "123", "1234", "12", "12ab", "ab12" };
        const char * rightComparable [comparableCount] = { "abce", "ABC", "abce", "124", "1224", "13", "13ac", "ab11" };

        for ( auto i : Range(comparableCount) ) {
#define COMP_TEST(_operand, _left, _right) \
            this->log(                      \
                    "String (%s) " #_operand " String (%s) : %s", \
                    String(_left).cStr(),   \
                    String(_right).cStr(),  \
                    String(_left) _operand String(_right) ? "true" : "false"\
            );                             \
                                           \
            if ( String(_left) _operand String(_right) != std::strcmp(_left, _right) _operand 0 ) { \
                this->logWarning("String " #_operand " compare error");                             \
                allOk = false;\
            }                              \
                                           \
            this->log(                     \
                    "String (%s) " #_operand " StringLiteral (%s) : %s",                            \
                    String(_left).cStr(),  \
                    _right,                \
                    String(_left) _operand _right ? "true" : "false"\
            );                             \
                                           \
            if ( String(_left) _operand _right != std::strcmp(_left, _right) _operand 0) {          \
                this->logWarning("String " #_operand " StringLiteral compare error");               \
                allOk = false;\
            }                              \
                                           \
            this->log(                     \
                    "String (%s) " #_operand " std::string (%s) : %s",                            \
                    String(_left).cStr(),  \
                    std::string(_right).c_str() ,                \
                    String(_left) _operand std::string(_right) ? "true" : "false"\
            );                             \
                                           \
            if ( String(_left) _operand std::string(_right) != std::strcmp(_left, _right) _operand 0) {          \
                this->logWarning("String " #_operand " std::string compare error");               \
                allOk = false;\
            }\

            COMP_TEST(>, leftComparable[i], rightComparable[i])
            COMP_TEST(<, leftComparable[i], rightComparable[i])
            COMP_TEST(>=, leftComparable[i], rightComparable[i])
            COMP_TEST(<=, leftComparable[i], rightComparable[i])

#undef COMP_TEST
        }
    });

    this->executeSubtest("Utility Functions, String Formatting", [this, & allOk] {
        this->log("String * int ( string multiplication ) : %s * %d = %s", String("abc...").cStr(), 5,
                  (String("abc...") * 5).cStr());
        if (String("abc...") * 5 != "abc...abc...abc...abc...abc...") {
            this->logWarning("String Multiplication Warning");
            allOk = false;
        }

        this->log("Left Trim of String Whitespace : '%s', trimmed : '%s'",
                  String("   \t  \n Whitespace String  \t  ").cStr(),
                  String("   \t  \n Whitespace String  \t  ").ltrim(" \t\n").cStr());
        this->log("Right Trim of String Whitespace : '%s', trimmed : '%s'",
                  String("   \t  \n Whitespace String  \t  ").cStr(),
                  String("   \t  \n Whitespace String  \t  ").rtrim(" \t\n").cStr());
        this->log("Trim of String Whitespace : '%s', trimmed : '%s'",
                  String("   \t  \n Whitespace String  \t  ").cStr(),
                  String("   \t  \n Whitespace String  \t  ").trim(" \t\n").cStr());

        if (String("   \t  \n Whitespace String  \t  ").ltrim(" \t\n") != "Whitespace String  \t  ") {
            this->logWarning("Ltrim Error");
            allOk = false;
        }

        if (String("   \t  \n Whitespace String  \t  ").rtrim(" \t\n") != "   \t  \n Whitespace String") {
            this->logWarning("Rtrim Error");
            allOk = false;
        }

        if (String("   \t  \n Whitespace String  \t  ").trim(" \t\n") != "Whitespace String") {
            this->logWarning("Trim Error");
            allOk = false;
        }

        this->log("'Sample String' left justified by %d : '%s'", 10, String("Sample String").ljust(10).cStr());
        this->log("'Sample String' left justified by %d : '%s'", 15, String("Sample String").ljust(15).cStr());
        this->log("'Sample String' left justified by %d : '%s'", 30, String("Sample String").ljust(30).cStr());

        this->log("'Sample String' right justified by %d : '%s'", 10, String("Sample String").rjust(10).cStr());
        this->log("'Sample String' right justified by %d : '%s'", 15, String("Sample String").rjust(15).cStr());
        this->log("'Sample String' right justified by %d : '%s'", 30, String("Sample String").rjust(30).cStr());

        if (String("Sample String").ljust(10).length() != std::max(String("Sample String").length(), 10llu)) {
            this->logWarning("Left Justify Error");
            allOk = false;
        }
        if (String("Sample String").ljust(15).length() != std::max(String("Sample String").length(), 15llu)) {
            this->logWarning("Left Justify Error");
            allOk = false;
        }
        if (String("Sample String").ljust(30).length() != std::max(String("Sample String").length(), 30llu)) {
            this->logWarning("Left Justify Error");
            allOk = false;
        }

        if (String("Sample String").rjust(10).length() != std::max(String("Sample String").length(), 10llu)) {
            this->logWarning("Right Justify Error");
            allOk = false;
        }
        if (String("Sample String").rjust(15).length() != std::max(String("Sample String").length(), 15llu)) {
            this->logWarning("Right Justify Error");
            allOk = false;
        }
        if (String("Sample String").rjust(30).length() != std::max(String("Sample String").length(), 30llu)) {
            this->logWarning("Right Justify Error");
            allOk = false;
        }

        this->log("'%s' lowercase : '%s'", "Sample String", String("Sample String").lower().cStr());
        this->log("'%s' uppercase : '%s'", "Sample String", String("Sample String").upper().cStr());

        if (String("Sample String").lower() != "sample string") {
            this->logWarning("Lower Error");
            allOk = false;
        }
        if (String("Sample String").upper() != "SAMPLE STRING") {
            this->logWarning("Upper Error");
            allOk = false;
        }

        this->log("'%c' is uppercase : '%s'", 'A', String::isUpperChar('A') ? "true" : "false");
        this->log("'%c' is uppercase : '%s'", 'a', String::isUpperChar('a') ? "true" : "false");
        this->log("'%c' is uppercase : '%s'", '0', String::isUpperChar('0') ? "true" : "false");

        if (String::isUpperChar('A') != true) {
            this->logWarning("isUpperChar Error");
            allOk = false;
        }

        if (String::isUpperChar('a') != false) {
            this->logWarning("isUpperChar Error");
            allOk = false;
        }

        if (String::isUpperChar('0') != false) {
            this->logWarning("isUpperChar Error");
            allOk = false;
        }

        this->log("'%c' is lowercase : '%s'", 'A', String::isLowerChar('A') ? "true" : "false");
        this->log("'%c' is lowercase : '%s'", 'a', String::isLowerChar('a') ? "true" : "false");
        this->log("'%c' is lowercase : '%s'", '0', String::isLowerChar('0') ? "true" : "false");

        if (String::isLowerChar('A') != false) {
            this->logWarning("isLowerChar Error");
            allOk = false;
        }

        if (String::isLowerChar('a') != true) {
            this->logWarning("isLowerChar Error");
            allOk = false;
        }

        if (String::isLowerChar('0') != false) {
            this->logWarning("isLowerChar Error");
            allOk = false;
        }

        this->log("'%c' is digit : '%s'", 'A', String::isDigit('A') ? "true" : "false");
        this->log("'%c' is digit : '%s'", 'a', String::isDigit('a') ? "true" : "false");
        this->log("'%c' is digit : '%s'", '0', String::isDigit('0') ? "true" : "false");

        if (String::isDigit('A') != false) {
            this->logWarning("isDigit Error");
            allOk = false;
        }

        if (String::isDigit('a') != false) {
            this->logWarning("isDigit Error");
            allOk = false;
        }

        if (String::isDigit('0') != true) {
            this->logWarning("isDigit Error");
            allOk = false;
        }

        this->log("'%c' is letter : '%s'", 'A', String::isLetter('A') ? "true" : "false");
        this->log("'%c' is letter : '%s'", 'a', String::isLetter('a') ? "true" : "false");
        this->log("'%c' is letter : '%s'", '0', String::isLetter('0') ? "true" : "false");

        if (String::isLetter('A') != true) {
            this->logWarning("isLetter Error");
            allOk = false;
        }

        if (String::isLetter('a') != true) {
            this->logWarning("isLetter Error");
            allOk = false;
        }

        if (String::isLetter('0') != false) {
            this->logWarning("isLetter Error");
            allOk = false;
        }

        this->log("'%c' is alpha : '%s'", 'A', String::isAlpha('A') ? "true" : "false");
        this->log("'%c' is alpha : '%s'", 'a', String::isAlpha('a') ? "true" : "false");
        this->log("'%c' is alpha : '%s'", '0', String::isAlpha('0') ? "true" : "false");
        this->log("'%c' is alpha : '%s'", '-', String::isAlpha('-') ? "true" : "false");

        if (String::isAlpha('A') != true) {
            this->logWarning("isAlpha Error");
            allOk = false;
        }

        if (String::isAlpha('a') != true) {
            this->logWarning("isAlpha Error");
            allOk = false;
        }

        if (String::isAlpha('0') != true) {
            this->logWarning("isAlpha Error");
            allOk = false;
        }

        if (String::isAlpha('-') != false) {
            this->logWarning("isAlpha Error");
            allOk = false;
        }

        this->log("'%c' is vowel : '%s'", 'E', String::isVowel('E') ? "true" : "false");
        this->log("'%c' is vowel : '%s'", 'b', String::isVowel('b') ? "true" : "false");
        this->log("'%c' is vowel : '%s'", '0', String::isVowel('0') ? "true" : "false");
        this->log("'%c' is vowel : '%s'", '-', String::isVowel('-') ? "true" : "false");

        if (!String::isVowel('E')) {
            this->logWarning("isVowel Error");
            allOk = false;
        }

        if (String::isVowel('b')) {
            this->logWarning("isVowel Error");
            allOk = false;
        }

        if (String::isVowel('0')) {
            this->logWarning("isVowel Error");
            allOk = false;
        }

        if (String::isVowel('-')) {
            this->logWarning("isVowel Error");
            allOk = false;
        }
        this->log("'%c' is consonant : '%s'", 'E', String::isConsonant('E') ? "true" : "false");
        this->log("'%c' is consonant : '%s'", 'b', String::isConsonant('b') ? "true" : "false");
        this->log("'%c' is consonant : '%s'", '0', String::isConsonant('0') ? "true" : "false");
        this->log("'%c' is consonant : '%s'", '-', String::isConsonant('-') ? "true" : "false");

        if (String::isConsonant('E')) {
            this->logWarning("isConsonant Error");
            allOk = false;
        }

        if (!String::isConsonant('b')) {
            this->logWarning("isConsonant Error");
            allOk = false;
        }

        if (String::isConsonant('0')) {
            this->logWarning("isConsonant Error");
            allOk = false;
        }

        if (String::isConsonant('-')) {
            this->logWarning("isConsonant Error");
            allOk = false;
        }

        this->log("Lower of '%c' : '%c'", 'a', String::lowerChar('a'));
        this->log("Lower of '%c' : '%c'", 'A', String::lowerChar('A'));
        this->log("Lower of '%c' : '%c'", '0', String::lowerChar('0'));
        this->log("Lower of '%c' : '%c'", '-', String::lowerChar('-'));

        if (String::lowerChar('a') != 'a') {
            this->logWarning("lowerchar error");
            allOk = false;
        }

        if (String::lowerChar('A') != 'a') {
            this->logWarning("lowerchar error");
            allOk = false;
        }

        if (String::lowerChar('0') != '0') {
            this->logWarning("lowerchar error");
            allOk = false;
        }

        if (String::lowerChar('-') != '-') {
            this->logWarning("lowerchar error");
            allOk = false;
        }

        this->log("Upper of '%c' : '%c'", 'a', String::upperChar('a'));
        this->log("Upper of '%c' : '%c'", 'A', String::upperChar('A'));
        this->log("Upper of '%c' : '%c'", '0', String::upperChar('0'));
        this->log("Upper of '%c' : '%c'", '-', String::upperChar('-'));

        if (String::upperChar('a') != 'A') {
            this->logWarning("upperchar error");
            allOk = false;
        }

        if (String::upperChar('A') != 'A') {
            this->logWarning("upperchar error");
            allOk = false;
        }

        if (String::upperChar('0') != '0') {
            this->logWarning("upperchar error");
            allOk = false;
        }

        if (String::upperChar('-') != '-') {
            this->logWarning("upperchar error");
            allOk = false;
        }

        char c;

        c = 'a';
        this->log("Lower of '%c' : '%c'", c, String::toLowerChar(c));
        c = 'A';
        this->log("Lower of '%c' : '%c'", c, String::toLowerChar(c));
        c = '0';
        this->log("Lower of '%c' : '%c'", c, String::toLowerChar(c));
        c = '-';
        this->log("Lower of '%c' : '%c'", c, String::toLowerChar(c));

        c = 'a';
        if (String::toLowerChar(c) != 'a') {
            this->logWarning("toLowerChar error");
            allOk = false;
        }

        c = 'A';
        if (String::toLowerChar(c) != 'a') {
            this->logWarning("toLowerChar error");
            allOk = false;
        }

        c = '0';
        if (String::toLowerChar(c) != '0') {
            this->logWarning("toLowerChar error");
            allOk = false;
        }

        c = '-';
        if (String::toLowerChar(c) != '-') {
            this->logWarning("toLowerChar error");
            allOk = false;
        }

        c = 'a';
        this->log("Upper of '%c' : '%c'", c, String::toUpperChar(c));
        c = 'A';
        this->log("Upper of '%c' : '%c'", c, String::toUpperChar(c));
        c = '0';
        this->log("Upper of '%c' : '%c'", c, String::toUpperChar(c));
        c = '-';
        this->log("Upper of '%c' : '%c'", c, String::toUpperChar(c));

        c = 'a';
        if (String::toUpperChar(c) != 'A') {
            this->logWarning("toUpperChar error");
            allOk = false;
        }

        c = 'A';
        if (String::toUpperChar(c) != 'A') {
            this->logWarning("toUpperChar error");
            allOk = false;
        }

        c = '0';
        if (String::toUpperChar(c) != '0') {
            this->logWarning("toUpperChar error");
            allOk = false;
        }

        c = '-';
        if (String::toUpperChar(c) != '-') {
            this->logWarning("toUpperChar error");
            allOk = false;
        }
    });

    this->executeSubtest("Assignment Tests", [this, & allOk] {
        String a = "Test String";
        std::string b = "Test std::string";
        StringLiteral c = "Test StringLiteral";
        char d = 'c';

        String o;

        o = a;

        if ( std::strcmp ( o.cStr(), "Test String" ) != 0 ) {
            this->logWarning("Assign Error");
            allOk = false;
        }

        o = b;

        if ( std::strcmp ( o.cStr(), "Test std::string" ) != 0 ) {
            this->logWarning("Assign Error");
            allOk = false;
        }

        o = c;

        if ( std::strcmp ( o.cStr(), "Test StringLiteral" ) != 0 ) {
            this->logWarning("Assign Error");
            allOk = false;
        }

        o = d;

        if ( std::strcmp ( o.cStr(), "c" ) != 0 ) {
            this->logWarning("Assign Error");
            allOk = false;
        }
    });

    this->executeSubtest("Split Tests", [this, &allOk] {
        String toSplit("This is a sample string, using several separators. Will it be okay? I hope so! Time to split");

        this->log("String : '%s'. Tokens after splitting by ' ,.!?' : %s. Number of tokens : %d", toSplit.cStr(), toSplit.split(" ,.!?").toString().cStr(), toSplit.split(" ,.!?").size());

        if ( toSplit.split(" ,.!?").size() != 18 ) {
            this->logWarning("Split Error");
            allOk = false;
        }

        if ( toSplit.split(" ,.!?")[2] != "a" ) {
            this->logWarning("Split Error");
            allOk = false;
        }

        if ( toSplit.split(" ,.!?")[6] != "several" ) {
            this->logWarning("Split Error");
            allOk = false;
        }

        if ( toSplit.split(" ,.!?")[8] != "Will" ) {
            this->logWarning("Split Error");
            allOk = false;
        }
    });

    this->executeSubtest("Replace Tests", [this, &allOk] {
        String original = "Test String";

        String m = original;
        this->log("Replaced in '%s' from 2 to 5 with 'inserted value' : '%s'", original.cStr(), m.replace(2, 3, "inserted value").cStr());
    });

    this->executeSubtest("Iterable Lambda Utilities Tests", [this, &allOk] {
        String original = "This is a sample string";

        this->log("Original String : '%s'", original.cStr());
        this->log("Vowel Count, using count : %d", original.count(String::isVowel));
        this->log("Consonant Count, using count : %d", original.count(String::isConsonant));
        this->log("Letter Count, using count : %d", original.count(String::isLetter));

        if ( original.count(String::isVowel) != 6 ) {
            this->logWarning("Lambda Count error");
            allOk = false;
        }

        if ( original.count(String::isConsonant) != 13 ) {
            this->logWarning("Lambda Count error");
            allOk = false;
        }

        if ( original.count(String::isLetter) != 19 ) {
            this->logWarning("Lambda Count error");
            allOk = false;
        }
    });

    allOk ? this->logOK("String test OK") : this->logError("String test Not OK");
    return allOk;
}

#if !defined(_MSC_VER)
#pragma clang diagnostic pop
#endif