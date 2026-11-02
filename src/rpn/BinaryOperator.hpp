#pragma once

#include <cmath>
#include <stdexcept>

#include "RPN_Base.hpp"

namespace rpn {


template<typename T>
class BinaryOperator : public Operator<T> {
public:
    BinaryOperator(const std::string& sign) 
        : rpn::Operator<T>(sign) 
    {}

    void execute(std::stack<T>& stack) const override {
        try {
            T rhs = pop_and_top(stack);
            T lhs = pop_and_top(stack);
            stack.push(compute(lhs, rhs));
        }
        catch (EmptyStackError& e) {
            throw std::runtime_error("Not enough operands for binary operator " 
                + Operator<T>::get_sign());
        }
    }

protected:
    virtual T compute(T lhs, T rhs) const = 0;
};

template<typename T>
class Add : public BinaryOperator<T> {
public:
    Add() : BinaryOperator<T>("+") {}
    T compute(T lhs, T rhs) const override {
        return lhs + rhs;
    }
};

template<typename T>
class Minus : public BinaryOperator<T> {
public:
    Minus() : BinaryOperator<T>("-") {}
    T compute(T lhs, T rhs) const override {
        return lhs - rhs;
    }
};

template<typename T>
class Times : public BinaryOperator<T> {
public:
    Times() : BinaryOperator<T>("*") {}
    T compute(T lhs, T rhs) const override {
        return lhs * rhs;
    }
};

template<typename T>
class Divide: public BinaryOperator<T> {
public:
    Divide() : BinaryOperator<T>("/") {}
    T compute(T lhs, T rhs) const override {
        if (rhs == 0)
            throw std::runtime_error("Can't divide by 0.");
        return lhs / rhs;
    }
};

template <typename T>
class Pow : public BinaryOperator<T> {
public:
    Pow() : BinaryOperator<T>("pow") {}
    T compute(T lhs, T rhs) const override {
        return std::pow(lhs, rhs);
    }
};


}