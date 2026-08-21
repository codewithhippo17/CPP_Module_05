# CPP Module 05 — Evaluation Prep
> Your complete line-by-line guide. Read this tonight. Sleep well.

---

## The Big Picture — What This Module Is About

Every exercise in this module teaches **one core idea**:

> When something goes wrong that you **cannot return a value for**, you throw an exception.

A constructor has no return value. A grade-setter has no meaningful error return. So instead of returning `-1` or `false` and hoping the caller checks it, you **throw** — and C++ guarantees the caller sees it.

---

## How Exceptions Flow in C++98 — The Mental Model

```
try {
    // 1. Normal code runs here
    //    If any line throws...
    Bureaucrat b("Bob", 0);  // <-- throws here

    // 2. Everything AFTER the throw is SKIPPED
    std::cout << "this never prints";

} catch (std::exception& e) {
    // 3. Execution jumps HERE instantly
    //    'e' is the exception that was thrown
    std::cout << e.what();   // "Grade too high"
}
// 4. Program continues here normally after catch
```

The throw **unwinds the stack** — every function between the throw and the catch gets cleaned up automatically. Local objects get their destructors called. Memory is safe.

---

## Exercise 00 — Bureaucrat

### What the class looks like

```
Bureaucrat
├── name  (const string — never changes after construction)
├── grade (int — 1 = highest rank, 150 = lowest rank)
│
├── GradeTooHighException   ← nested class inside Bureaucrat
└── GradeTooLowException    ← nested class inside Bureaucrat
```

### The nested exception classes — why they live *inside* Bureaucrat

```cpp
// In Bureaucrat.hpp:
class Bureaucrat {
  public:
    class GradeTooHighException : public std::exception {
      public:
        const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
      public:
        const char* what() const throw();
    };
};
```

**Q: Why are the exception classes inside Bureaucrat?**  
A: Because they *belong* to Bureaucrat. When a Bureaucrat fails, it's a Bureaucrat problem. The nesting makes the ownership clear. You access them as `Bureaucrat::GradeTooHighException` — the `::` tells you exactly where this exception comes from.

**Q: Why do they inherit from `std::exception`?**  
A: So callers can catch them with `catch(std::exception& e)` — a single generic catch that works for *all* standard exceptions. Without inheriting from `std::exception`, you'd need a separate catch for each type.

**Q: What is `const char* what() const throw()`?**  
- `const char*` — returns a C-string (a pointer to characters)
- `what()` — the name. All exceptions have this method. It's defined in `std::exception`
- `const` after `what()` — this method doesn't modify the exception object
- `throw()` — C++98 way of saying "this function will not throw". It's a promise.

### The constructor — where throwing happens

```cpp
// In Bureaucrat.cpp:
Bureaucrat::Bureaucrat(const std::string& name, int grade)
    : name(name), grade(grade) {   // <-- initializer list runs FIRST
  if (grade < 1)
    throw GradeTooHighException();  // grade 0, -1, -100 = too high (too powerful)
  if (grade > 150)
    throw GradeTooLowException();   // grade 151, 200 = too low (too weak)
}
```

**Step by step when `Bureaucrat b("Bob", 0)` runs:**
1. Initializer list: `name = "Bob"`, `grade = 0` — these run BEFORE the body
2. Body starts: `if (grade < 1)` → `0 < 1` → true
3. `throw GradeTooHighException()` — creates a GradeTooHighException object and throws it
4. The constructor body STOPS immediately
5. Because the constructor threw, `b` was **never fully created** — it doesn't exist
6. Stack unwinds to the nearest `catch(std::exception&)`
7. `what()` returns `"Grade too high"`

**Q: Why is grade 1 "too high" and grade 150 "too low"?**  
A: In this bureaucracy, 1 is the boss (highest power), 150 is the intern (lowest power). "Too high" means the number is too high to be valid (below 1). "Too low" means the number is too low in rank (above 150). Confusing at first — but remember: **lower number = more powerful**.

### incrementGrade and decrementGrade

```cpp
void Bureaucrat::incrementGrade() {
  if (grade <= 1)
    throw GradeTooHighException();  // Can't go higher than 1
  grade--;  // 42 → 41 (more powerful)
}

void Bureaucrat::decrementGrade() {
  if (grade >= 150)
    throw GradeTooLowException();   // Can't go lower than 150
  grade++;  // 42 → 43 (less powerful)
}
```

