#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main() {
  std::cout << "=== BUREAUCRAT SETUP ===" << std::endl;
  Bureaucrat boss("The Boss", 1); // Can do everything
  Bureaucrat midTier("Mid-Tier", 50); // Can sign Shrub/Robo, exec Shrub
  Bureaucrat intern("Intern", 150); // Can do nothing

  std::cout << boss << std::endl;
  std::cout << midTier << std::endl;
  std::cout << intern << std::endl;

  std::cout << "\n=== SHRUBBERY CREATION FORM TESTS ===" << std::endl;
  // Sign: 145, Exec: 137
  ShrubberyCreationForm shrub("Garden");
  
  // Intern tries to sign (fails, grade 150 > 145)
  intern.signForm(shrub);
  
  // Mid-Tier signs it (success, grade 50 <= 145)
  midTier.signForm(shrub);
  
  // Intern tries to execute (fails, grade 150 > 137)
  intern.executeForm(shrub);
  
  // Mid-Tier executes it (success, grade 50 <= 137)
  midTier.executeForm(shrub);

  std::cout << "\n=== ROBOTOMY REQUEST FORM TESTS ===" << std::endl;
  // Sign: 72, Exec: 45
  RobotomyRequestForm robo("Bender");
  
  // Mid-Tier signs it (success, grade 50 <= 72)
  midTier.signForm(robo);
  
  // Mid-Tier tries to execute (fails, grade 50 > 45)
  midTier.executeForm(robo);
  
  // Boss executes it (success, grade 1 <= 45)
  // Run this a few times to see the 50% chance if implemented correctly
  boss.executeForm(robo);
  boss.executeForm(robo);
  boss.executeForm(robo);

  std::cout << "\n=== PRESIDENTIAL PARDON FORM TESTS ===" << std::endl;
  // Sign: 25, Exec: 5
  PresidentialPardonForm pardon("Arthur Dent");
  
  // Boss tries to execute before signing (fails, Not Signed Exception)
  boss.executeForm(pardon);
  
  // Boss signs it
  boss.signForm(pardon);
  
  // Boss executes it
  boss.executeForm(pardon);

  return 0;
}
