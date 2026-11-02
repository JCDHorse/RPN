#pragma once

#include <cmath>

#include "RPN_Base.hpp"

namespace rpn {

template <typename T>
class UnaryOperator : public Operator<T> {
public:
    UnaryOperator(const std::string& sign) 
        : rpn::Operator<T>(sign) 
    {}

    void execute(Stack<T>& stack) const override {
        try {
            T operand = stack.pop();
            stack.push(compute(operand));
        }
        catch (StackEmptyError& e) {
            throw std::runtime_error("Not enough operands for unary operator " 
                + Operator<T>::get_sign());
        }
    }
protected:
    virtual T compute(T operand) const = 0;
};

template <typename T>
class Abs : public UnaryOperator<T> {
public: 
    Abs() : UnaryOperator<T>("abs") {}
protected:

    T compute(T operand) const override {
        return std::abs(operand);
    }
};

template <typename T>
class Sin : public UnaryOperator<T> {
public:
    Sin() : UnaryOperator<T>("sin") {}
    T compute(T operand) const override {
        return std::sin(operand);
    }
};

template <typename T>
class Cos : public UnaryOperator<T> {
public:
    Cos() : UnaryOperator<T>("cos") {}
    T compute(T operand) const override {
        return std::cos(operand);
    }
};

template <typename T>
class Tan: public UnaryOperator<T> {
public:
    Tan() : UnaryOperator<T>("Tan") {}
    T compute(T operand) const override {
        return std::tan(operand);
    }
};

} // namespace rpn
