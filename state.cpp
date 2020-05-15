// State design pattern

#include <algorithm>
#include <cctype>
#include <iostream>
#include <memory>
#include <string>

// state interface
struct IState {
    virtual void write(class Type_Writter& type_writter, std::string what) = 0;
    virtual ~IState() = default;
};

// context, we model a type writter with 2 states: Caps ON and Caps OFF
// that keep switching automatically
class Type_Writter {
  protected:
    std::unique_ptr<IState> state_;

  public:
    Type_Writter(std::unique_ptr<IState> state) : state_{std::move(state)} {}
    void set_state(std::unique_ptr<IState> state) { state_ = std::move(state); }
    void write(const std::string& what) { state_->write(*this, what); }
};

// concrete states
class Caps_ON : public IState {
  public:
    void write(Type_Writter& type_writter, std::string what) override;
};

class Caps_OFF : public IState {
  public:
    void write(Type_Writter& type_writter, std::string what) override;
};

// implementation of concrete states
void Caps_ON::write(Type_Writter& type_writter, std::string what) {
    std::transform(std::begin(what), std::end(what), std::begin(what),
                   ::toupper);
    std::cout << what;
}

void Caps_OFF::write(Type_Writter& type_writter, std::string what) {
    std::transform(std::begin(what), std::end(what), std::begin(what),
                   ::tolower);
    std::cout << what;
}

int main() {
    // the context
    Type_Writter type_writter{std::make_unique<Caps_OFF>()};

    // the state machine in action
    type_writter.write("Hello ");
    type_writter.write("World!\n");

    // switch the state
    type_writter.set_state(std::make_unique<Caps_ON>());
    type_writter.write("This ");
    type_writter.write("is ");
    type_writter.write("a ");
    type_writter.write("test.\n");
}
