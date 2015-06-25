// Double dispatching via virtual functions

#include <iostream>

class Cat;
class Bird;
class Dog;

struct IAnimal
{
    virtual void play(IAnimal&) = 0;
    virtual void play(Cat&) = 0;
    virtual void play(Bird&) = 0;
    virtual void play(Dog&) = 0;
    virtual ~IAnimal() = default;
};

class Dog: public IAnimal
{
public:
    void play(IAnimal& animal) override
    {
        animal.play(*this);
    }
    void play(Cat&) override
    {
        std::cout << "Dog plays with Cat" << std::endl;
    }
    void play(Bird&) override
    {
        std::cout << "Dog plays with Bird" << std::endl;
    }
    void play(Dog&) override
    {
        std::cout << "Dog plays with Dog" << std::endl;
    }
};

class Cat: public IAnimal
{
public:
    void play(IAnimal& animal) override
    {
        animal.play(*this);
    }
    void play(Cat&) override
    {
        std::cout << "Cat plays with Cat" << std::endl;
    }
    void play(Bird&) override
    {
        std::cout << "Cat plays with Bird" << std::endl;
    }
    void play(Dog&) override
    {
        std::cout << "Cat plays with Dog" << std::endl;
    }
};

class Bird: public IAnimal
{
public:
    void play(IAnimal& animal) override
    {
        animal.play(*this);
    }
    void play(Cat&) override
    {
        std::cout << "Bird plays with Cat" << std::endl;
    }
    void play(Bird&) override
    {
        std::cout << "Bird plays with Bird" << std::endl;
    }
    void play(Dog&) override
    {
        std::cout << "Bird plays with Dog" << std::endl;
};

void play(IAnimal& first, IAnimal& second)
{
    second.play(first);
}

int main()
{
    Cat cat;
    Dog dog;
    Bird bird;

    play(cat, dog);
    play(dog, cat);
    play(bird, cat);
}