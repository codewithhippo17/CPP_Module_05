#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>
#include <string>

class Bureaucrat;

class AForm {
private:
  const std::string name;
  bool isSigned;
  const int gradeToSign;
  const int gradeToExecute;

public:
  AForm();
  AForm(const std::string &name, int gradeToSign, int gradeToExecute);
  AForm(const AForm &other);
  AForm &operator=(const AForm &other);
  virtual ~AForm(); // Must be virtual for an abstract base class!

  const std::string &getName() const;
  bool getIsSigned() const;
  int getGradeToSign() const;
  int getGradeToExecute() const;

  void beSigned(const Bureaucrat &bureaucrat);
  
  // This pure virtual function makes the class Abstract!
  virtual void execute(Bureaucrat const & executor) const = 0;
  
  // Helper function for derived classes to check execution requirements
  void checkExecutionRequirements(const Bureaucrat &executor) const;

  class GradeTooHighException : public std::exception {
  public:
    const char *what() const throw();
  };

  class GradeTooLowException : public std::exception {
  public:
    const char *what() const throw();
  };
  
  class NotSignedException : public std::exception {
  public:
    const char *what() const throw();
  };
};

std::ostream &operator<<(std::ostream &os, const AForm &f);

#endif
