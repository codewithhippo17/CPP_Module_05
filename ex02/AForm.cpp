#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm()
    : name("Default"), isSigned(false), gradeToSign(150), gradeToExecute(150) {}

AForm::AForm(const std::string &name, int gradeToSign, int gradeToExecute)
    : name(name), isSigned(false), gradeToSign(gradeToSign),
      gradeToExecute(gradeToExecute) {
  if (gradeToSign < 1 || gradeToExecute < 1)
    throw GradeTooHighException();
  if (gradeToSign > 150 || gradeToExecute > 150)
    throw GradeTooLowException();
}

AForm::AForm(const AForm &other)
    : name(other.name), isSigned(other.isSigned),
      gradeToSign(other.gradeToSign), gradeToExecute(other.gradeToExecute) {}

AForm &AForm::operator=(const AForm &other) {
  if (this != &other)
    this->isSigned = other.isSigned;
  return *this;
}

AForm::~AForm() {}

// Getters

const std::string &AForm::getName() const { return name; }

bool AForm::getIsSigned() const { return isSigned; }

int AForm::getGradeToSign() const { return gradeToSign; }

int AForm::getGradeToExecute() const { return gradeToExecute; }

// Actions

void AForm::beSigned(const Bureaucrat &bureaucrat) {
  if (bureaucrat.getGrade() > this->gradeToSign)
    throw GradeTooLowException();
  this->isSigned = true;
}

void AForm::checkExecutionRequirements(const Bureaucrat &executor) const {
  if (!this->isSigned)
    throw NotSignedException();
  if (executor.getGrade() > this->gradeToExecute)
    throw GradeTooLowException();
}

// Exceptions

const char *AForm::GradeTooHighException::what() const throw() {
  return "Form grade too high";
}

const char *AForm::GradeTooLowException::what() const throw() {
  return "Form grade too low";
}

const char *AForm::NotSignedException::what() const throw() {
  return "Form is not signed";
}

std::ostream &operator<<(std::ostream &os, const AForm &f) {
  os << "Form: " << f.getName()
     << ", signed: " << (f.getIsSigned() ? "yes" : "no")
     << ", grade to sign: " << f.getGradeToSign()
     << ", grade to execute: " << f.getGradeToExecute();
  return os;
}
