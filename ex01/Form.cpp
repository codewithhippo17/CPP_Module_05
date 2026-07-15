#include "Form.hpp"
#include "Bureaucrat.hpp"

// Orthodox Canonical Form

Form::Form()
    : name("Default"), isSigned(false), gradeToSign(150), gradeToExecute(150) {}

Form::Form(const std::string &name, int gradeToSign, int gradeToExecute)
    : name(name), isSigned(false), gradeToSign(gradeToSign),
      gradeToExecute(gradeToExecute) {
  if (gradeToSign < 1 || gradeToExecute < 1)
    throw GradeTooHighException();
  if (gradeToSign > 150 || gradeToExecute > 150)
    throw GradeTooLowException();
}

Form::Form(const Form &other)
    : name(other.name), isSigned(other.isSigned),
      gradeToSign(other.gradeToSign), gradeToExecute(other.gradeToExecute) {}

Form &Form::operator=(const Form &other) {
  if (this != &other)
    this->isSigned = other.isSigned;
  return *this;
}

Form::~Form() {}

// Getters

const std::string &Form::getName() const { return name; }

bool Form::getIsSigned() const { return isSigned; }

int Form::getGradeToSign() const { return gradeToSign; }

int Form::getGradeToExecute() const { return gradeToExecute; }

// beSigned

void Form::beSigned(const Bureaucrat &bureaucrat) {
  if (bureaucrat.getGrade() > this->gradeToSign)
    throw GradeTooLowException();
  this->isSigned = true;
}

// Exception what() methods

const char *Form::GradeTooHighException::what() const throw() {
  return "Form grade too high";
}

const char *Form::GradeTooLowException::what() const throw() {
  return "Form grade too low";
}

// Stream insertion operator

std::ostream &operator<<(std::ostream &os, const Form &f) {
  os << "Form: " << f.getName()
     << ", signed: " << (f.getIsSigned() ? "yes" : "no")
     << ", grade to sign: " << f.getGradeToSign()
     << ", grade to execute: " << f.getGradeToExecute();
  return os;
}
