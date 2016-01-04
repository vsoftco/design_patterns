// Double dispatching via virtual functions

#include <iostream>
#include <string>

class Cat;
class Bird;
class Dog;

struct IAnimal
{
    virtual std::string name() const = 0;
    virtual void play(IAnimal&) = 0;
    virtual void play(Cat&) = 0;
    virtual void play(Bird&) = 0;
    virtual void play(Dog&) = 0;
    virtual ~IAnimal() = default;
};

class Cat: public IAnimal
{
public:
    std::string name() const override
    {
        return "Cat";
    }
    void play(IAnimal& animal) override
    {
        animal.play(*this);
    }
    void play(Cat&) override;
    void play(Dog&) override;
    void play(Bird&) override;
};

class Dog: public IAnimal
{
public:
    std::string name() const override
    {
        return "Dog";
    }
    void play(IAnimal& animal) override
    {
        animal.play(*this);
    }
    void play(Cat&) override;
    void play(Dog&) override;
    void play(Bird&) override;
};

class Bird: public IAnimal
{
public:
    std::string name() const override
    {
        return "Bird";
    }
    void play(IAnimal& animal) override
    {
        animal.play(*this);
    }
    void play(Cat&) override;
    void play(Dog&) override;
    void play(Bird&) override;
};

void Cat::play(Cat& cat)
{
    std::cout << name() << " plays with " << cat.name() << std::endl;
}
void Cat::play(Bird& bird)
{
    std::cout << name() << " plays with " << bird.name() << std::endl;
}
void Cat::play(Dog& dog)
{
    std::cout << name() << " plays with " << dog.name() << std::endl;
}

void Dog::play(Cat& cat)
{
    std::cout << name() << " plays with " << cat.name() << std::endl;
}
void Dog::play(Bird& bird)
{
    std::cout << name() << " plays with " << bird.name() << std::endl;
}
void Dog::play(Dog& dog)
{
    std::cout << name() << " plays with " << dog.name() << std::endl;
}

void Bird::play(Cat& cat)
{
    std::cout << name() << " plays with " << cat.name() << std::endl;
}
void Bird::play(Bird& bird)
{
    std::cout << name() << " plays with " << bird.name() << std::endl;
}
void Bird::play(Dog& dog)
{
    std::cout << name() << " plays with " << dog.name() << std::endl;
}

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