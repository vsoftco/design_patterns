// The pointer-to-implementation (PIMPL) idiom

#ifndef BOOK_H_
#define BOOK_H_

#include <memory>
#include <string>

class Book {
  public:
    // interface
    Book(const std::string& title, double price);
    ~Book(); // need to define it AFTER the definition of Book::BookImpl
    void print();

  private:
    struct BookImpl;
    std::unique_ptr<BookImpl> upBookImpl;
};

#endif // BOOK_H_