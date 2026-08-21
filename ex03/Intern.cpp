#include "Intern.hpp"

// canonical form

Intern::Intern() {}

Intern::Intern(const Intern &src) { *this = src; }

Intern::~Intern() { std::cout << "Intern Deconstructor called" << std::endl; }

Intern &Intern::operator=(const Intern &src) {
  if (this == &src)
    return *this;
  return *this;
}