**Why `grade--` makes the bureaucrat MORE powerful:** lower number = higher rank. Decrementing the integer = promoting the person.

**Why check BEFORE changing:** If you changed first then threw, the grade would be in an invalid state. Check → throw early → only change if safe.

### The stream operator

```cpp
std::ostream& operator<<(std::ostream& os, const Bureaucrat& b) {
  os << b.getName() << ", bureaucrat grade " << b.getGrade();
  return os;
}
```

This is what lets you write `std::cout << b1`. The `<<` operator is overloaded to print the bureaucrat's name and grade in the required format.

**Q: Why return `os`?**  
A: So you can chain: `std::cout << b1 << std::endl`. Each `<<` returns the stream, so the next `<<` has something to operate on.

### ex00 main.cpp — what each test does

| Test | Input | Expected behavior |
|------|-------|-------------------|
| VALID TEST | grade 42 | Prints name+grade, increments to 41, decrements to 42 |
| TOO HIGH TEST | grade 0 | Constructor throws GradeTooHighException, prints "Grade too high" |
| TOO LOW TEST | grade 151 | Constructor throws GradeTooLowException, prints "Grade too low" |
| INCREMENT LIMIT | grade 1, then increment | Prints grade 1, then throws GradeTooHighException |
| DECREMENT LIMIT | grade 150, then decrement | Prints grade 150, then throws GradeTooLowException |

---

## Exercise 01 — Form

### What changed from ex00

Bureaucrat gets a new method: `signForm(Form& form)`.  
Form is a new class with its own exception classes.

### The Form class

```
Form
├── name          (const string)
├── isSigned      (bool — starts false)
├── gradeToSign   (const int — minimum rank needed to sign)
├── gradeToExecute (const int — minimum rank needed to execute)
│
├── GradeTooHighException
└── GradeTooLowException
```

**Why two grade thresholds?** Signing a form = approving it exists. Executing a form = doing the action. Some forms need a high-ranking bureaucrat to approve but anyone can carry out the action, or vice versa.

### Form constructor

```cpp
Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
    : name(name), isSigned(false), gradeToSign(gradeToSign),
      gradeToExecute(gradeToExecute) {
  if (gradeToSign < 1 || gradeToExecute < 1)
    throw GradeTooHighException();
  if (gradeToSign > 150 || gradeToExecute > 150)
    throw GradeTooLowException();
}
```

Same logic as Bureaucrat — invalid grades throw immediately. `isSigned` starts as `false` always.

### beSigned — the key method

```cpp
void Form::beSigned(const Bureaucrat& bureaucrat) {
  if (bureaucrat.getGrade() > this->gradeToSign)
    throw GradeTooLowException();
  this->isSigned = true;
}
```

**The logic:** `bureaucrat.getGrade() > this->gradeToSign` means "the bureaucrat's rank number is LARGER than what's required" = the bureaucrat is LESS powerful than needed.

Example: Form needs grade 50 to sign. Bureaucrat has grade 80.  
`80 > 50` → true → throw. Grade 80 is less powerful than grade 50.

Example: Form needs grade 50. Bureaucrat has grade 1.  
`1 > 50` → false → sign succeeds.

**Why throw `GradeTooLowException` from Form, not Bureaucrat?**  
Because it's the *form* reporting that the bureaucrat is not ranked highly enough — it's a Form-level problem.

### signForm — where everything connects

```cpp
// In Bureaucrat.cpp (ex01):
void Bureaucrat::signForm(Form& form) {
  try {
    form.beSigned(*this);  // *this = "the bureaucrat itself"
    std::cout << this->name << " signed " << form.getName() << std::endl;
  } catch (std::exception& e) {
    std::cout << this->name << " couldn't sign " << form.getName()
              << " because " << e.what() << std::endl;
  }
}
```

**Flow when signing SUCCEEDS:**
1. `signForm` is called on the bureaucrat
2. It calls `form.beSigned(*this)` — passes itself to the form
3. Form checks: bureaucrat grade <= gradeToSign? Yes → sets `isSigned = true`
4. No exception → falls through to the success print

**Flow when signing FAILS:**
1. Same start
2. Form checks: bureaucrat grade > gradeToSign? Yes → `throw GradeTooLowException()`
3. Exception unwinds back into `signForm`'s catch block
4. Prints "couldn't sign ... because Form grade too low"

