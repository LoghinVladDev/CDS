//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_PRIMITIVEGENERATOR_HPP
#define CDS_PRIMITIVEGENERATOR_HPP

#define _G_OP_OBJ_CONST(_dType, _opVal, _rDatType, _dTypeVal, _dInternalType) \
    constexpr auto operator _opVal ( _dType const & o ) const noexcept -> _rDatType { return this->_dTypeVal _opVal o._dTypeVal; } \
    constexpr auto operator _opVal ( _dInternalType value ) const noexcept -> _rDatType { return this->_dTypeVal _opVal value; }

#define _G_OP_OBJ(_dType, _opVal, _dTypeVal, _dInternalType) \
    constexpr auto operator _opVal ( _dType const & o ) noexcept -> _dType & { this->_dTypeVal _opVal o._dTypeVal; return * this; } \
    constexpr auto operator _opVal ( _dInternalType value ) noexcept -> _dType & { this->_dTypeVal _opVal value; return * this; }

#define _G_OBJ_CONSTEXPR(_dType, _dInternalType, _dInternalName, _dInternalInitValue) \
    private:                                                                \
        _dInternalType _dInternalName { _dInternalInitValue };              \
    public:                                                                 \
        constexpr _dType () noexcept = default;                             \
        constexpr _dType ( _dType const & ) noexcept = default;             \
        constexpr _dType ( _dType && ) noexcept = default;                  \
        constexpr ~_dType () noexcept = default;                             \
                                                                            \
        constexpr _dType ( _dInternalType value ) noexcept : _dInternalName(value) {} \
                                                                            \
        constexpr _dType & operator = ( _dType const & o ) noexcept {       \
            if ( this == & o ) return * this;                               \
            this->v = o.v;                                                  \
            return * this;                                                  \
        }                                                                   \
                                                                            \
        constexpr _dType & operator = ( _dInternalType value ) noexcept {   \
            this->_dInternalName = value;                                   \
            return * this;                                                  \
        }                                                                   \
                                                                            \
        _G_OP_OBJ_CONST(_dType, +, _dType, _dInternalName, _dInternalType)  \
        _G_OP_OBJ_CONST(_dType, -, _dType, _dInternalName, _dInternalType)  \
        _G_OP_OBJ_CONST(_dType, *, _dType, _dInternalName, _dInternalType)  \
        _G_OP_OBJ_CONST(_dType, /, _dType, _dInternalName, _dInternalType)  \
        _G_OP_OBJ_CONST(_dType, %, _dType, _dInternalName, _dInternalType)  \
                                                                            \
        _G_OP_OBJ(_dType, +=, _dInternalName, _dInternalType)               \
        _G_OP_OBJ(_dType, -=, _dInternalName, _dInternalType)               \
        _G_OP_OBJ(_dType, *=, _dInternalName, _dInternalType)               \
        _G_OP_OBJ(_dType, /=, _dInternalName, _dInternalType)               \
        _G_OP_OBJ(_dType, %=, _dInternalName, _dInternalType)               \
                                                                            \
        _G_OP_OBJ_CONST(_dType, ==, bool, _dInternalName, _dInternalType)   \
        _G_OP_OBJ_CONST(_dType, !=, bool, _dInternalName, _dInternalType)   \
        _G_OP_OBJ_CONST(_dType, >, bool, _dInternalName, _dInternalType)    \
        _G_OP_OBJ_CONST(_dType, <, bool, _dInternalName, _dInternalType)    \
        _G_OP_OBJ_CONST(_dType, >=, bool, _dInternalName, _dInternalType)   \
        _G_OP_OBJ_CONST(_dType, <=, bool, _dInternalName, _dInternalType)   \
                                                                            \
        _G_OP_OBJ_CONST(_dType, &, _dType, _dInternalName, _dInternalType)  \
        _G_OP_OBJ_CONST(_dType, |, _dType, _dInternalName, _dInternalType)  \
        _G_OP_OBJ_CONST(_dType, ^, _dType, _dInternalName, _dInternalType)  \
                                                                            \
        _G_OP_OBJ(_dType, &, _dInternalName, _dInternalType)                \
        _G_OP_OBJ(_dType, |, _dInternalName, _dInternalType)                \
        _G_OP_OBJ(_dType, ^, _dInternalName, _dInternalType)                \
                                                                            \
        constexpr operator _dInternalType () const noexcept {           \
            return this->v;                                                 \
        }                                                                   \
                                                                            \
        [[nodiscard]] constexpr inline auto get () const noexcept -> _dInternalType { \
            return this->v;                                                 \
        }


#endif //CDS_PRIMITIVEGENERATOR_HPP
