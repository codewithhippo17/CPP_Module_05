#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

int main() {
  std::cout << "=== BUREAUCRAT SETUP ===" << std::endl;
  Bureaucrat boss("The Boss", 1);
  Bureaucrat midTier("Mid-Tier", 50);
  Bureaucrat intern("Intern", 150);

  std::cout << boss << std::endl;
  std::cout << midTier << std::endl;
  std::cout << intern << std::endl;

  std::cout << "\n=== SHRUBBERY CREATION FORM TESTS ===" << std::endl;
  ShrubberyCreationForm shrub("Garden");
  intern.signForm(shrub);
  midTier.signForm(shrub);
  intern.executeForm(shrub);
  midTier.executeForm(shrub);

  std::cout << "\n=== ROBOTOMY REQUEST FORM TESTS ===" << std::endl;
  RobotomyRequestForm robo("Bender");
  midTier.signForm(robo);
  midTier.executeForm(robo);
  boss.executeForm(robo);
  boss.executeForm(robo);
  boss.executeForm(robo);

  std::cout << "\n=== PRESIDENTIAL PARDON FORM TESTS ===" << std::endl;
  PresidentialPardonForm pardon("Arthur Dent");
  boss.executeForm(pardon);
  boss.signForm(pardon);
  boss.executeForm(pardon);

  return 0;
}
