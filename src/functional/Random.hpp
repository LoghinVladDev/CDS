//
// Created by loghin on 21.03.2021.
//

#ifndef CDS_RANDOM_HPP
#define CDS_RANDOM_HPP

#include <random>
#include <CDS/Object>
#include <type_traits>
#include <limits>

class Random : public Object {
private:
    template <typename T, typename D, typename TE, typename RD>
    class BaseRandom : public Object {
    public:
        using ValueType     = T;
        using Distribution  = D;
        using RandomDevice  = RD;
        using TwisterEngine = TE;

    private:
        RandomDevice    randomDevice;
        TwisterEngine   twisterEngine;
        Distribution    distribution;

        ValueType       _lowerBound;
        ValueType       _higherBound;

        __CDS_cpplang_ConstexprConditioned static auto typeName () noexcept -> StringLiteral {
            if ( std::is_same<uint8, ValueType>::value ) return "uint8";
            if ( std::is_same<uint16, ValueType>::value ) return "uint16";
            if ( std::is_same<uint32, ValueType>::value ) return "uint32";
            if ( std::is_same<uint64, ValueType>::value ) return "uint64";

            if ( std::is_same<sint8, ValueType>::value ) return "int8";
            if ( std::is_same<sint16, ValueType>::value ) return "int16";
            if ( std::is_same<sint32, ValueType>::value ) return "int32";
            if ( std::is_same<sint64, ValueType>::value ) return "int64";

            if ( std::is_same<int, ValueType>::value ) return "int";
            if ( std::is_same<long long, ValueType>::value ) return "long";
            if ( std::is_same<float, ValueType>::value ) return "float";
            if ( std::is_same<double, ValueType>::value ) return "double";

            return "unknown";
        };

    public:
#if defined(_MSC_VER)
#pragma push_macro("max")
#pragma push_macro("min")
#undef max
#undef min
#endif
        explicit BaseRandom(ValueType lower = std::numeric_limits<T>::min(), ValueType upper = std::numeric_limits<T>::max()) noexcept :
            twisterEngine(randomDevice()),
            distribution(lower, upper),
            _lowerBound(lower),
            _higherBound(upper) { }

#if defined(_MSC_VER)
#pragma pop_macro("min")
#pragma pop_macro("max")
#endif

        auto get () noexcept -> ValueType { return this->distribution(this->twisterEngine); }
        inline auto operator () () noexcept -> ValueType { return this->get(); }
        constexpr auto low () const noexcept -> ValueType { return this->_lowerBound; }
        constexpr auto high () const noexcept -> ValueType { return this->_higherBound; }

        inline auto seed ( typename TwisterEngine::result_type seed ) noexcept -> void { this->twisterEngine.seed(seed); }

        __CDS_NoDiscard auto toString () const noexcept -> String override {
            return String()
                .append("RandomGenerator{")
                .append("type = ").append(typeName())
                .append("}");
        }
    };

public:

    template <typename T, typename D, typename TE = std::mt19937, typename RD = std::random_device>
    using Generator = BaseRandom<T, D, TE, RD>;

    using Int                               = Generator<sint32, std::uniform_int_distribution<sint32>>;
    using Long                              = Generator<sint64, std::uniform_int_distribution<sint64>, std::mt19937_64>;
    using Float                             = Generator<float, std::uniform_real_distribution<float>>;
    using Double                            = Generator<double, std::uniform_real_distribution<double>, std::mt19937_64>;

    using UnsignedInt     __CDS_MaybeUnused = Generator<uint32, std::uniform_int_distribution<uint32>>;
    using UnsignedLong    __CDS_MaybeUnused = Generator<uint64, std::uniform_int_distribution<uint64>>;
};

#endif //CDS_RANDOM_HPP
