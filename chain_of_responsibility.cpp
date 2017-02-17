// Chain of responsibility design pattern

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>

// handler interface
class IHandler
{
    std::shared_ptr<IHandler> next_{nullptr};
public:
    void set_next(std::shared_ptr<IHandler> handler)
    {
        next_ = handler;
    }
    std::shared_ptr<IHandler> get_next() const
    {
        return next_;
    }
    virtual void handle_request(std::size_t ammount) = 0;
    virtual ~IHandler() = default;
};

// client
class ATM
{
    std::shared_ptr<IHandler> start_;
public:
    ATM(std::shared_ptr<IHandler> start): start_{start} {}
    void set_start(std::shared_ptr<IHandler> start)
    {
        start_ = start;
    }
    void dispense(std::size_t ammount)
    {
        std::cout << "ATM withdrawal of $" << ammount << '\n';
        start_->handle_request(ammount);
    }
};

// concrete handlers
class Handle_100: public IHandler
{
    void handle_request(std::size_t ammount) override
    {
        std::size_t q = ammount / 100;
        std::size_t r = ammount % 100;

        if (q > 0)
        {
            std::cout << "Dispensing: ";
            std::cout << std::right << std::setw(10) << q << " x $100\n";
            get_next()->handle_request(r);
        }
        else
        {
            get_next()->handle_request(ammount);
        }
    }
};

struct Handle_50: public IHandler
{
    void handle_request(std::size_t ammount) override
    {
        std::size_t q = ammount / 50;
        std::size_t r = ammount % 50;

        if (q > 0)
        {
            std::cout << "Dispensing: ";
            std::cout << std::right << std::setw(10) << q << " x $50\n";
            get_next()->handle_request(r);
        }
        else
        {
            get_next()->handle_request(ammount);
        }
    }
};

struct Handle_20: public IHandler
{
    void handle_request(std::size_t ammount) override
    {
        std::size_t q = ammount / 20;
        std::size_t r = ammount % 20;

        if (q > 0)
        {
            std::cout << "Dispensing: ";
            std::cout << std::right << std::setw(10) << q << " x $20\n";
        }
        if (r > 0)
        {
            std::cout << "Dispensing change: ";
            std::cout << std::right << std::setw(3) << r << " x $1\n";
        }
    }
};

int main()
{
    // define the chain elements
    auto handle_100 = std::make_shared<Handle_100>();
    auto handle_50 = std::make_shared<Handle_50>();
    auto handle_20 = std::make_shared<Handle_20>();

    // link the chain elements
    handle_100->set_next(handle_50);
    handle_50->set_next(handle_20);

    // instantiate the ATM with the beginning of the chain
    ATM atm{handle_100};
    atm.dispense(1296);
    std::cout << '\n';

    // instantiate the ATM with $50 handler as the starting of the chain
    atm.set_start(handle_50);
    atm.dispense(443);
}
