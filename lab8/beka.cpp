#include <iostream>
#include <iomanip>
#include <initializer_list>
#include <vector>

template <typename T, size_t M, size_t N>
class Matrix {
public:
    // Type aliases
    using iterator = T*;
    using const_iterator = const T*;

    // Constructor
    Matrix(const std::initializer_list<std::initializer_list<T>>& init) {
        size_t row = 0;
        for (const auto& row_list : init) {
            size_t column = 0;
            for (const auto& value : row_list) {
                data[row * N + column] = value;
                column++;
            }
            row++;
        }
    }

    // Column iterator
    class col_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        col_iterator(pointer ptr, size_t column)
            : ptr(ptr), column(column) {}

        col_iterator& operator++() {
            ptr += N;  // Move to the next column
            return *this;
        }

        col_iterator operator++(int) {
            col_iterator prev = *this;
            ++(*this);
            return prev;
        }

        bool operator==(const col_iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const col_iterator& other) const {
            return !(*this == other);
        }

        reference operator*() const {
            return *ptr;
        }

        pointer operator->() const {
            return ptr;
        }

    private:
        pointer ptr;
        size_t column;
    };

    col_iterator col_begin(size_t column) {
        return col_iterator(data + column - 1, column);
    }

    col_iterator col_end(size_t column) {
        return col_iterator(data + M * N + column - 1, column);
    }

private:
    T data[M * N];
};

int main() {
    using DMatrix = Matrix<double, 3, 4>;
    DMatrix m({ {1, 2, 3, 4},
                {5, 6, 7, 8},
                {9, 10, 11, 12} });

    // Print columns
    for (DMatrix::col_iterator it = m.col_begin(3); it != m.col_end(3); ++it) {
        std::cout << std::setw(6) << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}