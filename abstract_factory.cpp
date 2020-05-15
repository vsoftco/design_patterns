// Abstract factory design pattern

#include <iostream>
#include <memory>

// abstract product
struct IWidget {
    virtual void draw() const = 0;
    virtual ~IWidget() = default;
};

// concrete product
class OSXButton : public IWidget {
  public:
    void draw() const override { std::cout << "\tOS X Button" << '\n'; }
};

// concrete product
class OSXWindow : public IWidget {
  public:
    void draw() const override { std::cout << "\tOS X Window" << '\n'; }
};

// concrete product
class WinButton : public IWidget {
  public:
    void draw() const override { std::cout << "\tWindows Button" << '\n'; }
};

// concrete product
class WinWindow : public IWidget {
  public:
    void draw() const override { std::cout << "\tWindows Window" << '\n'; }
};

// abstract factory
struct IFactory {
    virtual std::unique_ptr<IWidget> create_button() = 0;
    virtual std::unique_ptr<IWidget> create_window() = 0;
    virtual ~IFactory() = default;
};

// concrete factory
class OSXFactory : public IFactory {
  public:
    OSXFactory() { std::cout << "Creating the OSXFactory..." << '\n'; }
    std::unique_ptr<IWidget> create_button() {
        return std::make_unique<OSXButton>();
    }
    std::unique_ptr<IWidget> create_window() {
        return std::make_unique<OSXWindow>();
    }
    virtual ~OSXFactory() {
        std::cout << "Destroying the OSXFactory..." << '\n';
    }
};

// concrete factory
class WinFactory : public IFactory {
  public:
    WinFactory() { std::cout << "Creating the WinFactory..." << '\n'; }
    std::unique_ptr<IWidget> create_button() {
        return std::make_unique<WinButton>();
    }
    std::unique_ptr<IWidget> create_window() {
        return std::make_unique<WinWindow>();
    }
    virtual ~WinFactory() {
        std::cout << "Destroying the WinFactory..." << '\n';
    }
};

// combine Abstract factory with Strategy
class SuperFactory : public IFactory {
    std::unique_ptr<IFactory> _factory;

  public:
    explicit SuperFactory(std::unique_ptr<IFactory> factory)
        : _factory{std::move(factory)} {
        std::cout << "Creating the SuperFactory..." << '\n';
    }
    void set_factory(std::unique_ptr<IFactory> factory) {
        std::cout << "Changing the IFactory strategy" << '\n';
        _factory = std::move(factory);
    }
    std::unique_ptr<IWidget> create_button() {
        return _factory->create_button();
    }
    std::unique_ptr<IWidget> create_window() {
        return _factory->create_window();
    }
    ~SuperFactory() { std::cout << "Destroying the SuperFactory..." << '\n'; }
};

int main() {
    // Direct usage of Abstract factory pattern
    std::unique_ptr<IFactory> factory{std::make_unique<OSXFactory>()};
    factory->create_button()->draw();
    factory->create_window()->draw();
    std::cout << "--------" << '\n';

    factory = std::make_unique<WinFactory>();
    factory->create_button()->draw();
    factory->create_window()->draw();
    std::cout << "--------" << '\n';

    // Usage via the Strategy pattern
    SuperFactory super_factory(std::make_unique<OSXFactory>());
    super_factory.create_button()->draw();
    super_factory.set_factory(std::move(factory));
    super_factory.create_window()->draw();
    std::cout << "--------" << '\n';
}
