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
    std::shared_ptr<IState> _state;
public:
    Context(std::shared_ptr<IState> state = nullptr): _state{state} {}
    void set_state(std::shared_ptr<IState> state)
    {
        _state = state;
    }

    std::shared_ptr<IState> get_state()
    {
        return _state;
    }
};

// concrete states
class ON: public IState, public std::enable_shared_from_this<ON>
{
public:
    void do_action(Context& context) override
    {
        context.set_state(shared_from_this());
        std::cout << "The state is ON\n";
    }
};

class OFF: public IState, public std::enable_shared_from_this<OFF>
{
public:
    void do_action(Context& context) override
    {
        context.set_state(shared_from_this());
        std::cout << "The state is OFF\n";
    }
};

int main()
{
    // context
    Context context;

    // states
    auto on_state = std::make_shared<ON>();
    auto off_state = std::make_shared<OFF>();

    on_state->do_action(context);
    off_state->do_action(context);
    off_state->do_action(context);
}
