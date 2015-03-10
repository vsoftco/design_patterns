// Strategy design pattern

#include <iostream>
#include <memory>
#include <string>

// strategy interface
struct IFlies
{
	virtual std::string fly() = 0; // the algorithm (strategy)
	virtual ~IFlies() = default;
};

// algorithm (strategy)
class Flies: public IFlies
{
public:
	std::string fly() override
	{
		return "Flying high!";
	}
};

// algorithm (strategy)
class CantFly: public IFlies
{
public:
	std::string fly() override
	{
		return "Can't fly :(";
	}
};

// we implement the algorithm (strategy) via composition
class Animal
{
private:
	std::unique_ptr<IFlies> _flying_type;
public:
	explicit Animal(std::unique_ptr<IFlies> flying_type) :
		_flying_type(std::move(flying_type)) {}

	void set_flying_ability(std::unique_ptr<IFlies> flying_type)
	{
		_flying_type = std::move(flying_type);
	}
	void try_to_fly()
	{
		std::cout << '\t' << _flying_type->fly() << std::endl;
	}
};

class Dog: public Animal
{
public:
	Dog(): Animal(std::make_unique<CantFly>()) {}
};

class Bird: public Animal
{
public:
	Bird(): Animal(std::make_unique<Flies>()) {}
};

int main()
{
	Dog dog;
	std::cout << "I'm a dog, trying to fly..." << std::endl;
	dog.try_to_fly();

	Bird bird;
	std::cout << "I'm a bird, trying to fly..." << std::endl;
	bird.try_to_fly();

	// changing the algorithm (strategy) at runtime
	std::cout << "I'm a bird, but changed my mind about flying..." << std::endl;
	bird.set_flying_ability(std::make_unique<CantFly>());
	bird.try_to_fly();
}