**Q: Why does signForm catch the exception instead of letting it propagate?**  
A: The subject says to print a readable message. If we let it propagate, main() would have to handle it — messier. Catching it here gives a clean "X couldn't sign Y because Z" message.

---

## Exercise 02 — AForm (Abstract) + Concrete Forms

### The key design change: Form becomes AForm (Abstract)

```cpp
// AForm.hpp
virtual void execute(Bureaucrat const& executor) const = 0;
//                                                    ^^^
//                                      Pure virtual — no body here
//                                      AForm CANNOT be instantiated
```

`= 0` makes `execute` a **pure virtual function**. This means:
- You cannot create an `AForm` object directly
- Any class inheriting from AForm MUST implement `execute()`
- You CAN have `AForm*` pointers and `AForm&` references that point to concrete forms

### The three concrete forms

| Form | Sign grade | Execute grade | What it does |
|------|-----------|--------------|--------------|
| ShrubberyCreationForm | 145 | 137 | Creates `<target>_shrubbery` file with ASCII trees |
| RobotomyRequestForm | 72 | 45 | Prints drill noises, 50% chance of success |
| PresidentialPardonForm | 25 | 5 | Prints that target was pardoned by Zaphod Beeblebrox |

### checkExecutionRequirements — the elegant central check

```cpp
// In AForm.cpp:
void AForm::checkExecutionRequirements(const Bureaucrat& executor) const {
  if (!this->isSigned)
    throw NotSignedException();
  if (executor.getGrade() > this->gradeToExecute)
    throw GradeTooLowException();
}
```

