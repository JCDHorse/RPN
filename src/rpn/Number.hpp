#pragma once

#include "RPN_Base.hpp"

namespace rpn {

template <typename T>
class Number : public Element<T> {
public:
    Number(T _value) : value(_value) {}

    void execute(Stack<T>& stack) const override {
        stack.push(value);
    }

private:
    T value;
};

template <std::floating_point T>
class Pi : public Number<T> {
public:
    Pi() : Number<T>(std::numbers::pi_v<T>) {}
};

template <std::floating_point T>
class E : public Number<T> {
public:
    E() : Number<T>(std::numbers::e_v<T>) {}
};

} // namespace rpn