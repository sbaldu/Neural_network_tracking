
#include <concepts>
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

using namespace boost::numeric::ublas;

/* #include "Matrix.hpp" */

template <typename T>
using Matrix = matrix<T>;

template <typename T, typename F=row_major>
matrix<T, F> makeMatrix(std::size_t m, std::size_t n, const std::vector<T> & v) {
    if (m*n!=v.size()) {
        ; // Handle this case
    }

    unbounded_array<T> storage(m*n);
    std::copy(v.begin(), v.end(), storage.begin());
    return matrix<T>(m, n, storage);
}

template <typename T>
std::vector<T> operator*(const Matrix<T>& m, const std::vector<T>& vec) {
  size_t N{m.size1()};
  std::vector<T> result(N);
  for (int i{}; i < N; ++i) {
	T value{};
	for (int j{}; j < m.size2(); ++j) {
	  value += m(i, j) * vec[j];
	}
	result[i] = value;
  }

  return result;
}

template <typename T, std::convertible_to<T> E>
std::vector<T> operator*(const Matrix<T>& m, const std::vector<E>& vec) {
  size_t N{m.size1()};
  std::vector<T> result(N);
  for (int i{}; i < N; ++i) {
	T value{};
	for (int j{}; j < m.size2(); ++j) {
	  value += m(i, j) * vec[j];
	}
	result[i] = value;
  }
  
  return result;
}

// Overload sum operator for vectors
template <typename T>
std::vector<T> operator+(const std::vector<T>& v1, const std::vector<T>& v2) {
  std::vector<T> result(v1.size());

  for (int i{}; i < v1.size(); ++i) {
	result[i] = v1[i] + v2[i];
  }

  return result;
}

// Overload subtraction
template <typename T>
std::vector<T> operator-(const std::vector<T>& v1, const std::vector<T>& v2) {
  std::vector<T> result(v1.size());

  for (int i{}; i < v1.size(); ++i) {
	result[i] = v1[i] - v2[i];
  }

  return result;
}

// Overload product of vector with constant
template <typename T, std::convertible_to<T> E>
std::vector<T> operator*(E constant, std::vector<T> vec) {
  std::vector<T> result{vec};

  for (auto& element : result) {
	element *= constant;
  }

  return result;
}

// Overload of operator-= with matrices
template <typename T>
void operator-=(std::vector<T>& vec, const Matrix<T>& m) {
  for (int i{}; i < vec.size(); ++i) {
	vec[i] -= m.data()[i];
  }
}

template <typename T, typename E>
void operator-=(std::vector<T>& vec, const Matrix<E>& m) {
  for (int i{}; i < vec.size(); ++i) {
	vec[i] -= m.data()[i];
  }
}
