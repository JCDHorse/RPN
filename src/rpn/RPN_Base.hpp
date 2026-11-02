#pragma once

#include <stdexcept>
#include <string>
#include <stack>

namespace rpn {

class EmptyStackError : public std::runtime_error  {
public:
    EmptyStackError()
        : std::runtime_error("stack is empty.")
    {}
};

template <typename T>
T pop_and_top(std::stack<T>& stack) {
    if (stack.empty()) 
        throw EmptyStackError();

    T top = stack.top();
    stack.pop();
    return top;
}

template <typename T>
class Element
{
public:
    virtual void execute(std::stack<T>& stack) const = 0;
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