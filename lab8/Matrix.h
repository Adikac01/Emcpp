#pragma include once

#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

template <typename T, size_t N, size_t M>
class Matrix{

	T data[N * M];

public:
	constexpr size_t numberOfRows() const noexcept{ return N; }
	constexpr size_t numberOfColumns() const noexcept { return M; }

	Matrix(int nrows = N, int ncols = M) noexcept {
		std::fill_n(data, N * M, T{});
	}
	Matrix(const std::initializer_list<std::initializer_list<T>> &list) noexcept{
		T *p = data;
		for (const auto &row : list)
		{
			T *p2 = std::copy(row.begin(), row.end(), p);
			std::fill(p2, p += M, T{});
		}
	}

	Matrix(const Matrix &m) noexcept {
		std::copy_n(m.data, N * M, data);
	}

	Matrix &operator=(const Matrix &m) noexcept {
		if (&m != this)
		{	
			std::copy_n(m.data, N * M, data);
		}
		return *this;
	}

	const T &operator()(size_t i, size_t j) const noexcept {
		return data[(i - 1) * M + j - 1];
	}

	T& operator()(size_t i, size_t j) noexcept {
        return data[(i - 1) * M + j - 1];
    }

	friend Matrix operator+(const Matrix &a, const Matrix &b) noexcept {
		Matrix r;
		for (size_t i = 1; i <= N; ++i)
		{
			for (size_t j = 1; j <= M; ++j)
			{
				r(i, j) = a(i, j) + b(i, j);
			}
		}
		return r;
	}

	class iterator {
		T* ptr;

	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		iterator(T* p) : ptr(p) {}

		iterator& operator++() {
			++ptr;
			return *this;
		}

		iterator operator++(int){
			iterator temp = *this;
			++ptr;
		}
		
		T& operator*() const {
			return *ptr;
		}

		T* operator->() const {
			return ptr;
		}

		bool operator==(const iterator& other) const{
			return ptr == other.ptr;
		}

		bool operator!=(const iterator& other) const{
			return ptr != other.ptr;
		}
	};

	using const_iterator = const T*;

	using row_iterator = T*;

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
            ptr += M;  // Move to the next column
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



	iterator begin() noexcept {
        return iterator(data);
    }

    iterator end() noexcept {
        return iterator(data + N * M);
    }

    const_iterator begin() const noexcept {
        return data;
    }

    const_iterator end() const noexcept {
        return data + N * M;
    }

    row_iterator row_begin(size_t n) noexcept {
        return data + (n - 1) * M;
    }

    row_iterator row_end(size_t n) noexcept {
        return data + n * M;
    }

    col_iterator col_begin(size_t column) {
        return col_iterator(data + column-1, column);
    }

    col_iterator col_end(size_t column) {
        return col_iterator(data + M * N + column-1, column);
    }
};

template <typename T, size_t N, size_t M>
void printMatrix(const Matrix<T, N, M> &m, int width = 10){
	for (size_t i = 1; i <= m.numberOfRows(); ++i){
		for (size_t j = 1; j <= m.numberOfColumns(); ++j){
			if (j != 1)
				cout << " ";
			cout << setw(width) << m(i, j);
		}
		cout << endl;
	}
}
