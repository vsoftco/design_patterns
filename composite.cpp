// Composite design pattern

#include <iostream>
#include <memory>
#include <vector>

// basic elements interface
struct IShape
{
    virtual void add(std::shared_ptr<IShape> elem) = 0 ;
    virtual void draw() const = 0;
};

// concrete basic element (leaf)
class Circle: public IShape
{
    // this is a leaf, nothing to add
    void add(std::shared_ptr<IShape> elem) override {} 
    void draw() const override
    {
        std::cout << "Drawing a Circle\n";
    }
};

// concrete basic element (leaf)
class Square: public IShape
{
    // this is a leaf, nothing to add
    void add(std::shared_ptr<IShape>) override {}
    void draw() const override
    {
        std::cout << "Drawing a Square\n";
    }
};

// composite
class Composite: public IShape
{
    std::vector<std::shared_ptr<IShape>> collection_;
public:
    void add(std::shared_ptr<IShape> elem) override
    {
        collection_.push_back(elem);
    }
    void draw() const override
    {
        std::cout << "Composite\n";
        // delegate to the individual elements
        for (auto && elem : collection_)
        {
            elem->draw();
        }
    }
};

int main()
{
    auto circle = std::make_shared<Circle>();
    auto square = std::make_shared<Square>();

    // create a first-level composition
    auto shapes = std::make_shared<Composite>();
    shapes->add(circle);
    shapes->add(square);
    shapes->draw();

    // create a composition of 2 first level compositions
    std::cout << '\n';
    auto collection_of_shapes = std::make_shared<Composite>();
    collection_of_shapes->add(shapes);
    collection_of_shapes->add(shapes);
    collection_of_shapes->draw();
}
