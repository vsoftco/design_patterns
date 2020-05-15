// Template method design pattern via the Non-Virtual Interface idiom (NVI)

#include <iostream>
#include <memory>

class Base {
    virtual void f() { std::cout << "Base::f()\n"; }

  public:
    void call() {
        std::cout << "Before calling f()\n";
        f(); // run-time dispatch
        std::cout << "After calling f()\n";
    }
    virtual ~Base() = default;
};

class Derived : public Base {
    // change behaviour
    void f() override { std::cout << "Derived::f()\n"; }
};

int main() {
    std::unique_ptr<Base> pBase{std::make_unique<Derived>()};
    pBase->call();
}
