#ifndef SRC_MODEL_HELPERS_MATRIX_H_
#define SRC_MODEL_HELPERS_MATRIX_H_

#include <stdarg.h>

#include <cmath>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

namespace s21 {
template <class T>
class Matrix {
 private:
  int rows_{}, cols_{};
  T **matrix_{};
  bool error_{false};

 private:
  void CreateMatrix();
  void DeleteMatrix();
  void CopyMatrix(Matrix const &other);
  bool IsEqualSize(const Matrix &other);
  void InitMatrix(std::initializer_list<T> const &items);

 public:
  [[nodiscard]] int GetRows() const;
  [[nodiscard]] int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);
  void ResizeMatrix(int rows, int cols);
  bool GetError() { return error_; };
  bool IsEqualMatrix(const Matrix &other);
  void MulMatrix(const Matrix<T> &other);

  Matrix() = default;
  Matrix(int rows, int cols);
  Matrix(const Matrix &other);
  [[nodiscard]] Matrix(
      std::initializer_list<T> const &items);  // only for square matrix

  bool operator==(const Matrix &other);
  Matrix &operator=(const Matrix &other);
  T &operator()(int row, int col);
  Matrix<T> operator*(const Matrix<T> &other);

  ~Matrix();
};
}  // namespace s21

#endif  // SRC_MODEL_HELPERS_MATRIX_H_
