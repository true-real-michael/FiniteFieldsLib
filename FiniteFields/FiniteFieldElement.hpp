//
// Created by Mikhail Kiselyov on 22.02.2023.
//

#ifndef FINITEFIELDS_FINITEFIELDELEMENT_HPP
#define FINITEFIELDS_FINITEFIELDELEMENT_HPP

#include "Polynomial.hpp"
#include "PrimeFieldElement.hpp"
#include "InvalidFieldException.h"

namespace FiniteFields {

    template<const PrimeField primeField>
    class FiniteFieldElement {
        Polynomial<PrimeFieldElement<primeField>> _irreduciblePolynomial;
        Polynomial<PrimeFieldElement<primeField>> _value;

        void validateOtherElement(const FiniteFieldElement &other) const {
            if (_irreduciblePolynomial != other.GetIrreduciblePolynomial())
                throw InvalidFieldException();
        }

    public:

        explicit FiniteFieldElement(
                const Polynomial<PrimeFieldElement<primeField>> &irreduciblePolynomial,
                const Polynomial<PrimeFieldElement<primeField>> &value);

        FiniteFieldElement(const FiniteFieldElement<primeField> &other);

        void SetValue(const Polynomial<PrimeFieldElement<primeField>> &value);
        Polynomial<PrimeFieldElement<primeField>> GetValue() const;
        Polynomial<PrimeFieldElement<primeField>> GetIrreduciblePolynomial() const;

        size_t degree();
        FiniteFieldElement operator*(const FiniteFieldElement &other) const;
        FiniteFieldElement operator+(const FiniteFieldElement &other) const;
        FiniteFieldElement operator/(const FiniteFieldElement &other) const;
        FiniteFieldElement operator-(const FiniteFieldElement &other) const;
        FiniteFieldElement operator%(const FiniteFieldElement &other) const;
        bool operator==(const FiniteFieldElement &other) const;

    };

    template<const PrimeField primeField>
    Polynomial<PrimeFieldElement<primeField>> FiniteFieldElement<primeField>::GetIrreduciblePolynomial() const {
        return _irreduciblePolynomial;
    }

    template<const PrimeField primeField>
    FiniteFieldElement<primeField>::FiniteFieldElement(const FiniteFieldElement<primeField> &other) :
        _irreduciblePolynomial(other.GetIrreduciblePoly()),
        _value(other.GetValue()) {}

    template<const PrimeField primeField>
    bool FiniteFieldElement<primeField>::operator==(const FiniteFieldElement &other) const {
        validateOtherElement(other);
        return _value == other.GetValue();
    }

    template<const PrimeField primeField>
    FiniteFieldElement<primeField>
    FiniteFieldElement<primeField>::operator-(const FiniteFieldElement &other) const {
        validateOtherElement(other);
        return {_value - other.GetValue()};
    }

    template<const PrimeField primeField>
    FiniteFieldElement<primeField>
    FiniteFieldElement<primeField>::operator%(const FiniteFieldElement &other) const {
        validateOtherElement(other);
        return {_value % other.GetValue()};
    }

    template<const PrimeField primeField>
    FiniteFieldElement<primeField>
    FiniteFieldElement<primeField>::operator/(const FiniteFieldElement &other) const {
        validateOtherElement(other);
        return {_value / other.GetValue()};
    }

    template<const PrimeField primeField>
    FiniteFieldElement<primeField>
    FiniteFieldElement<primeField>::operator*(const FiniteFieldElement &other) const {
        validateOtherElement(other);
        return {_value * other.GetValue()};
    }

    template<const PrimeField primeField>
    FiniteFieldElement<primeField>
    FiniteFieldElement<primeField>::operator+(const FiniteFieldElement &other) const {
        validateOtherElement(other);
        return {_value + other.GetValue()};
    }

    template<const PrimeField primeField>
    size_t FiniteFieldElement<primeField>::degree() {
        return _value.degree();
    }

    template<const PrimeField primeField>
    Polynomial<PrimeFieldElement<primeField>> FiniteFieldElement<primeField>::GetValue() const {
        return _value;
    }

    template<const PrimeField primeField>
    void FiniteFieldElement<primeField>::SetValue(
            const Polynomial<PrimeFieldElement<primeField>> &value) {
        _value = value % _irreduciblePolynomial;
    }

    template<const PrimeField primeField>
    FiniteFieldElement<primeField>::FiniteFieldElement(
            const Polynomial<PrimeFieldElement<primeField>> &irreduciblePolynomial,
            const Polynomial<PrimeFieldElement<primeField>> &value) :
            _irreduciblePolynomial(irreduciblePolynomial),
            _value(value % _irreduciblePolynomial) {}


} // FiniteFields

#endif //FINITEFIELDS_FINITEFIELDELEMENT_HPP
