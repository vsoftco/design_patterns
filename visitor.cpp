// Visitor design pattern

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

// object hierarchy we will visit
class IObject
{
public:
    virtual void accept(class IVisitor& visitor) = 0;
    virtual ~IObject() = default;
};

class Car: public IObject
{
public:
    std::string car() const
    {
        return "Car";
    }
    void accept(IVisitor& visitor) override;
};

class Plane: public IObject
{
public:
    std::string plane() const
    {
        return "Plane";
    }
    void accept(IVisitor& visitor) override;
};

class Train: public IObject
{
public:
    std::string train() const
    {
        return "Train";
    }
    void accept(IVisitor& visitor) override;
};

// visitor hierarchy
class IVisitor
{
public:
    virtual void visit(Car& car) = 0;
    virtual void visit(Plane& plane) = 0;
    virtual void visit(Train& plane) = 0;
    virtual ~IVisitor() = default;
};

// accept the visitor(s)
void Car::accept(IVisitor& visitor)
{
    visitor.visit(*this); // double dispatching
}

void Plane::accept(IVisitor& visitor)
{
    visitor.visit(*this);
}

void Train::accept(IVisitor& visitor)
{
    visitor.visit(*this);
}

// define as many visitors as you want
// first type of visitor, implement some functionality
class VisitorOne: public IVisitor
{
    virtual void visit(Car& car) override
    {
        std::cout << "Visitor one on " << car.car() << '\n';
    }
    virtual void visit(Plane& plane) override
    {
        std::cout << "Visitor one on " << plane.plane() << '\n';
    }
    virtual void visit(Train& train) override
    {
        std::cout << "Visitor one on " << train.train() << '\n';
    }
};

// second type of visitor, different functionality
class VisitorTwo: public IVisitor
{
    virtual void visit(Car& car) override
    {
        std::cout << "Visitor two on " << car.car() << '\n';
    }
    virtual void visit(Plane& plane) override
    {
        std::cout << "Visitor two on " << plane.plane() << '\n';
    }
    virtual void visit(Train& train) override
    {
        std::cout << "Visitor two on " << train.train() << '\n';
    }
};

int main()
{
    // objects
    Car car;
    Plane plane;
    Train train;

    std::vector<std::reference_wrapper<IObject>> objects;
    objects.push_back(car);
    objects.push_back(plane);
    objects.push_back(train);

    // visitors
    VisitorOne vis_one;
    VisitorTwo vis_two;

    // first visitor
    for (auto&& elem : objects)
    {
        elem.get().accept(vis_one);
    }

    // second visitor
    for (auto && elem : objects)
    {
        elem.get().accept(vis_two);
    }
}
