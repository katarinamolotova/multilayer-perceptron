//
// Created by k.molotova on 7/11/23.
//

#ifndef CPP7_MLP_3_TESTER_H
#define CPP7_MLP_3_TESTER_H

#include <chrono>
#include <vector>

#include "../neural_net/matrix/helpers/matrix.h"
#include "../neural_net/neural_net.h"

typedef std::vector<std::vector<double>> data_example;
using std::vector;
using std::chrono::duration;
using std::chrono::high_resolution_clock;

namespace s21 {

class Tester {
 public:
  struct TestingInfo {
    double time{};
    double error{};
    double accuracy{};
    double precision{};
    double recall{};
    double f_measure{};
  };

  explicit Tester(NeuralNet* net);
  TestingInfo AutomationTest(data_example test_example, double part);
  unsigned int ManualTest(const std::vector<double>& test_example);
  [[nodiscard]] bool GetError() const { return error_; }

 private:
  NeuralNet* net_;
  TestingInfo info_;
  bool error_ = false;

  static double CalculateFMeasure(double precision, double recall);
  static double CalculatePrecision(Matrix<double>& confusion_matrix);
  static double CalculateRecall(Matrix<double>& confusion_matrix);
};

}  // namespace s21

#endif  // CPP7_MLP_3_TESTER_H
