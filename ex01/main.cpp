#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

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

    b5.decrementGrade();
  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  std::cout << "\n=== FORM CREATION TEST ===" << std::endl;
  try {
    Form f1("Tax Form 28B", 50, 20);
    std::cout << f1 << std::endl; 
  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  std::cout << "\n=== SUCCESSFUL SIGNING TEST ===" << std::endl;
  try {
    Bureaucrat boss("The Boss", 1);
    Form f2("Important Contract", 50, 20);
    
    std::cout << boss << std::endl;
    std::cout << f2 << std::endl;

    boss.signForm(f2);
    
    std::cout << f2 << std::endl;
  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  std::cout << "\n=== FAILED SIGNING TEST ===" << std::endl;
  try {
    Bureaucrat intern("Intern", 150);
    Form f3("Top Secret Document", 10, 5);
    
    std::cout << intern << std::endl;
    std::cout << f3 << std::endl;

    intern.signForm(f3);
    
    std::cout << f3 << std::endl;
  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  std::cout << "\n=== FORM INVALID GRADES TEST ===" << std::endl;
  try {
    std::cout << "Trying to create a Form with gradeToSign = 0..." << std::endl;
    Form invalidForm("Invalid", 0, 50);
  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }
  
  try {
    std::cout << "Trying to create a Form with gradeToExecute = 151..." << std::endl;
    Form invalidForm2("Invalid2", 50, 151);
  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
