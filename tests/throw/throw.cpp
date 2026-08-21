struct demo {
  demo() {}
  // In C++98, move constructors don't exist
  // Only copy constructor matters
private:
  demo(const demo &); // private = inaccessible copy constructor
};

int main() {
  throw demo(); // ERROR: copy constructor is inaccessible
  return 0;
}
