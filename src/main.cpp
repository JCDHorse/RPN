#include <exception>
#include <iostream>

#include "RPN.hpp"

int main() {
    using ValueType = long_double_t;
    std::cout << "RPN Calculator - 0.2" << std::endl;
    rpn::Parser<ValueType> parser;
    rpn::Calculator<ValueType> calc;
    std::string input;

    while (input != "end") {
        std::cout << "> ";

        if (!std::getline(std::cin, input))
            break;

        if (input == "end")
            break;

        try {
            auto elems = parser.parse(input);
            auto result = calc.execute(elems);
            std::cout << result << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
