//
// Created by Mikhail Kiselyov on 24.02.2023.
//

#include "gtest/gtest.h"
#include "PrimeFieldElement.hpp"

using namespace FiniteFields;

TEST(PrimeFieldElementSuite, PrimeBase) {
    EXPECT_NO_THROW({ PrimeFieldElement<2> a(0); });
    EXPECT_NO_THROW({ PrimeFieldElement<3> b(1); });
    EXPECT_NO_THROW({ PrimeFieldElement<5> c(2); });
    EXPECT_NO_THROW({ PrimeFieldElement<7> d(-1); });
    EXPECT_NO_THROW({ PrimeFieldElement<11> e(4); });
    EXPECT_NO_THROW({ PrimeFieldElement<13> f(4); });
}

TEST(PrimeFieldElementSuite, NonPrimeBase) {
    EXPECT_ANY_THROW({ PrimeFieldElement<4> a(0); });
    EXPECT_ANY_THROW({ PrimeFieldElement<6> b(1); });
    EXPECT_ANY_THROW({ PrimeFieldElement<9> c(2); });
    EXPECT_ANY_THROW({ PrimeFieldElement<10> d(-1); });
    EXPECT_ANY_THROW({ PrimeFieldElement<12> e(4); });
    EXPECT_ANY_THROW({ PrimeFieldElement<15> f(4); });
}

TEST(PrimeFieldElementSuite, SimpleArithmetic1) {
    PrimeFieldElement<5> a(0);
    PrimeFieldElement<5> b(1);
    PrimeFieldElement<5> c(2);
    PrimeFieldElement<5> d(-1);
    PrimeFieldElement<5> e(4);

    ASSERT_EQ(b - b, a);
    ASSERT_EQ(b + b, c);
    ASSERT_EQ(d, e);
}

TEST(PrimeFieldElementSuite, SimpleArithmetic2) {
    ASSERT_EQ(PrimeFieldElement<5>(2) * PrimeFieldElement<5>(4), PrimeFieldElement<5>(8));
    ASSERT_EQ(PrimeFieldElement<5>(2).inv(), PrimeFieldElement<5>(3));
    ASSERT_EQ(PrimeFieldElement<5>(3) / PrimeFieldElement<5>(4), PrimeFieldElement<5>(12));
    ASSERT_EQ(PrimeFieldElement<5>(2).pow(4), PrimeFieldElement<5>(16));
}
