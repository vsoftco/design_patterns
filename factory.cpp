// Factory design pattern

#include <iostream>
#include <memory>
#include <string>

// interface for common products that will be created by the factory
struct IFruit {
    virtual std::string get_name() const = 0;
    virtual ~IFruit() = default;
};

// concrete product
class Apple : public IFruit {
  public:
    std::string get_name() const override { return "apple"; }
};

// concrete product
class BigApple : public Apple {
  public:
    std::string get_name() const override { return "big apple"; }
};

// concrete product
class Orange : public IFruit {
  public:
    std::string get_name() const override { return "orange"; }
};

// concrete factory, deleted constructor
// creates products via static make_fruit
class FruitFactory {
  public:
    FruitFactory() = delete;

    std::unique_ptr<IFruit> static make_fruit(const std::string& fruit) {
        if (fruit == "apple")
            return std::make_unique<Apple>();
        else if (fruit == "big apple")
            return std::make_unique<BigApple>();
        else if (fruit == "orange")
            return std::make_unique<Orange>();

        return nullptr;
    }
};

int main() {
    std::unique_ptr<IFruit> fruit;

    fruit = FruitFactory::make_fruit("apple");
    if (fruit)
        std::cout << "Making: " << fruit->get_name() << '\n';
    else
        std::cout << "Sorry, we don't have " << fruit->get_name() << '\n';

    fruit = FruitFactory::make_fruit("big apple");
    if (fruit)
        std::cout << "Making: " << fruit->get_name() << '\n';
    else
        std::cout << "Sorry, we don't have " << fruit->get_name() << '\n';

    fruit = FruitFactory::make_fruit("orange");
    if (fruit)
        std::cout << "Making: " << fruit->get_name() << '\n';
    else
        std::cout << "Sorry, we don't have " << fruit->get_name() << '\n';

    fruit = FruitFactory::make_fruit("banana");
    if (fruit)
        std::cout << "Making an " << fruit->get_name() << '\n';
    else
        std::cout << "Sorry, this fruit is too exotic to make!\n";
}
