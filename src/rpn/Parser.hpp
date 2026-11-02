#pragma once 

#include <sstream>
#include <functional>
#include <memory>

#include "RPN_Base.hpp"
#include "BinaryOperator.hpp"
#include "UnaryOperator.hpp"
#include "Number.hpp"

namespace rpn {
template<typename T>
class Parser {
public:
    Parser() : operators{
        {"+", &make<Add<T>>},
        {"-", &make<Minus<T>>},
        {"*", &make<Times<T>>},
        {"/", &make<Divide<T>>},
        {"abs", &make<Abs<T>>},
        {"pow", &make<Pow<T>>},
        {"pi", &make<Pi<T>>},
        {"e", &make<E<T>>},
        {"sin", &make<Sin<T>>},
        {"cos", &make<Cos<T>>},
        {"tan", &make<Tan<T>>},
    } {}

    std::vector<std::unique_ptr<Element<T>>> parse(const std::string& str) {
        std::vector<std::unique_ptr<Element<T>>> elems;
        std::istringstream iss(str);
        std::string token;

        while (iss >> token) {
            auto it = operators.find(token);
            if (it != operators.end()) {
                elems.push_back(it->second());
            }
            else {
                T number = parse_number(token);
                elems.push_back(std::make_unique<Number<T>>(number));
            }
        }

        return elems;
    }

private:
    using OperatorFactory = std::function<std::unique_ptr<Element<T>>()>;

    std::unordered_map<std::string, OperatorFactory> operators;

    template <typename Op>
    static std::unique_ptr<Element<T>> make() { 
        return std::make_unique<Op>(); 
    }


    T parse_number(const std::string_view& token) {
        T value {};
        const char* first = token.data();
        const char* last = first + token.size();
        auto [ptr, ec] = std::from_chars(first, last, value);

        if (ec == std::errc::result_out_of_range)
            throw std::runtime_error("Number out of range " + std::string(token));
        if (ec != std::errc{} || ptr != last)
            throw std::runtime_error("Invalid number: " + std::string(token));

        return value;
    }

};

} // namespace rpn