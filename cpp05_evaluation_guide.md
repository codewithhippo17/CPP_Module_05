# C++ Module 05 - Evaluation Guide

This guide breaks down each exercise of C++ Module 05, explaining the core concepts, what the code does, and what you should explain or demonstrate during a 42 evaluation.

## General Module Concept: Exceptions
Module 05 introduces **Exceptions** in C++ (`try`, `catch`, `throw`).
The main rule to remember: **Never use pointers for exceptions**. Always throw objects and catch them by reference (e.g., `catch (std::exception &e)`). This prevents object slicing and memory leaks.

---

## Exercise 00: Mommy, when I grow up, I want to be a bureaucrat!

### 💡 Core Concept
Creating a basic class (`Bureaucrat`) with custom exceptions. 
Bureaucrats have a name (constant) and a grade (1 is highest, 150 is lowest).

### 🔍 What to explain during evaluation
1.  **Custom Exceptions**: Show how `GradeTooHighException` and `GradeTooLowException` inherit from `std::exception` and override the `what()` method.
2.  **Grade Bounds**: Explain that grade 1 is the highest and 150 is the lowest. If you try to instantiate or increment a Bureaucrat past 1, it throws `GradeTooHighException`.
3.  **Try/Catch Blocks**: In `main.cpp`, demonstrate how you wrap the instantiation and increment/decrement logic in `try {}` blocks, and how the `catch` block gracefully handles the error without crashing the program.
4.  **Const Name**: Show that the name is `const std::string`, meaning it's initialized in the constructor's initialization list and cannot be changed later.

### 🧪 What to test
*   Create a Bureaucrat with grade 0 (should catch GradeTooHigh).
*   Create a Bureaucrat with grade 151 (should catch GradeTooLow).
*   Create a Bureaucrat with grade 1, then decrement it (should work, grade becomes 2).
*   Create a Bureaucrat with grade 1, then increment it (should throw exception).

---

## Exercise 01: Form up, maggots!

### 💡 Core Concept
Interaction between two classes: `Bureaucrat` and `Form`. Forms require a specific grade to be signed and executed.

### 🔍 What to explain during evaluation
1.  **Form Attributes**: A Form has a name, a boolean indicating if it's signed (default false), a grade required to sign, and a grade required to execute.
2.  **Double Exception Checking**: Similar to Bureaucrat, the Form constructor must throw if the provided grades are out of bounds (1-150).
3.  **The `beSigned` Method**: Explain how `beSigned(Bureaucrat &b)` works. If the Bureaucrat's grade is higher or equal (meaning numerically lower or equal) to the sign grade, the form becomes signed. If not, it throws a `GradeTooLowException`.
4.  **Bureaucrat's `signForm`**: Explain the `signForm()` method in Bureaucrat, which prints `<bureaucrat> signed <form>` or `<bureaucrat> couldn't sign <form> because <reason>`.

### 🧪 What to test
*   Try creating a Form with an invalid grade (e.g., 0 or 151).
*   Have a low-level Bureaucrat try to sign a high-level Form (should fail and print the reason).
*   Have a high-level Bureaucrat sign a form (should succeed).

---

## Exercise 02: No, you need form 28B, not 28C...

### 💡 Core Concept
Abstract classes and inheritance. The base `Form` class becomes `AForm` (Abstract Form), and we create three concrete forms with specific behaviors.

### 🔍 What to explain during evaluation
1.  **Abstract Base Class**: Show that `AForm` has a pure virtual function `virtual void execute(Bureaucrat const & executor) const = 0;`. This makes the class abstract (you can't instantiate `AForm` directly).
2.  **Execution Requirements**: Explain the logic in the base class or derived classes that checks two things before executing:
    *   Is the form signed? (If not, throw `FormNotSignedException`).
    *   Does the Bureaucrat have a high enough grade to execute it? (If not, throw `GradeTooLowException`).
3.  **The Three Concrete Forms**:
    *   **ShrubberyCreationForm**: Show how it creates a file `<target>_shrubbery` and writes ASCII trees inside it.
    *   **RobotomyRequestForm**: Show the 50% chance logic (using `rand()` or similar) to either robotomize the target or fail.
    *   **PresidentialPardonForm**: Simply prints that Zaphod Beeblebrox pardoned the target.
4.  **Bureaucrat's `executeForm`**: Show how the Bureaucrat attempts to execute the form and prints success or the exception caught.

### 🧪 What to test
*   Attempt to execute an unsigned form (should throw).
*   Sign a form, but try to execute it with a Bureaucrat who doesn't have the required execution grade (should throw).
*   Successfully sign and execute all three forms (check that the shrubbery file is actually created).

---

## Exercise 03: At least this beats coffee-making

### 💡 Core Concept
Pointers to member functions or factory patterns to avoid massive `if/else if` blocks.

### 🔍 What to explain during evaluation
1.  **The Intern Class**: The Intern has no name, no grade, and only one useful function: `makeForm(std::string formName, std::string target)`.
2.  **Avoiding If/Else Forests**: Show how you implemented `makeForm`. The subject explicitly states: "You must avoid unreadable and ugly macros, and endless if/elseif/else branching."
    *   *Good Approach*: An array of strings containing the form names, and an array of pointers to member functions (or an array of objects) that create the respective forms.
3.  **Return Value**: It returns a pointer to a newly allocated `AForm`.
4.  **Error Handling**: Show what happens if an unknown form name is passed (it should print an explicit error message and return `NULL` or throw an exception, depending on your implementation choice).

### 🧪 What to test
*   Have the Intern create a "robotomy request" form (should return a valid pointer).
*   Have the Intern try to create a "nonexistent form" (should handle the error cleanly without crashing).
