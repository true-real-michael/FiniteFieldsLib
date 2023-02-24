//
// Created by Mikhail Kiselyov on 24.02.2023.
//

#ifndef FINITEFIELDS_MAIN_FINITEFIELD_HPP
#define FINITEFIELDS_MAIN_FINITEFIELD_HPP

#include "Polynomial.hpp"
#include "PrimeFieldElement.hpp"
#include "FiniteFieldElement.hpp"

namespace FiniteFields {

    template<PrimeField pf>
    class FiniteField {
        Polynomial<PrimeFieldElement<pf>> _modulus;
        size_t n;
    public:
        constexpr FiniteField(size_t n, const Polynomial<PrimeFieldElement<pf>> &modulus) :
                _modulus(modulus) {}

//        FiniteFieldElement<> ElementFromPolynomial(const Polynomial<PrimeFieldElement<p>> &value);
//        FiniteFieldElement<pf> Zero();
//        FiniteFieldElement<pf> One();
    };

//    template<size_t p, size_t n>
//    FiniteFieldElement<p, n> FiniteField<p, n>::ElementFromPolynomial(const Polynomial<PrimeFieldElement<p>> &value) {
//        return FiniteFieldElement<p, n>(Polynomial(value), Polynomial(_modulus));
//    }

} // FiniteFields

#endif //FINITEFIELDS_MAIN_FINITEFIELD_HPP
