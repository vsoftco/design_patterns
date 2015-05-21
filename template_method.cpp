// Template method design pattern via the Non-Virtual Interface idiom (NVI)

#include <iostream>
#include <memory>

class Base
{
    virtual void f() {std::cout << "Base::f()" << std::endl;}
public:
    void call()
    {
        std::cout << "Before calling f()" << std::endl;
        f(); // run-time dispatch
        std::cout << "After calling f()" << std::endl;
    }
    virtual ~Base() = default;
};

class Derived: public Base
{
    // change behaviour
    void f() override {std::cout << "Derived::f()" << std::endl;}
};

int main()
{
    auto pBase = std::make_unique<Derived>();
    pBase -> call();
}
