#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

#include "RPN.hpp"

namespace {

// Parse + exécute une expression RPN pour le type T.
template <typename T>
T eval(const std::string& expr) {
    rpn::Parser<T> parser;
    rpn::Calculator<T> calc;
    return calc.execute(parser.parse(expr));
}

// ---------------------------------------------------------------------------
// Tests communs aux entiers et aux flottants
// ---------------------------------------------------------------------------
template <typename T>
class RpnNumericTest : public ::testing::Test {};

using NumericTypes = ::testing::Types<int, long, double>;
TYPED_TEST_SUITE(RpnNumericTest, NumericTypes);

TYPED_TEST(RpnNumericTest, SingleNumber) {
    EXPECT_EQ(eval<TypeParam>("42"), TypeParam{42});
}

TYPED_TEST(RpnNumericTest, Addition) {
    EXPECT_EQ(eval<TypeParam>("3 4 +"), TypeParam{7});
}

TYPED_TEST(RpnNumericTest, SubtractionRespectsOperandOrder) {
    EXPECT_EQ(eval<TypeParam>("10 4 -"), TypeParam{6});
    EXPECT_EQ(eval<TypeParam>("4 10 -"), TypeParam{-6});
}

TYPED_TEST(RpnNumericTest, Multiplication) {
    EXPECT_EQ(eval<TypeParam>("6 7 *"), TypeParam{42});
}

TYPED_TEST(RpnNumericTest, DivisionRespectsOperandOrder) {
    EXPECT_EQ(eval<TypeParam>("20 4 /"), TypeParam{5});
}

TYPED_TEST(RpnNumericTest, NegativeNumber) {
    EXPECT_EQ(eval<TypeParam>("-3 2 *"), TypeParam{-6});
}

TYPED_TEST(RpnNumericTest, MinusAloneIsAnOperator) {
    EXPECT_EQ(eval<TypeParam>("5 3 -"), TypeParam{2});
}

TYPED_TEST(RpnNumericTest, ChainedExpression) {
    // (3 + 4) * 2 - 5 = 9
    EXPECT_EQ(eval<TypeParam>("3 4 + 2 * 5 -"), TypeParam{9});
}

TYPED_TEST(RpnNumericTest, ExtraWhitespaceIsIgnored) {
    EXPECT_EQ(eval<TypeParam>("   3   4    +  "), TypeParam{7});
}

TYPED_TEST(RpnNumericTest, CalculatorIsReusable) {
    rpn::Parser<TypeParam> parser;
    rpn::Calculator<TypeParam> calc;
    EXPECT_EQ(calc.execute(parser.parse("1 2 +")), TypeParam{3});
    EXPECT_EQ(calc.execute(parser.parse("5 5 *")), TypeParam{25});
}

TYPED_TEST(RpnNumericTest, UnknownTokenThrows) {
    EXPECT_THROW(eval<TypeParam>("abc"), std::runtime_error);
    EXPECT_THROW(eval<TypeParam>("1 2 ^"), std::runtime_error);
    EXPECT_THROW(eval<TypeParam>("12abc 3 +"), std::runtime_error);
}

TYPED_TEST(RpnNumericTest, PlusSignPrefixIsRejected) {
    // std::from_chars n'accepte pas le '+' initial.
    EXPECT_THROW(eval<TypeParam>("+3 2 +"), std::runtime_error);
}

TYPED_TEST(RpnNumericTest, OutOfRangeNumberThrows) {
    EXPECT_THROW(eval<TypeParam>("1" + std::string(400, '0') + " 1 +"),
                 std::runtime_error);
}

// ---------------------------------------------------------------------------
// Entiers uniquement
// ---------------------------------------------------------------------------
TEST(RpnIntTest, IntegerDivisionTruncates) {
    EXPECT_EQ(eval<int>("7 2 /"), 3);
    EXPECT_EQ(eval<int>("-7 2 /"), -3);
}

TEST(RpnIntTest, DecimalNumberIsRejected) {
    EXPECT_THROW(eval<int>("3.5 2 +"), std::runtime_error);
}

// ---------------------------------------------------------------------------
// Flottants uniquement
// ---------------------------------------------------------------------------
TEST(RpnDoubleTest, DecimalArithmetic) {
    EXPECT_DOUBLE_EQ(eval<double>("3.5 2 +"), 5.5);
    EXPECT_DOUBLE_EQ(eval<double>("1 4 /"), 0.25);
    EXPECT_DOUBLE_EQ(eval<double>("-2.5 2 *"), -5.0);
}

TEST(RpnDoubleTest, ScientificNotation) {
    EXPECT_DOUBLE_EQ(eval<double>("1e-3 1000 *"), 1.0);
}

// ---------------------------------------------------------------------------
// Parser
// ---------------------------------------------------------------------------
TEST(RpnParserTest, EmptyStringGivesNoElements) {
    rpn::Parser<int> parser;
    EXPECT_TRUE(parser.parse("").empty());
    EXPECT_TRUE(parser.parse("   ").empty());
}

TEST(RpnParserTest, ElementCount) {
    rpn::Parser<int> parser;
    EXPECT_EQ(parser.parse("1 2 + 3 *").size(), 5u);
}

// ---------------------------------------------------------------------------
// Expressions invalides.
// Ces tests dépendent du comportement de Stack<T>::pop() sur pile vide :
// il doit lever une exception (et non avoir un comportement indéfini).
// ---------------------------------------------------------------------------
TEST(RpnErrorTest, EmptyExpressionThrows) {
    EXPECT_ANY_THROW(eval<int>(""));
}

TEST(RpnErrorTest, OperatorWithoutOperandsThrows) {
    EXPECT_ANY_THROW(eval<int>("+"));
}

TEST(RpnErrorTest, OperatorWithMissingOperandThrows) {
    EXPECT_ANY_THROW(eval<int>("1 +"));
}

// ---------------------------------------------------------------------------
// Tests désactivés : ils échouent tant que les corrections suggérées en revue
// ne sont pas appliquées. Retire le préfixe DISABLED_ une fois fait.
// ---------------------------------------------------------------------------
TEST(RpnErrorTest, DISABLED_LeftoverOperandsThrow) {
    EXPECT_THROW(eval<int>("1 2"), std::runtime_error);
}

TEST(RpnErrorTest, DISABLED_IntDivisionByZeroThrows) {
    EXPECT_THROW(eval<int>("1 0 /"), std::domain_error);
}

TEST(RpnErrorTest, DISABLED_DoubleDivisionByZeroThrows) {
    EXPECT_THROW(eval<double>("1 0 /"), std::domain_error);
}

}  // namespace