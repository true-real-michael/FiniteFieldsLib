//
// Created by Mikhail Kiselyov on 24.02.2023.
//

#include "gtest/gtest.h"
#include "PrimeFieldElement.hpp"
#include "Polynomial.hpp"

using namespace FiniteFields;

TEST(PolynomialOverPrimeFieldSuite, SimpleArithmetic1) {
    constexpr PrimeField pf(3);
    Polynomial<PrimeFieldElement<pf>> a({1, 2, 3, 4, 5});
    Polynomial<PrimeFieldElement<pf>> b({1, 3, 5});
    Polynomial<PrimeFieldElement<pf>> c({1, 2, 2, -1, 5, 2, 1});
    ASSERT_EQ(a * b, c);
}
