#include <iostream>
#include <exception>
#include <string>

// Simulates your exception hierarchy:
//
//   std::exception
//       └── MyBaseException   (like your GradeTooHighException)
//               └── MyFileException  (adds extra data: a filename)
//
// The point: catching by value SLICES the derived part off.
//            catching by reference preserves everything.

class MyBaseException : public std::exception {
public:
    int errorCode;
    MyBaseException(int code) : errorCode(code) {}
    ~MyBaseException() throw() {}
    const char *what() const throw() { return "BASE ERROR"; }
};

class MyFileException : public MyBaseException {
public:
    std::string filename;
    MyFileException(int code, const std::string &file)
        : MyBaseException(code), filename(file) {}
    ~MyFileException() throw() {}
    const char *what() const throw() { return "FILE ERROR"; }
};

// ── CATCH BY VALUE: slicing happens ──────────────────────

static void demo_catchByValue() {
    std::cout << "═══════════════════════════════════════" << std::endl;
    std::cout << "  CATCH BY VALUE  —  catch (Base e)" << std::endl;
    std::cout << "═══════════════════════════════════════" << std::endl;
    try {
        throw MyFileException(42, "/etc/passwd");
    } catch (MyBaseException e) {
        std::cout << "  what():      " << e.what() << std::endl;
        std::cout << "  errorCode:   " << e.errorCode << std::endl;
        std::cout << "  sizeof(e):   " << sizeof(e) << " bytes" << std::endl;
        std::cout << std::endl;
        std::cout << "  >> A COPY was made.  The MyFileException was squashed" << std::endl;
        std::cout << "  >> into a MyBaseException.  filename is GONE." << std::endl;
        std::cout << "  >> what() called the BASE version (slicing kills vtbl)." << std::endl;
    }
}

// ── CATCH BY REFERENCE: nothing lost ─────────────────────

static void demo_catchByReference() {
    std::cout << std::endl;
    std::cout << "═══════════════════════════════════════" << std::endl;
    std::cout << "  CATCH BY REFERENCE  —  catch (Base &e)" << std::endl;
    std::cout << "═══════════════════════════════════════" << std::endl;
    try {
        throw MyFileException(99, "/etc/shadow");
    } catch (MyBaseException &e) {
        std::cout << "  what():      " << e.what() << std::endl;
        std::cout << "  errorCode:   " << e.errorCode << std::endl;
        std::cout << "  sizeof(e):   " << sizeof(e) << " bytes (reference = pointer)" << std::endl;
        std::cout << std::endl;
        std::cout << "  >> e POINTS to the original MyFileException." << std::endl;
        std::cout << "  >> No copy.  No slicing.  what() dispatches correctly." << std::endl;
    }
}

// ── YOUR ACTUAL PATTERN ───────────────────────────────────

static void demo_yourCode() {
    std::cout << std::endl;
    std::cout << "═══════════════════════════════════════" << std::endl;
    std::cout << "  YOUR CODE:  catch (std::exception &e)" << std::endl;
    std::cout << "═══════════════════════════════════════" << std::endl;
    try {
        throw MyFileException(13, "data.bin");
    } catch (std::exception &e) {
        std::cout << "  e.what():    " << e.what() << std::endl;
        std::cout << std::endl;
        std::cout << "  >> Virtual dispatch STILL WORKS through a base reference." << std::endl;
        std::cout << "  >> If we caught by VALUE here, e.what() would print" << std::endl;
        std::cout << "  >> std::exception::what() — a useless default message." << std::endl;
    }
}

// ── THE ANALOGY ──────────────────────────────────────────

static void demo_analogy() {
    std::cout << std::endl;
    std::cout << "───────────────────────────────────────" << std::endl;
    std::cout << "  THE PIZZA ANALOGY" << std::endl;
    std::cout << "───────────────────────────────────────" << std::endl;
    std::cout << "  Without &:  🍕 → [letterbox] → 🫓" << std::endl;
    std::cout << "              The pizza gets squeezed through a slot." << std::endl;
    std::cout << "              Only the crust fits.  Toppings are lost." << std::endl;
    std::cout << std::endl;
    std::cout << "  With &:     🍕 ← you point at it" << std::endl;
    std::cout << "              You open the door and point at the pizza." << std::endl;
    std::cout << "              Nothing is copied.  Everything is there." << std::endl;
}

int main() {
    demo_catchByValue();
    demo_catchByReference();
    demo_yourCode();
    demo_analogy();
    return 0;
}
