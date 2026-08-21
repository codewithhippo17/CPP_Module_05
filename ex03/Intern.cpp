#include "Intern.hpp"

// canonical form

Intern::Intern() {}

Intern::Intern(const Intern &src) { *this = src; }

Intern &Intern::operator=(const Intern &src) {
  if (this == &src)
    return *this;
  return *this;
}

Intern::~Intern() {}

static AForm *makePresident(const std::string &target) {
  return new PresidentialPardonForm(target);
}

static AForm *makeRobot(const std::string &target) {
  return new RobotomyRequestForm(target);
}

static AForm *makeShrubbery(const std::string &target) {
  return new ShrubberyCreationForm(target);
}

AForm *Intern::makeForm(const std::string &formName,
                        const std::string &target) const {

  static const std::string names[] = {"presidential pardon", "robotomy request",
                                      "shrubbery creation"};
  static AForm *(*makers[])(const std::string &) = {&makePresident, &makeRobot,
                                                    &makeShrubbery};
  for (int i = 0; i < 3; i++) {
    if (formName == names[i]) {
      std::cout << "Intern creates " << formName << std::endl;
      return makers[i](target);
    }
  }
  std::cout << "Intern cannot create a form called " << formName << std::endl;
  return NULL;
}
