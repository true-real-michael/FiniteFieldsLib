//
// Created by Mikhail Kiselyov on 24.02.2023.
//

#ifndef FINITEFIELDS_MAIN_PRIMEFIELD_H
#define FINITEFIELDS_MAIN_PRIMEFIELD_H

#include "PrimeFieldElement.hpp"

namespace FiniteFields {

    class PrimeField {
    public:
        size_t p;

        constexpr explicit PrimeField(size_t p) : p(p) {}
    };

}

#endif //FINITEFIELDS_MAIN_PRIMEFIELD_H
