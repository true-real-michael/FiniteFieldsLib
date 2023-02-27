//
// Created by Mikhail Kiselyov on 24.02.2023.
//

#include "gtest/gtest.h"
#include "PrimeFieldElement.hpp"

using namespace FiniteFields;

TEST(PrimeFieldElementSuite, PrimeBase) {
    EXPECT_NO_THROW({ PrimeFieldElement<PrimeField(5)> a(0); });
    EXPECT_NO_THROW({ PrimeFieldElement<PrimeField(3)> b(1); });
    EXPECT_NO_THROW({ PrimeFieldElement<PrimeField(5)> c(2); });
    EXPECT_NO_THROW({ PrimeFieldElement<PrimeField(7)> d(-1); });
    EXPECT_NO_THROW({ PrimeFieldElement<PrimeField(11)> e(4); });
    EXPECT_NO_THROW({ PrimeFieldElement<PrimeField(13)> f(4); });
}

TEST(PrimeFieldElementSuite, NonPrimeBase) {
    EXPECT_ANY_THROW({ PrimeFieldElement<PrimeField(4)> a(0); });
    EXPECT_ANY_THROW({ PrimeFieldElement<PrimeField(6)> b(1); });
    EXPECT_ANY_THROW({ PrimeFieldElement<PrimeField(9)> c(2); });
    EXPECT_ANY_THROW({ PrimeFieldElement<PrimeField(10)> d(-1); });
    EXPECT_ANY_THROW({ PrimeFieldElement<PrimeField(12)> e(4); });
    EXPECT_ANY_THROW({ PrimeFieldElement<PrimeField(15)> f(4); });
}

TEST(PrimeFieldElementSuite, SimpleArithmetic1) {
    constexpr PrimeField pf(5);

    PrimeFieldElement<pf> a(0);
    PrimeFieldElement<pf> b(1);
    PrimeFieldElement<pf> c(2);
    PrimeFieldElement<pf> d(-1);
    PrimeFieldElement<pf> e(4);

    ASSERT_EQ(b - b, a);
    ASSERT_EQ(b + b, c);
    ASSERT_EQ(d, e);
}

TEST(PrimeFieldElementSuite, SimpleArithmetic2) {
    constexpr PrimeField pf(5);

    ASSERT_EQ(PrimeFieldElement<pf>(2) * PrimeFieldElement<pf>(4), PrimeFieldElement<pf>(8));
    ASSERT_EQ(PrimeFieldElement<pf>(2).inv(), PrimeFieldElement<pf>(3));
    ASSERT_EQ(PrimeFieldElement<pf>(3) / PrimeFieldElement<pf>(4), PrimeFieldElement<pf>(12));
    ASSERT_EQ(PrimeFieldElement<pf>(2).pow(4), PrimeFieldElement<pf>(16));
}
