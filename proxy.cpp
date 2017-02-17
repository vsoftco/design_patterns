// Proxy design pattern

#include <iostream>
#include <memory>

// car interface
struct ICar
{
    virtual void drive() const = 0;
    virtual ~ICar() = default;
};

// concrete car
class Car: public ICar
{
    void drive() const override
    {
        std::cout << "Driving a car!\n";
    }
};

// proxy to a car, additional checks
class Car_Proxy: public ICar
{
    std::unique_ptr<ICar> car_{std::make_unique<Car>()};
    unsigned age_;
public:
    Car_Proxy(unsigned age): age_{age} {}
    void drive() const override
    {
        if (age_ < 18)
        {
            std::cout << "You cannot drive a car yet!\n";
        }
        else
        {
            car_->drive();
        }
    }
};

int main()
{
    Car_Proxy underage_driver(17);
    underage_driver.drive();

    Car_Proxy driver(18);
    driver.drive();
}
