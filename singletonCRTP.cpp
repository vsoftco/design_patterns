// Singleton pattern via CRTP (curiously recurring template pattern)
// thread safe in C++11 and later

#include <iostream>
#include <type_traits>

// generic Singleton
template <typename T>
class Singleton
{
protected:
    Singleton(const Singleton&) = delete; // to prevent CASE 3
    Singleton& operator=(const Singleton&) = delete; // to prevent CASE 4
    Singleton() noexcept = default; // to allow creation of Singleton<Foo>
    // by the derived class Foo, since otherwise the (deleted)
    // copy constructor prevents the compiler from generating
    // a default constructor;
    // declared protected to prevent CASE 5
public:
    static T& get_instance()
    noexcept(std::is_nothrow_constructible<T>::value)
    {
        static T instance;
        return instance;
    }
    // thread local instance
    static thread_local T& get_thread_local_instance()
    noexcept(std::is_nothrow_constructible<T>::value)
    {
        static T instance;
        return instance;
    }
};

// specific Singleton instance
// use const if you want a const instance returned
// make the constructor and destructor private
class Foo: public Singleton</*const*/ Foo>
{
    // so Singleton<Foo> can access the constructor and destructor of Foo
    friend class Singleton<Foo>;
    Foo() // to prevent CASE 1
    {
        std::cout << "Foo::Foo() private constructor" << std::endl;
    }
    // OK to be private, since Singleton<Foo> is a friend and can invoke it
    ~Foo() // to prevent CASE 2
    {
        std::cout << "Foo::~Foo() private destructor" << std::endl;
    }
public:
    void say_hello()
    {
        std::cout << "\t Hello from Singleton" << std::endl;
    }
};

int main()
{
    Foo& sFoo = Foo::get_instance();
    sFoo.say_hello();

    Foo& sAnotherFoo = Foo::get_instance(); // OK, get the same instance
    sAnotherFoo.say_hello();

    Foo& sYetAnotherFoo = sFoo; // still OK, get the same instance
    sYetAnotherFoo.say_hello();

    thread_local Foo& stlFoo = Foo::get_thread_local_instance(); // thread local instance
    stlFoo.say_hello();

    // CASE 1: error: 'Foo::Foo()' is private
    // Foo foo;
    // Foo* psFoo = new Foo;

    // CASE 2: error: 'Foo::~Foo()' is private
    Foo* psFoo = &Foo::get_instance(); // can get pointer
    psFoo->say_hello();
    // delete psFoo; // cannot delete it

    // CASE 3: error: use of deleted function 'Foo::Foo(const Foo&)'
    // Foo foo(sFoo);

    // CASE 4: error: use of deleted function 'Foo& Foo::operator=(const Foo&)'
    // sFoo = sAnotherFoo;

    // CASE 5: error: 'Singleton<T>::Singleton() [with T = Foo]' is protected
    // Singleton<Foo> direct_sFoo;
}
