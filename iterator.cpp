// Iterator design pattern

#include <iostream>
#include <vector>

// the iterable collection
template <typename T>
class Collection {
    std::vector<T> data_;

    // a very simplistic (private) iterator
    class Iterator {
        Collection& collection_;
        std::size_t pos_ = 0;

      public:
        Iterator(Collection& collection) : collection_{collection} {}
        bool has_next() const { return pos_ < collection_.size(); }
        void advance() { ++pos_; }
        T& get() const { return collection_.data_[pos_]; }
        void rewind() { pos_ = 0; }
    };

  public:
    Collection(std::initializer_list<T> data) : data_{data} {}
    std::size_t size() const { return data_.size(); }
    Iterator first() { return *this; }
};

int main() {
    Collection<int> collection{0, 1, 2, 3};

    // obtain an iterator to the first element
    auto iter = collection.first();

    // Java-like iteration
    while (iter.has_next()) {
        // reference to the current element
        auto& element = iter.get();

        // display it
        std::cout << element << ' ';

        // modify the current element
        element = collection.size() - 1 - element;

        iter.advance();
    }

    // display the modified elements
    std::cout << '\n';
    iter.rewind();
    for (; iter.has_next(); iter.advance()) {
        std::cout << iter.get() << ' ';
    }
    std::cout << '\n';
}
