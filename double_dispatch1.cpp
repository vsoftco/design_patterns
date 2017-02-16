// Double dispatching via virtual functions

#include <iostream>
#include <memory>
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
        animal.play(*this); // double dispatching
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
        animal.play(*this); // double dispatching
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
        animal.play(*this); // double dispatching
    }
    void play(const Cat&) const override;
    void play(const Dog&) const override;
    void play(const Bird&) const override;
};

void Cat::play(const Cat& cat) const
{
    std::cout << name() << " plays with " << cat.name() << '\n';
}
void Cat::play(const Bird& bird) const
{
    std::cout << name() << " plays with " << bird.name() << '\n';
}
void Cat::play(const Dog& dog) const
{
    std::cout << name() << " plays with " << dog.name() << '\n';
}

void Dog::play(const Cat& cat) const
{
    std::cout << name() << " plays with " << cat.name() << '\n';
}
void Dog::play(const Bird& bird) const
{
    std::cout << name() << " plays with " << bird.name() << '\n';
}
void Dog::play(const Dog& dog) const
{
    std::cout << name() << " plays with " << dog.name() << '\n';
}

void Bird::play(const Cat& cat) const
{
    std::cout << name() << " plays with " << cat.name() << '\n';
}
void Bird::play(const Bird& bird) const
{
    std::cout << name() << " plays with " << bird.name() << '\n';
}
void Bird::play(const Dog& dog) const
{
    std::cout << name() << " plays with " << dog.name() << '\n';
}

void play(const IAnimal& first, const IAnimal& second)
{
    second.play(first);
}

int main()
{
    std::unique_ptr<IAnimal> upCat{std::make_unique<Cat>()};
    std::unique_ptr<IAnimal> upDog{std::make_unique<Dog>()};
    std::unique_ptr<IAnimal> upBird{std::make_unique<Bird>()};

    play(*upCat, *upDog);
    play(*upCat, *upBird);
    play(*upDog, *upBird);

    play(*upDog, *upCat);
    play(*upBird, *upCat);
    play(*upBird, *upDog);
}
