// The pointer-to-implementation (PIMPL) idiom

// compile with g++ -std=c++14 book.cpp main.cpp -opimpl

#include "book.h"

int main() {
    Book book("Robinson Crusoe", 10.99);
    book.print();
}
