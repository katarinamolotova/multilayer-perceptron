//
// Created by k.molotova on 7/11/23.
//

#ifndef CPP7_MLP_3_MATRIX_NEURAL_NET_H
#define CPP7_MLP_3_MATRIX_NEURAL_NET_H

#include "../neural_net.h"
#include "helpers/matrix.h"

namespace s21 {

class MatrixNeuralNet : public NeuralNet {
 public:
  MatrixNeuralNet() = default;

  void BackPropagation(int expected) override;
  void FeedForward() override;

  bool SetInput(const vector<double> &) override;
  void SetTopology(vector<int>) override;

  void SetRandomWeights() override;
  void SetWeightsFromFile(ParserWeights &parser) override;
  bool SaveWeights(ParserWeights &parser, const string &path) override;

  double GetError(int expected) override;
  int GetResult() override;

 private:
  vector<Matrix<double>> weights_;
  vector<Matrix<double>> weights_error_;
  vector<Matrix<double>> weights_delta_;
  vector<Matrix<double>> values_;
  vector<int> topology_;

  static Matrix<double> Sigmoid(Matrix<double> &matrix);
  void UpdateErrorOutputLayer(int expected);
  void UpdateErrorHiddenLayers();
  void UpdateWeights();
};

}  // namespace s21

#endif  // CPP7_MLP_3_MATRIX_NEURAL_NET_H
