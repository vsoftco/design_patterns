// The pointer-to-implementation (PIMPL) idiom

#include <iostream>
#include "book.h"

// BEGIN private implementation details
struct Book::BookImpl {
    BookImpl(const std::string& title, double price)
        : title(title), price(price) {}

    // can add more members without the need for clients of Book to recompile
    std::string title;
    double price;
};
// END private implementation details

// BEGIN Book implementation
Book::Book(const std::string& title, double price)
    : upBookImpl{std::make_unique<BookImpl>(title, price)} {}
Book::~Book() = default; // need the destructor here for unique_ptr

void Book::print() {
    std::cout << "Title: " << upBookImpl->title << '\n';
    std::cout << "Price: " << upBookImpl->price << '\n';
}
// END Book implementation
