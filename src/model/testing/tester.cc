//
// Created by k.molotova on 7/11/23.
//

#include "tester.h"

namespace s21 {

Tester::Tester(s21::NeuralNet *net) : net_(net) {}

unsigned int Tester::ManualTest(const std::vector<double> &test_example) {
  error_ |= !net_->SetInput(test_example);
  net_->FeedForward();
  return net_->GetResult();
}

Tester::TestingInfo Tester::AutomationTest(data_example test_example,
                                           double part) {
  info_ = TestingInfo{};
  auto start = high_resolution_clock::now();

  int count_right = 0;
  int size = (int)((double)test_example.size() * part);
  Matrix<double> confusion_matrix = Matrix<double>(26, 26);

  for (int i = 0; i < size; i++) {
    int expected = (int)test_example[i].front();
    vector<double> input = test_example[i];
    input.erase(input.begin());
    error_ |= !net_->SetInput(input);
    net_->FeedForward();
    if (net_->GetResult() == expected) count_right++;
    confusion_matrix(net_->GetResult(), expected) += 1;
    info_.error += net_->GetError(expected);
  }

  auto end = high_resolution_clock::now();
  info_.time = ((duration<float>)(end - start)).count();
  info_.error /= size;
  info_.accuracy = count_right * 100. / size;

  info_.precision = CalculatePrecision(confusion_matrix);
  info_.recall = CalculateRecall(confusion_matrix);
  info_.f_measure = CalculateFMeasure(info_.precision, info_.recall);

  return info_;
}

double Tester::CalculatePrecision(Matrix<double> &confusion_matrix) {
  double precision = 0;
  int count = 0;
  for (int i = 0; i < 26; ++i) {
    double sum = 0;
    for (int j = 0; j < 26; ++j) {
      sum += confusion_matrix(i, j);
    }
    if (confusion_matrix(i, i) != 0) {
      precision += confusion_matrix(i, i) / sum;
      count++;
    }
  }
  return precision / count;
}

double Tester::CalculateRecall(Matrix<double> &confusion_matrix) {
  double recall = 0;
  int count = 0;
  for (int i = 0; i < 26; ++i) {
    double sum = 0;
    for (int j = 0; j < 26; ++j) {
      sum += confusion_matrix(j, i);
    }
    if (sum > 0) {
      recall += confusion_matrix(i, i) / sum;
      count++;
    }
  }
  return recall / count;
}

double Tester::CalculateFMeasure(double precision, double recall) {
  return 2 * (precision * recall) / (precision + recall);
}

}  // namespace s21
