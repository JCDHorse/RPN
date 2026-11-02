#pragma once

#include <stdexcept>
#include <vector>
#include <memory>

#include "RPN_Base.hpp"

namespace rpn {

template<typename T>
class Calculator {
public:
    Calculator() {}
    T execute(const std::vector<std::unique_ptr<Element<T>>>& rpnelems) const {
        std::stack<T> stack;
        for (const auto& elem : rpnelems) {
            elem->execute(stack);
        }
        if (stack.empty()) {
            throw std::runtime_error("Error: stack is empty.");
        }
        return pop_and_top(stack);
    }
};

} // namespace rpn