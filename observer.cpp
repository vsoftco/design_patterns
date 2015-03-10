// Observer design pattern

#include <cstddef>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

// observer interface
struct IObserver 
{
    virtual void notify() = 0;
    virtual ~IObserver() = default;
};

// concrete observer
class Observer: public IObserver 
{
    std::size_t _ID;
public:
    explicit Observer(std::size_t ID): _ID(ID) {}
    void notify() override
    {
        std::cout << "\tObserver " << _ID << " notified!" << std::endl;
    }
    std::size_t ID()
    {
        return _ID;
    }
};

// subject interface
struct ISubject 
{
    virtual void registerObserver(std::shared_ptr<Observer> spo) = 0;
    virtual void unregisterObserver(std::shared_ptr<Observer> spo) = 0;
    virtual void notifyObservers() = 0;
    virtual ~ISubject() = default;
};

// concrete subject
class Subject: public ISubject 
{
    std::map<std::size_t, std::shared_ptr<Observer>> _observers{};
public:
    void registerObserver(std::shared_ptr<Observer> spo) override
    {
        _observers[spo->ID()] = spo;
    }
    void unregisterObserver(std::shared_ptr<Observer> spo) override
    {
        _observers.erase(spo->ID());
    }
    void notifyObservers() override
    {
        for (auto& elem : _observers)
            elem.second->notify();
    }
};

int main()
{
    // 1 subject
    Subject subject;

    // N observers
    std::size_t N = 4;
    std::vector<std::shared_ptr<Observer>> vobs;
    for (std::size_t i = 0; i < N; ++i)
        vobs.push_back(std::make_shared<Observer>(i));

    // register all of them
    std::cout << "Registering all " << N << " Observers..." << std::endl;
    for (std::size_t i = 0; i < vobs.size(); ++i)
        subject.registerObserver(vobs[i]);

    // notify
    std::cout << "Notifying all " << N << " Observers..." << std::endl;
              subject.notifyObservers();

    // un-register Observers 1 and 2
    std::cout << "Un-registering Observer 1 and Observer 2..." << std::endl;
    subject.unregisterObserver(vobs[1]);
    subject.unregisterObserver(vobs[2]);

    // notify
    std::cout << "Notifying remaining Observers:" << std::endl;
    subject.notifyObservers();
}