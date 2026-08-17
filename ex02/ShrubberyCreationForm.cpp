#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

ShrubberyCreationForm::ShrubberyCreationForm()
    : AForm("ShrubberyCreationForm", 145, 137), target("DefaultTarget") {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
    : AForm("ShrubberyCreationForm", 145, 137), target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
    : AForm(other), target(other.target) {}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) {
  if (this != &other) {
    AForm::operator=(other);
    this->target = other.target;
  }
  return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const {
  this->checkExecutionRequirements(executor);

  std::string filename = this->target + "_shrubbery";
  std::ofstream outfile(filename.c_str());

  if (!outfile.is_open()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return;
  }

  outfile << "       _-_" << std::endl;
  outfile << "    /~~   ~~\\" << std::endl;
  outfile << " /~~         ~~\\" << std::endl;
  outfile << "{               }" << std::endl;
  outfile << " \\  _-     -_  /" << std::endl;
  outfile << "   ~  \\\\ //  ~" << std::endl;
  outfile << "_- -   | | _- _" << std::endl;
  outfile << "  _ -  | |   -_" << std::endl;
  outfile << "      // \\\\" << std::endl;

  outfile.close();
}
