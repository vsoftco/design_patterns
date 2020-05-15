// Method chaining design pattern

#include <iostream>
#include <string>

class Person {
    std::string name_;
    unsigned age_;

  public:
    Person() : name_{}, age_{} {}
    Person& name(std::string name) {
        name_ = std::move(name);
        return *this;
    }
    Person& age(unsigned age) {
        age_ = age;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Person& rhs) {
        return os << rhs.name_ << " " << rhs.age_;
    }
};

int main() {
    Person person;
    person.name("John").age(35);
    std::cout << person;
}
