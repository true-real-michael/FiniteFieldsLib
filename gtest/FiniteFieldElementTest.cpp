//
// Created by Mikhail Kiselyov on 24.02.2023.
//

#include "gtest/gtest.h"
#include "FiniteFieldElement.hpp"
//#include "FFE2.h"

using namespace FiniteFields;

TEST(FiniteFieldElementTestSuite, FFEConstruction) {
    constexpr PrimeField pf(3);
    const Polynomial<PrimeFieldElement<pf>> irreduciblePoly({1, 2, 3});
    FiniteFieldElement<pf> element1(irreduciblePoly, Polynomial<PrimeFieldElement<pf>>({2, 3, 4}));
    FiniteFieldElement<pf> element2(irreduciblePoly, Polynomial<PrimeFieldElement<pf>>({2, 3, 4}));
    ASSERT_EQ(element1, element2);
}
