// Factory method for classes having constructors
// that take an arbitary number of parameters

#include <iostream>
#include <memory>

class Factory
{
public:
    template<typename T, typename... Params>
    static std::unique_ptr<T> create(Params... params)
    {
        return std::make_unique<T>(params...);
    }
};

struct Foo
{
    Foo(int) {};
};

struct Bar
{
    Bar(bool, double) {};
};

int main()
{
    std::shared_ptr<Foo> foo = Factory::create<Foo>(42);
    std::shared_ptr<Bar> bar = Factory::create<Bar>(true, 42.5);
}
