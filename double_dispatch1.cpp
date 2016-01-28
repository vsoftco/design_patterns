// Double dispatching via virtual functions

#include <iostream>
#include <string>

class Cat;
class Bird;
class Dog;

struct IAnimal
{
    virtual std::string name() const = 0;
    virtual void play(const IAnimal&) const = 0;
    virtual void play(const Cat&) const  = 0;
    virtual void play(const Bird&) const = 0;
    virtual void play(const Dog&) const = 0;
    virtual ~IAnimal() = default;
};

class Cat: public IAnimal
{
public:
    std::string name() const override
    {
        return "Cat";
    }
    void play(const IAnimal& animal) const override
    {
        animal.play(*this);
    }
    void play(const Cat&) const override;
    void play(const Dog&) const override;
    void play(const Bird&) const override;
};

class Dog: public IAnimal
{
public:
    std::string name() const override
    {
        return "Dog";
    }
    void play(const IAnimal& animal) const override
    {
        animal.play(*this);
    }
    void play(const Cat&) const override;
    void play(const Dog&) const override;
    void play(const Bird&) const override;
};

class Bird: public IAnimal
{
public:
    std::string name() const override
    {
        return "Bird";
    }
    void play(const IAnimal& animal) const override
    {
        animal.play(*this);
    }
    void play(const Cat&) const override;
    void play(const Dog&) const override;
    void play(const Bird&) const override;
};

void Cat::play(const Cat& cat) const
{
    std::cout << name() << " plays with " << cat.name() << std::endl;
}
void Cat::play(const Bird& bird) const
{
    std::cout << name() << " plays with " << bird.name() << std::endl;
}
void Cat::play(const Dog& dog) const
{
    std::cout << name() << " plays with " << dog.name() << std::endl;
}

void Dog::play(const Cat& cat) const
{
    std::cout << name() << " plays with " << cat.name() << std::endl;
}
void Dog::play(const Bird& bird) const
{
    std::cout << name() << " plays with " << bird.name() << std::endl;
}
void Dog::play(const Dog& dog) const
{
    std::cout << name() << " plays with " << dog.name() << std::endl;
}

void Bird::play(const Cat& cat) const
{
    std::cout << name() << " plays with " << cat.name() << std::endl;
}
void Bird::play(const Bird& bird) const
{
    std::cout << name() << " plays with " << bird.name() << std::endl;
}
void Bird::play(const Dog& dog) const
{
    std::cout << name() << " plays with " << dog.name() << std::endl;
}

void play(const IAnimal& first, const IAnimal& second)
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
