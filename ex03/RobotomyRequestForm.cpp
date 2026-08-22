#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"

RobotomyRequestForm::RobotomyRequestForm()
    : AForm("RobotomyRequestForm", 72, 45), target("DefaultTarget") {}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
    : AForm("RobotomyRequestForm", 72, 45), target(target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other)
    : AForm(other), target(other.target) {}

RobotomyRequestForm &
RobotomyRequestForm::operator=(const RobotomyRequestForm &other) {
  if (this != &other) {
    AForm::operator=(other);
    this->target = other.target;
  }
  return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const {
  checkExecutionRequirements(executor);

  std::cout << "* drilling noises *" << std::endl;

  static bool seeded = false;

  if (!seeded) {
    std::srand(std::time(NULL));
    seeded = true;
  }

  if (std::rand() % 2 == 0)
    std::cout << target << " has been robotomized successfully!" << std::endl;
  else
    std::cout << "Robotomy failed on " << target << std::endl;
}
