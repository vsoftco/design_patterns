// State design pattern

#include <iostream>
#include <memory>

// state interface
struct IState
{
    virtual void do_action(class Context&) = 0;
};

// concrete context
class Context
{
protected:
    std::shared_ptr<IState> state_;
public:
    Context(std::shared_ptr<IState> state = nullptr): state_{state} {}
    void setstate_(std::shared_ptr<IState> state)
    {
        state_ = state;
    }

    std::shared_ptr<IState> getstate_()
    {
        return state_;
    }
};

// concrete states
class ON: public IState, public std::enable_shared_from_this<ON>
{
public:
    void do_action(Context& context) override
    {
        context.setstate_(shared_from_this());
        std::cout << "The state is ON\n";
    }
};

class OFF: public IState, public std::enable_shared_from_this<OFF>
{
public:
    void do_action(Context& context) override
    {
        context.setstate_(shared_from_this());
        std::cout << "The state is OFF\n";
    }
};

int main()
{
    // context
    Context context;

    // states
    auto onstate_ = std::make_shared<ON>();
    auto offstate_ = std::make_shared<OFF>();

    onstate_->do_action(context);
    offstate_->do_action(context);
    offstate_->do_action(context);
}
