// Facade design pattern

#include <iostream>

// complex systems
class Engine
{
public:
    void start() const
    {
        std::cout << "Starting the engine.\n";
    }
    void stop() const
    {
        std::cout << "Stopping the engine.\n";
    }
};

class Hand_Brake
{
public:
    void pull() const
    {
        std::cout << "Pulling the hand brake.\n";
    }
    void release() const
    {
        std::cout << "Releasing the hand brake.\n";
    }
};

class Gear_Box
{
public:
    void park() const
    {
        std::cout << "Setting the gearbox to PARK.\n";
    }
    void drive() const
    {
        std::cout << "Setting the gearbox to DRIVE.\n";
    }
    void reverse() const
    {
        std::cout << "Setting the gearbox to REVERSE.\n";
    }
    void neutral() const
    {
        std::cout << "Setting the gearbox to NEUTRAL.\n";
    }
};

// facade interface
struct IFacade
{
    virtual void start() const = 0;
    virtual void stop() const = 0;
    virtual ~IFacade() = default;
};

// concrete facades
class Car_Facade: public IFacade
{
    Engine engine_{};
    Hand_Brake hand_brake_{};
    Gear_Box gear_box_{};
public:
    void start() const
    {
        std::cout << "STARTING THE CAR\n";
        engine_.start();
        hand_brake_.release();
        gear_box_.drive();
        std::cout << '\n';
    }
    void stop() const
    {
        std::cout << "STOPPING THE CAR\n";
        gear_box_.park();
        hand_brake_.pull();
        engine_.stop();
        std::cout << '\n';
    }
};

class Scooter_Facade: public IFacade
{
    Engine engine_{};
public:
    void start() const
    {
        std::cout << "STARTING THE SCOOTER\n";
        engine_.start();
        std::cout << '\n';
    }
    void stop() const
    {
        std::cout << "STOPPING THE SCOOTER\n";
        engine_.stop();
        std::cout << '\n';
    }
};

int main()
{
    Car_Facade car_facade;
    Scooter_Facade scooter_facade;

    car_facade.start();
    car_facade.stop();

    scooter_facade.start();
    scooter_facade.stop();
}