**Q: Why put this in the base class instead of each concrete class?**  
A: DRY (Don't Repeat Yourself). All three forms need the same checks. One method in the base = one place to fix if something changes. The subject hints at this: "one way is more elegant than the other."

### How a concrete form uses it

```cpp
// In ShrubberyCreationForm.cpp:
void ShrubberyCreationForm::execute(Bureaucrat const& executor) const {
  this->checkExecutionRequirements(executor);  // <-- base class does the guard work
  // ... actual work below
  std::ofstream outfile(filename.c_str());
  outfile << "       _-_" << std::endl;
  // ... more tree art
}
```

**If the check fails:** `checkExecutionRequirements` throws → `execute` stops → exception propagates up to `executeForm` → caught there.

**If the check passes:** method continues to the actual work.

### NotSignedException — the new exception

```cpp
// In AForm.hpp:
class NotSignedException : public std::exception {
  public:
    const char* what() const throw();
};

// In AForm.cpp:
const char* AForm::NotSignedException::what() const throw() {
  return "Form is not signed";
}
```

This is thrown when someone tries to execute a form that hasn't been signed yet. The Presidential Pardon test in main.cpp demonstrates this exactly.

### executeForm — the new Bureaucrat method

```cpp
void Bureaucrat::executeForm(AForm const& form) const {
  try {
    form.execute(*this);  // virtual dispatch → calls the right concrete execute()
    std::cout << this->name << " executed " << form.getName() << std::endl;
  } catch (std::exception& e) {
    std::cout << this->name << " couldn't execute " << form.getName()
              << " because " << e.what() << std::endl;
  }
}
```

**Virtual dispatch in action:** `form.execute(*this)` — even though `form` is an `AForm&`, C++ looks at the actual runtime type and calls the right `execute()`. If `form` is really a `ShrubberyCreationForm`, it calls `ShrubberyCreationForm::execute()`.

### ShrubberyCreationForm — file I/O

```cpp
void ShrubberyCreationForm::execute(Bureaucrat const& executor) const {
  this->checkExecutionRequirements(executor);

  std::string filename = this->target + "_shrubbery";  // e.g. "Garden_shrubbery"
  std::ofstream outfile(filename.c_str());  // .c_str() because C++98 needs char*

  if (!outfile.is_open()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return;
  }

  outfile << "       _-_" << std::endl;
  // ... ASCII tree written to file
  outfile.close();
}
```

**Q: What is `.c_str()`?**  
A: `std::string` is a C++ object. `std::ofstream` in C++98 only accepts `const char*` (C-style string). `.c_str()` converts the C++ string to a C-style pointer.

### RobotomyRequestForm — the static seeded random

```cpp
static bool seeded = false;
if (!seeded) {
  std::srand(std::time(NULL));
  seeded = true;
}

if (std::rand() % 2 == 0) {
  std::cout << this->target << " has been robotomized successfully!" << std::endl;
} else {
  std::cout << "Robotomy on " << this->target << " failed." << std::endl;
}
```

**Q: Why `static bool seeded`?**  
A: `static` inside a function means the variable persists across calls — it's only initialized once in the whole program. This ensures `srand()` is called only once. Calling `srand()` multiple times resets the random sequence, which is bad.

**Q: Why `std::time(NULL)`?**  
A: Gives the current timestamp as a seed. Different each second → different random sequence each run.

**Q: What does `rand() % 2 == 0` do?**  
A: `rand()` returns a random integer. `% 2` gives either 0 or 1. Each has a 50% chance. So this is a fair coin flip.

---

## The Orthodox Canonical Form — Why It Matters

Every class (except exception classes) must have exactly these four:

```cpp
class Foo {
  Foo();                         // 1. Default constructor
  Foo(const Foo& other);         // 2. Copy constructor
  Foo& operator=(const Foo& o); // 3. Copy assignment operator
  ~Foo();                        // 4. Destructor
};
```

**Q: Why are exception classes exempt?**  
The subject says so explicitly: "exception classes do not have to be designed in Orthodox Canonical Form." They're simple, small, throw-once-and-die objects.

**The const string problem in assignment:**

```cpp
// Bureaucrat::operator=
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
  if (this != &other)
    this->grade = other.grade;  // Only copy grade, NOT name
  return *this;
}
```

**Q: Why don't you copy `name`?**  
A: Because `name` is `const std::string`. You cannot assign to a `const` member after construction. Only `grade` can change.

**Q: What is `if (this != &other)`?**  
A: Self-assignment guard. If you write `b1 = b1`, without this check you'd overwrite data you're reading from. The `&` takes the address — comparing pointers to see if it's the same object.

---

## Exception Inheritance Chain — The Full Picture

```
std::exception          (standard library — the root of all exceptions)
    │
    ├── Bureaucrat::GradeTooHighException
    ├── Bureaucrat::GradeTooLowException
    │
    ├── Form::GradeTooHighException
    ├── Form::GradeTooLowException
    │
    ├── AForm::GradeTooHighException
    ├── AForm::GradeTooLowException
    └── AForm::NotSignedException
```

**Why this matters for catch:**

```cpp
catch (Bureaucrat::GradeTooHighException& e) { }  // catches ONLY this type
catch (std::exception& e) { }                      // catches ANYTHING above

// Order matters: specific catches BEFORE generic
try { ... }
catch (Bureaucrat::GradeTooHighException& e) { /* specific */ }
catch (std::exception& e) { /* fallback */ }
```

If you put `catch(std::exception&)` first, it catches everything — the specific catches below it never run.

---

## Catch by Reference — Why It Matters

```cpp
// CORRECT — catch by const reference
catch (std::exception& e) {
  std::cout << e.what();  // calls the DERIVED what() via virtual dispatch
}

// WRONG — catch by value (SLICING)
catch (std::exception e) {
  std::cout << e.what();  // calls std::exception::what() — loses your message!
}
```

**Object slicing:** When you catch by value, C++ copies the exception into a `std::exception` object. The `GradeTooHighException` parts are sliced off. `what()` is now the base class version — returns nothing useful.

Catching by `&` (reference) keeps the original object intact. `what()` is virtual so it still calls the derived version that returns your message.

---

## Forward Declaration — The Include Dance

```cpp
// In Form.hpp (ex01):
class Bureaucrat;  // <-- forward declaration

class Form {
  void beSigned(const Bureaucrat& bureaucrat);  // just a reference — OK
};
```

**Q: Why not `#include "Bureaucrat.hpp"` directly in Form.hpp?**  
A: Bureaucrat.hpp already includes Form.hpp (because Bureaucrat uses Form). If Form.hpp also includes Bureaucrat.hpp → circular dependency → compiler explodes.

A forward declaration says "this class exists, trust me" without needing the full definition. It works when you only use **references or pointers** to that class. The actual `#include` goes in the `.cpp` file where you need the full definition.

---

## Common Evaluator Questions — Your Answers

**Q: What is an exception?**  
A: A mechanism for signaling errors that can't be handled through normal return values. When something goes wrong, you `throw` an object. The runtime searches up the call stack for a matching `catch` block.

**Q: What happens when a constructor throws?**  
A: The object is never created. Its destructor will NOT be called. Any members that were fully constructed WILL have their destructors called. The exception propagates to the caller.

**Q: Why catch by reference?**  
A: To avoid object slicing. Catching by value copies the exception and loses the derived class information. Catching by reference preserves the original type and virtual dispatch works correctly on `what()`.

**Q: What does `what() const throw()` mean?**  
A: `what()` is the method name (inherited from `std::exception`). `const` means it doesn't modify the exception. `throw()` is the C++98 empty exception specification — it promises this function won't throw.

**Q: What is a pure virtual function?**  
A: A function declared with `= 0`. The base class has no implementation. Any concrete derived class MUST implement it. The base class cannot be instantiated directly.

**Q: Why is AForm abstract?**  
A: Because "a form" in isolation doesn't mean anything — you can't execute a generic form. You need a specific type of form. Making it abstract forces you to always use a concrete type (Shrubbery, Robotomy, Presidential) while still being able to reference them through `AForm&` or `AForm*`.

**Q: Why does `grade--` in incrementGrade make the bureaucrat more powerful?**  
A: Grade 1 is the highest power. Grade 150 is the lowest. Lower number = more powerful. Decrementing the integer promotes the bureaucrat.

**Q: What is `*this` in `form.beSigned(*this)`?**  
A: `this` is a pointer to the current object. `*this` dereferences it — gives you the actual Bureaucrat object. The method expects a `const Bureaucrat&` (reference), so we pass the dereferenced object.

**Q: Why can't you copy `name` in the assignment operator?**  
A: `name` is `const std::string`. Constants cannot be reassigned after initialization. Only mutable members (like `grade`) can be copied in `operator=`.

**Q: What is `std::exception`?**  
A: The standard base class for all exceptions in C++. Defined in `<exception>`. Has a virtual `what()` method that returns a C-string describing the error.

**Q: What is virtual dispatch?**  
A: When you call a virtual function through a base class reference/pointer, C++ looks at the actual runtime type of the object and calls that class's implementation — not the base class's. This is how `form.execute(*this)` calls `ShrubberyCreationForm::execute()` even though `form` is typed as `AForm&`.

---

## Quick Mental Walkthrough — ex02 main.cpp

```
1. boss(grade 1), midTier(grade 50), intern(grade 150) — all created fine

2. ShrubberyCreationForm shrub("Garden")  ← sign:145, exec:137
   intern.signForm(shrub)     → grade 150 > 145 → FAIL: "Form grade too low"
   midTier.signForm(shrub)    → grade 50 <= 145 → SUCCESS: isSigned = true
   intern.executeForm(shrub)  → grade 150 > 137 → FAIL: "Form grade too low"
   midTier.executeForm(shrub) → grade 50 <= 137 → SUCCESS: Garden_shrubbery file created

3. RobotomyRequestForm robo("Bender")  ← sign:72, exec:45
   midTier.signForm(robo)     → grade 50 <= 72  → SUCCESS: isSigned = true
   midTier.executeForm(robo)  → grade 50 > 45   → FAIL: "Form grade too low"
   boss.executeForm(robo)     → grade 1 <= 45   → SUCCESS: 50/50 drill noise

4. PresidentialPardonForm pardon("Arthur Dent")  ← sign:25, exec:5
   boss.executeForm(pardon)   → isSigned = false → FAIL: "Form is not signed"
   boss.signForm(pardon)      → grade 1 <= 25   → SUCCESS: isSigned = true
   boss.executeForm(pardon)   → grade 1 <= 5    → SUCCESS: "pardoned by Zaphod"
```

---

## Things That Could Trip You Up

1. **Grade direction is inverted** — "too high" = the integer is too small (< 1), "too low" = the integer is too large (> 150)

2. **The assignment operator can't copy `name`** — it's `const`. Only `grade` (and `isSigned` in Form) can be copied

3. **The form exceptions come from Form/AForm**, not Bureaucrat — `GradeTooLowException` from `Form::beSigned` is `Form::GradeTooLowException`, not `Bureaucrat::GradeTooLowException`

4. **catch by reference, always** — never `catch(std::exception e)`, always `catch(std::exception& e)`

5. **Check before execute, not after** — `checkExecutionRequirements` throws before any side effects happen

6. **`isSigned` check comes before grade check** — you check if the form is signed first, then if the bureaucrat has enough grade to execute

7. **`*this` dereferences the pointer** — `this` is a pointer, `*this` is the object, which is what the methods expect as a reference parameter

---

*Good luck at your evaluation. You built this — you understand it.*
