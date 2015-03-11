// Decorator design pattern

#include <iostream>
#include <memory>

// interface for Window and Decorator
struct IWindow
{
    virtual void draw() = 0;
    virtual ~IWindow() = default;
};

// concrete Window
class Window: public IWindow
{
public:
    void draw() override
    {
        std::cout << "Basic Window" << std::endl;
    }
};

// basic Decorator
class Decorator: public IWindow
{
    std::unique_ptr<IWindow> _window; // has a 
public:
    explicit Decorator(std::unique_ptr<IWindow> window): _window(std::move(window)) {}
    void draw() override
    {
        _window->draw(); // delegate responsability
    }
};

// add borders
class BorderDecorator: public Decorator
{
public:
    explicit BorderDecorator(std::unique_ptr<IWindow> window):
        Decorator(std::move(window)) {}
    void draw() override
    {
        Decorator::draw();
        std::cout << "\twith Border" << std::endl;
    }
};

// add scrollbars
class ScrollBarDecorator: public Decorator
{
public:
    explicit ScrollBarDecorator(std::unique_ptr<IWindow> window):
        Decorator(std::move(window)) {}
    void draw() override
    {
        Decorator::draw();
        std::cout << "\twith ScrollBar" << std::endl;
    }
};

int main()
{
    std::unique_ptr<IWindow> decorated_window =
        std::make_unique<BorderDecorator>(
            std::make_unique<BorderDecorator>(
                std::make_unique<ScrollBarDecorator>(
                    std::make_unique<Window>()
                )
            )
        );
    decorated_window->draw();
}
