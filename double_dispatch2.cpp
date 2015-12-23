// Double dispatching via function maps

#include <iostream>
#include <memory>
#include <map>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <typeinfo>

struct IAnimal
{
    virtual std::string name() = 0;
    virtual ~IAnimal() = default;
};

using FPTR = void(*)(IAnimal& first, IAnimal& second);
using PLAY_MAP = std::map<std::pair<std::type_index, std::type_index>, FPTR>;

PLAY_MAP play_map; // dispatching function map

class Cat: public IAnimal
{
public:
    std::string name() override
    {
        return "Cat";
    }
};
class Dog: public IAnimal
{
public:
    std::string name() override
    {
        return "Dog";
    }
};
class Bird: public IAnimal
{
public:
    std::string name() override
    {
        return "Bird";
    }
};

// pair-wise interactions
void cat_dog(IAnimal& cat, IAnimal& dog)
{
    std::cout << cat.name() << " plays with " << dog.name() << std::endl;
}

void cat_bird(IAnimal& cat, IAnimal& bird)
{
    std::cout << cat.name() << " plays with " << bird.name() << std::endl;
}

void dog_bird(IAnimal& dog, IAnimal& bird)
{
    std::cout << dog.name() << " plays with " << bird.name() << std::endl;
}

// assume symmetry for the other way around
void dog_cat(IAnimal& dog, IAnimal& cat)
{
    cat_dog(dog, cat); // reverse the animals
}

void bird_cat(IAnimal& bird, IAnimal& cat)
{
    cat_bird(bird, cat); // reverse the animals
}

void bird_dog(IAnimal& bird, IAnimal& dog)
{
    dog_bird(bird, dog); // reverse the animals
}

// now add the dispatching functions to the map
void populate_play_map()
{
    play_map[ {std::type_index(typeid(Cat)),  
        std::type_index(typeid(Dog))}]  = &cat_dog;
    play_map[ {std::type_index(typeid(Cat)),  
        std::type_index(typeid(Bird))}] = &cat_bird;
    play_map[ {std::type_index(typeid(Bird)), 
        std::type_index(typeid(Dog))}]  = &bird_dog;
    play_map[ {std::type_index(typeid(Dog)),  
        std::type_index(typeid(Cat))}]  = &dog_cat;
    play_map[ {std::type_index(typeid(Bird)), 
        std::type_index(typeid(Cat))}]  = &bird_cat;
    play_map[ {std::type_index(typeid(Dog)),  
        std::type_index(typeid(Bird))}] = &bird_dog;
}

// finally double dispatch
void play(IAnimal& first, IAnimal& second)
{
    auto type_idx_first = std::type_index(typeid(first));
    auto type_idx_second = std::type_index(typeid(second));

    auto found = play_map.find({type_idx_first, type_idx_second});
    if (found == play_map.end())
        throw std::runtime_error("No dispatching function in the function map!");
    play_map[found->first](first, second);
}

int main()
{
    populate_play_map();
    std::unique_ptr<IAnimal> upCat{new Cat};
    std::unique_ptr<IAnimal> upDog{new Dog};
    std::unique_ptr<IAnimal> upBird{new Bird};

    play(*upCat, *upDog);
    play(*upCat, *upBird);
    play(*upDog, *upBird);

    play(*upDog, *upCat);
    play(*upBird, *upCat);
    play(*upBird, *upDog);

    
    // this line throws, animals don't play with the same species
    try
    {
        play(*upDog, *upDog);
    }
    catch(...)
    {
        std::cerr << "No dispatching function!\n";
    }
}
