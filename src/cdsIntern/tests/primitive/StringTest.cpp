//
// Created by loghin on 05.04.2021.
//

#include "StringTest.h"

#include <CDS/String>

auto StringTest::execute() noexcept -> bool {
    bool allOk = true;
    this->logBold("Start of test String....");

    this->logBold("\tCtor Tests");
    String empty;
    this->log("\t\tEmpty String Constructed : %s, %s", empty.cStr(), empty.diag().cStr());
    if ( !empty.empty() ) {
        this->logWarning("Empty String Unexpected Error");
        allOk = false;
    }

    String b = "Test String to be copied";
    String copy(b);
    this->log("\t\tString Constructed with Copy Constructor : Original : '%s', Copy : '%s'. Copy Diag : %s", b.cStr(), copy.cStr(), copy.diag().cStr());
    if ( b != copy ) {
        this->logWarning("Copy String Unexpected Error");
        allOk = false;
    }

    const char * literal = "Test StringLiteral to be copied";
    String literalCopy(literal);
    this->log("\t\tString Constructed with StringLiteral : Original : '%s', String : '%s'. Diag : '%s'",
              literal,
              literalCopy.cStr(),
              literalCopy.diag().cStr()
    );

    if ( literalCopy != literal ) {
        this->logWarning("StringLiteral Constructor Error");
        allOk = false;
    }

    std::string stdString = "std::string to be copied";
    String stdCopy (stdString);
    this->log("\t\tString Constructed with std::string : Original : '%s', String : '%s'. Diag : %s",
        stdString.c_str(),
        stdCopy.cStr(),
        stdCopy.diag().cStr()
    );

    if ( stdCopy != stdString ) {
        this->logWarning("std::string construction Error");
        allOk = false;
    }

    String defaultedString(10, 'a');
    this->log("\t\tString Constructed with default values : '%s'. Diag : %s", defaultedString.cStr(), defaultedString.diag().cStr());

    if ( defaultedString != "aaaaaaaaaa" ) {
        this->logWarning("String with default values construction Error");
        allOk = false;
    }

    std::string stdStringIt = "String that will be iterated. Should not appear";
    String iteratedStd ( stdStringIt.begin(), stdStringIt.end().operator-=(strlen(" Should not appear")) );
    this->log("\t\tString Constructed with std::string iterators : Intended : '%s'. Result : '%s'. Diag : %s",
        std::string(stdStringIt.begin(), stdStringIt.end().operator-= (strlen(" Should not appear"))).c_str(),
        iteratedStd.cStr(),
        iteratedStd.diag().cStr()
    );

    if ( iteratedStd != std::string(stdStringIt.begin(), stdStringIt.end().operator-= (strlen(" Should not appear"))) ) {
        this->logWarning("String from std::string iterators construction Error");
        allOk = false;
    }

    String stringIt = "String that will be iterated";
    String iterated (stringIt.begin(), stringIt.end());
    this->log("\t\tString Constructed with String iterators : Intended : '%s', Result : '%s'. Diag : %s",
          stringIt.cStr(),
          iterated.cStr(),
          iterated.diag().cStr()
    );

    if ( iterated != stringIt ) {
        this->logWarning("String from String iterators construction Error");
        allOk = false;
    }

    iterated = String (stringIt.cbegin(), stringIt.cend());
    this->log("\t\tString Constructed with String const iterators : Intended : '%s', Result : '%s'. Diag : %s",
          stringIt.cStr(),
          iterated.cStr(),
          iterated.diag().cStr()
    );

    if ( iterated != stringIt ) {
        this->logWarning("String from String const iterators construction Error");
        allOk = false;
    }

    iterated = String (stringIt.rbegin(), stringIt.rend());
    this->log("\t\tString Constructed with String reverse iterators : Intended : '%s', Result : '%s'. Diag : %s",
          stringIt.reversed().cStr(),
          iterated.cStr(),
          iterated.diag().cStr()
    );

    if ( iterated != stringIt.reversed() ) {
        this->logWarning("String from String reverse iterators construction Error");
        allOk = false;
    }

    iterated = String (stringIt.crbegin(), stringIt.crend());
    this->log("\t\tString Constructed with String const reverse iterators : Intended : '%s', Result : '%s'. Diag : %s",
          stringIt.reversed().cStr(),
          iterated.cStr(),
          iterated.diag().cStr()
    );

    if ( iterated != stringIt.reversed() ) {
        this->logWarning("String from String const reverse iterators construction Error");
        allOk = false;
    }

    String initialized = {'S', 'a', 'm', 'p', 'l', 'e', ' ', 'S', 't', 'r', 'i', 'n', 'g'};
    this->log("\t\tString Constructed from std::initializer list. Intended : '%s', Result : '%s'. Diag : %s",
        "Sample String",
        initialized.cStr(),
        initialized.diag().cStr()
    );

    if ( initialized != "Sample String" ) {
        this->logWarning("String from Initializer List construction Error");
        allOk = false;
    }

    this->logBold("\tIterator Tests");

    String toIterate = "2345678";

    this->log("\t\tIterating : %s", toIterate.cStr());
    std::cout << "\t\tRegular Iteration : ";
    for ( auto e : toIterate ) std::cout << e << ' ';
    std::cout << "\n";

    std::cout << "\t\tReverse Iteration : ";
    for ( auto e = toIterate.rbegin(); e != toIterate.rend(); e++ ) std::cout << e.value() << ' ';
    std::cout << '\n';

    std::cout << "\t\tRegular Const Iteration : ";
    for ( const auto e : toIterate ) std::cout << e << ' ';
    std::cout << "\n";

    std::cout << "\t\tReverse Const Iteration : ";
    for ( auto e = toIterate.crbegin(); e != toIterate.crend(); e++ ) std::cout << e.value() << ' ';
    std::cout << '\n';

    std::cout << "\t\tReference Iteration : ";
    for ( auto & e : toIterate ) std::cout << e << ' ';
    std::cout << "\n";

    std::cout << "\t\tConst Reference Iteration : ";
    for ( auto const & e : toIterate ) std::cout << e << ' ';
    std::cout << "\n";

    std::cout << "\t\tConst Reference Iteration with modification : ";
    for ( auto & e : toIterate ) std::cout << ++e << ' ';
    std::cout << "\n";

    this->log("\t\tNew String : %s", toIterate.cStr());

    std::cout << "\t\tReverse Iteration with modification : ";
    for ( auto e = toIterate.rbegin(); e != toIterate.rend(); e++ ) std::cout << --e.value() << ' ';
    std::cout << '\n';

    this->log("\t\tNew String : %s", toIterate.cStr());

    this->logBold("\tProperty Tests");

    Array < String > strings = {
            "Some", "strings", "to test the", "properties", "on"
    };

    for ( auto const & s : strings ) {
        this->log("\t\tString : '%s'. Properties : "
                  "\tlength/size : %u"
                  "\tcapacity/maxSize : %u", s.cStr(), s.size(), s.capacity());
    }

    this->logBold("\tMemory Tests");

    String memoryOperated = "This is a sample string";

    this->log("\t\tOriginal String : '%s'. Diag : %s", memoryOperated.cStr(), memoryOperated.diag().cStr());
    auto memOpCopy = memoryOperated;
    memOpCopy.resize(10);
    this->log("\t\tOriginal shrunk to 10 with resize : '%s'. Diag : %s", memOpCopy.cStr(), memOpCopy.diag().cStr());

    auto memOpCopy2 = memoryOperated;
    memOpCopy2.resize(100);
    this->log("\t\tOriginal enlarged to 100 with resize : '%s'. Diag : %s", memOpCopy2.cStr(), memOpCopy2.diag().cStr());


    auto memOpCopy3 = memoryOperated;
    memOpCopy3.reserve(10);
    this->log("\t\tOriginal attempt shrink to 10 with reserve : '%s'. Diag : %s", memOpCopy3.cStr(), memOpCopy3.diag().cStr());

    auto memOpCopy4 = memoryOperated;
    memOpCopy4.reserve(100);
    this->log("\t\tOriginal enlarged to 100 with reserve : '%s'. Diag : %s", memOpCopy4.cStr(), memOpCopy4.diag().cStr());


    auto memOpCopy5 = memoryOperated;
    memOpCopy5.shrink(10);
    this->log("\t\tOriginal shrunk to 10 with shrink : '%s'. Diag : %s", memOpCopy5.cStr(), memOpCopy5.diag().cStr());

    auto memOpCopy6 = memoryOperated;
    memOpCopy6.shrink(100);
    this->log("\t\tOriginal attepted to enlarge to 100 with shrink : '%s'. Diag : %s", memOpCopy6.cStr(), memOpCopy6.diag().cStr());

    allOk ? this->logOK("String test OK") : this->logError("String test Not OK");
    return allOk;
}
