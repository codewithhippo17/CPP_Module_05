#include "Bureaucrat.hpp"

int main() {
    std::cout << "=== VALID TEST ===" << std::endl;
    try {
        Bureaucrat b1("Alice", 42);
        std::cout << b1 << std::endl;

        b1.incrementGrade();
        std::cout << "After increment: " << b1 << std::endl;

        b1.decrementGrade();
        std::cout << "After decrement: " << b1 << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== TOO HIGH TEST ===" << std::endl;
    try {
        Bureaucrat b2("Bob", 0); // invalid → too high
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== TOO LOW TEST ===" << std::endl;
    try {
        Bureaucrat b3("Charlie", 151); // invalid → too low
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== INCREMENT LIMIT TEST ===" << std::endl;
    try {
        Bureaucrat b4("Dave", 1);
        std::cout << b4 << std::endl;

        b4.incrementGrade(); // should throw
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== DECREMENT LIMIT TEST ===" << std::endl;
    try {
        Bureaucrat b5("Eve", 150);
        std::cout << b5 << std::endl;

        b5.decrementGrade(); // should throw
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
