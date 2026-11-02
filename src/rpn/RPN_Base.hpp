#pragma once

#include "Stack.hpp"

#include <string>

namespace rpn {


template <typename T>
class Element
{
public:
    virtual void execute(Stack<T>& stack) const = 0;
    virtual ~Element() = default;
};

template <typename T>
class Operator : public Element<T> {
private:
    std::string sign;
protected:
    Operator(const std::string& _sign) : sign(_sign) {}
    std::string get_sign() const {
        return sign;
    }
};

} // namespace rpn