#pragma once

#include <vector>
#include <memory>

#include "RPN_Base.hpp"

namespace rpn {

template<typename T>
class Calculator {
public:
    Calculator() {}
    T execute(const std::vector<std::unique_ptr<Element<T>>>& rpnelems) const {
        Stack<T> stack;
        for (const auto& elem : rpnelems) {
            elem->execute(stack);
        }
        return stack.pop();
    }
};

} // namespace rpn