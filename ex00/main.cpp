#include "Bureaucrat.hpp"

int main() {
  std::cout << "=== VALID TEST ===" << std::endl;
  try {
    Bureaucrat b1("Abdul", 42);
    std::cout << b1 << std::endl;

    b1.incrementGrade();
    std::cout << "After increment: " << b1 << std::endl;

    b1.decrementGrade();
    std::cout << "After decrement: " << b1 << std::endl;
  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  std::cout << "\n=== TOO HIGH TEST ===" << std::endl;
  try {
    Bureaucrat b2("Hippo", 0);
  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  std::cout << "\n=== TOO LOW TEST ===" << std::endl;
  try {
    Bureaucrat b3("Simo", 151);
  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  std::cout << "\n=== INCREMENT LIMIT TEST ===" << std::endl;
  try {
    Bureaucrat b4("Karim", 1);
    std::cout << b4 << std::endl;

    b4.incrementGrade();
  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  std::cout << "\n=== DECREMENT LIMIT TEST ===" << std::endl;
  try {
    Bureaucrat b5("Qassem", 150);
    std::cout << b5 << std::endl;

    b5.decrementGrade(); // should throw
  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
