//
// Created by loghin on 24/09/2021.
//

#ifndef CDS_CONVERSION_HPP
#define CDS_CONVERSION_HPP

namespace Conversion {

    /**
     * @brief Implementation 'borrowed' from gcc11 charconv.h to add constexpr functionality
     */
    template<typename Type>
    __CDS_cpplang_ConstexprConditioned static auto toCharBase10(char * buffer, uint32 length, Type value) noexcept -> void { // NOLINT(bugprone-reserved-identifier)
        static_assert(std::is_integral<Type>::value, "implementation bug");
        static_assert(std::is_unsigned<Type>::value, "implementation bug");

        constexpr char digits[201] =
                "0001020304050607080910111213141516171819"
                "2021222324252627282930313233343536373839"
                "4041424344454647484950515253545556575859"
                "6061626364656667686970717273747576777879"
                "8081828384858687888990919293949596979899";

        uint32 pos = length - 1;
        while (value >= 100) {
            auto const number = (value % 100) * 2;
            value /= 100;

            buffer[pos] = digits[number + 1];
            buffer[pos - 1] = digits[number];
            pos -= 2;
        }

        if (value >= 10) {
            auto const number = value * 2;
            buffer[1] = digits[number + 1];
            buffer[0] = digits[number];
        } else {
            buffer[0] = '0' + value;
        }
    }

    /**
     * @brief Implementation 'borrowed' from gcc11 charconv.h to add constexpr functionality
     */
    template < typename Type >
    __CDS_cpplang_ConstexprConditioned static auto toCharBase10Length (Type value, uint32 base = 10) noexcept -> uint32 {
        static_assert(std::is_integral < Type > :: value, "implementation bug");
        static_assert(std::is_unsigned < Type > :: value, "implementation bug");

        uint32 n = 1;
        uint32 const base2 = base * base;
        uint32 const base3 = base2 * base;
        uint32 const base4 = base3 * base;

        while(true) {
            if ( value < base ) return n;
            else if ( value < base2 ) return n + 1;
            else if ( value < base3 ) return n + 2;
            else if ( value < base4 ) return n + 3;
            value /= base4;
            n += 4;
        }
    }
}

#endif //CDS_CONVERSION_HPP
