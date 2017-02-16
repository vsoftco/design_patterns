// Command design pattern

#include <cstddef>
#include <iostream>

// device interface (receivers)
class IDevice
{
protected:
    bool is_on_ = false;
    std::size_t volume_ = 0;
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void up() = 0;
    virtual void down() = 0;
    virtual ~IDevice() = default;

    bool get_state() const
    {
        return is_on_;
    }

    std::size_t get_volume() const
    {
        return volume_;
    }
};

// command interface
class ICommand
{
protected:
    IDevice& device_;
public:
    ICommand(IDevice& device): device_{device} {}
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~ICommand() = default;
};

// devices
class TV: public IDevice
{
    void on() override
    {
        is_on_ = true;
        std::cout << "TV is ON\n";
    }

    void off() override
    {
        is_on_ = false;
        std::cout << "TV is OFF\n";
    }

    void up() override
    {
        if (volume_ < 10)
            ++volume_;
        std::cout << "Turning volume up to   " << volume_ << '\n';
    }

    void down() override
    {
        if (volume_ > 0)
            --volume_;
        std::cout << "Turning volume down to " << volume_ << '\n';
    }
};

// commands
class Turn_ON: public ICommand
{
public:
    using ICommand::ICommand;
    void execute() override
    {
        device_.on();
    }

    void undo() override
    {
        device_.off();
    }
};

class Turn_OFF: public ICommand
{
public:
    using ICommand::ICommand;
    void execute() override
    {
        device_.off();
    }

    void undo() override
    {
        device_.on();
    }
};

class Turn_UP: public ICommand
{
public:
    using ICommand::ICommand;
    void execute() override
    {
        device_.up();
    }

    void undo() override
    {
        device_.down();
    }
};

class Turn_DOWN: public ICommand
{
public:
    using ICommand::ICommand;
    void execute() override
    {
        device_.down();
    }

    void undo() override
    {
        device_.up();
    }
};

int main()
{
    TV tv; // a concrete device

    // some commands
    Turn_ON turn_on(tv);
    Turn_OFF turn_off(tv);
    Turn_UP turn_up(tv);
    Turn_DOWN turn_down(tv);

    // execute/undo the commands
    turn_on.execute(); // execute
    turn_off.execute();
    turn_off.undo();   // undo
    
    turn_up.execute();
    turn_up.execute();
    turn_down.execute();
    turn_up.undo();
    turn_up.undo(); // the volume cannot be less than zero

    for (std::size_t i =  0; i < 12; ++i)
        turn_up.execute(); // the volume cannot be greater than 10

    turn_off.execute();

    std::cout << "TV in ON? " << std::boolalpha << tv.get_state() << '\n';
    std::cout << "Final volume: " << tv.get_volume() << '\n';
}
