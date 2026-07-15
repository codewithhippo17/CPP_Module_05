
#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>

class Form {
private:
  const std::string name;
  bool isSigned;
  int gradeToExecute;
  int gradeToSign;

public:
  Form();
  Form(const std::string &name, int grade);
  Form(const Form &other);
  Form &operator=(const Form &other);
  ~Form();

  const std::string &getName() const;
  int getGrade() const;

  void incrementGrade();
  void decrementGrade();

  void beSigned(const Bureaucrat &bureaucrat);

  class GradeTooHighException : public std::exception {
  public:
    const char *what() const throw();
  };

  class GradeTooLowException : public std::exception {
  public:
    const char *what() const throw();
  };
};

std::ostream &operator<<(std::ostream &os, const Bureaucrat &b);

#endif // BUREAUCRAT_HPP
