// Decorator design pattern

#include <iostream>
#include <memory>

// interface for Window and Decorator
struct IWindow
{
    virtual void draw() const = 0;
    virtual ~IWindow() = default;
};

// concrete Window
class Window: public IWindow
{
public:
    void draw() const override
    {
        std::cout << "Basic Window\n";
    }
};

// fancy Window
class FancyWindow: public Window
{
public:
    void draw() const override
    {
        std::cout << "Fancy Window\n";
    }
};

// basic Decorator
class Decorator: public IWindow
{
    std::unique_ptr<IWindow> _window; // has a
public:
    explicit Decorator(std::unique_ptr<IWindow> window):
        _window{std::move(window)} {}
    void draw() const override
    {
        _window->draw(); // delegate responsibility
    }
};

// add borders
class BorderDecorator: public Decorator
{
public:
    explicit BorderDecorator(std::unique_ptr<IWindow> window):
        Decorator(std::move(window)) {}
    void draw() const override
    {
        Decorator::draw();
        std::cout << "\twith Border\n";
    }
};

// add scrollbars
class ScrollBarDecorator: public Decorator
{
public:
    explicit ScrollBarDecorator(std::unique_ptr<IWindow> window):
        Decorator(std::move(window)) {}
    void draw() const override
    {
        Decorator::draw();
        std::cout << "\twith ScrollBar\n";
    }
};

int main()
{
    // decorate a basic Window
    std::unique_ptr<IWindow> decorated_window =
        std::make_unique<BorderDecorator>(
            std::make_unique<BorderDecorator>(
                std::make_unique<ScrollBarDecorator>(
                    std::make_unique<Window>()
                )
            )
        );
    // display it
    decorated_window->draw();

    // decorate a FancyWindow
    std::unique_ptr<IWindow> decorated_fancy_window =
        std::make_unique<BorderDecorator>(
            std::make_unique<BorderDecorator>(
                std::make_unique<ScrollBarDecorator>(
                    std::make_unique<FancyWindow>()
                )
            )
        );
    // display it
    decorated_fancy_window->draw();

    // a basically decorated window
    std::unique_ptr<IWindow> basic_decorated_window =
        std::make_unique<Decorator>(
            std::make_unique<Window>()
        );
    // display it
    basic_decorated_window->draw();
}
