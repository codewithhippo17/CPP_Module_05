#include "Bureaucrat.hpp"

// canonical form

Bureaucrat::Bureaucrat() : name("Default"), grade(150) {}

Bureaucrat::Bureaucrat(const std::string &name, int grade)
    : name(name), grade(grade) {
  if (grade < 1)
    throw GradeTooHighException();
  if (grade > 150)
    throw GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat &other)
    : name(other.name), grade(other.grade) {}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other) {
  if (this != &other)
    this->grade = other.grade;
  return *this;
}

Bureaucrat::~Bureaucrat() {}

std::ostream &operator<<(std::ostream &os, const Bureaucrat &b) {
  os << b.getName() << ", bureaucrat grade " << b.getGrade();
  return os;
}

// Getters

const std::string &Bureaucrat::getName() const { return name; }

int Bureaucrat::getGrade() const { return grade; }

// accumulate grades

void Bureaucrat::incrementGrade() {
  if (grade <= 1)
    throw GradeTooHighException();
  grade--;
}

void Bureaucrat::decrementGrade() {
  if (grade >= 150)
    throw GradeTooLowException();
  grade++;
}

// exception handling

const char *Bureaucrat::GradeTooHighException::what() const throw() {
  return "Grade too high";
}

const char *Bureaucrat::GradeTooLowException::what() const throw() {
  return "Grade too low";
}
