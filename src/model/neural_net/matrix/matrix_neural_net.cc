//
// Created by k.molotova on 7/11/23.
//

#include "matrix_neural_net.h"

namespace s21 {

void MatrixNeuralNet::SetTopology(vector<int> topology) {
  topology_ = topology;
  weights_.clear();
  weights_error_.clear();
  weights_delta_.clear();
  values_.clear();

  for (int i = 0; i < (int)topology_.size() - 1; i++)
    weights_.emplace_back(topology_[i], topology_[i + 1]);

  for (int &i : topology_) {
    values_.emplace_back(1, i);
    weights_error_.emplace_back(1, i);
    weights_delta_.emplace_back(1, i);
  }
}

void MatrixNeuralNet::SetRandomWeights() {
  for (int i = 0; i < (int)topology_.size() - 1; i++)
    for (int j = 0; j < weights_[i].GetRows(); j++)
      for (int k = 0; k < weights_[i].GetCols(); k++)
        weights_[i](j, k) = GetRandomWeight();
}

void MatrixNeuralNet::SetWeightsFromFile(ParserWeights &parser) {
  SetTopology(parser.GetTopology());
  vector<vector<vector<double>>> weights = parser.GetWeights();
  for (int i = 0; i < (int)topology_.size() - 1; i++)
    for (int j = 0; j < weights_[i].GetRows(); j++)
      for (int k = 0; k < weights_[i].GetCols(); k++)
        weights_[i](j, k) = weights[i][j][k];
}

bool MatrixNeuralNet::SetInput(const vector<double> &input_value) {
  if ((int)input_value.size() != topology_[0]) return false;

  for (int i = 0; i < topology_[0]; i++) values_[0](0, i) = input_value[i];

  return true;
}

void MatrixNeuralNet::BackPropagation(int expected) {
  UpdateErrorOutputLayer(expected);
  UpdateErrorHiddenLayers();
  UpdateWeights();
}

void MatrixNeuralNet::UpdateErrorOutputLayer(int expected) {
  for (int i = 0; i < topology_[topology_.size() - 1]; ++i) {
    double value = values_[topology_.size() - 1](0, i);
    int active = (i != expected) ? 0 : 1;
    weights_error_[topology_.size() - 1](0, i) =
        -value * (1 - value) * (active - value);
  }
}

void MatrixNeuralNet::UpdateErrorHiddenLayers() {
  for (int k = (int)topology_.size() - 2; k > 0; --k) {
    for (int i = 0; i < weights_[k].GetRows(); ++i) {
      double tmp = 0;
      for (int j = 0; j < weights_[k].GetCols(); ++j)
        tmp += weights_[k](i, j) * weights_error_[k + 1](0, j);
      weights_error_[k](0, i) = tmp * values_[k](0, i) * (1 - values_[k](0, i));
    }
  }
}

void MatrixNeuralNet::UpdateWeights() {
  for (int i = 0; i < (int)topology_.size() - 1; ++i) {
    for (int j = 0; j < topology_[i + 1]; ++j) {
      double error_la = weights_error_[i + 1](0, j) * learning_rate_;
      for (int k = 0; k < topology_[i]; ++k) {
        double value = values_[i](0, k);
        double new_moment = (moment_ * weights_delta_[i](0, k)) +
                            (1 - moment_) * (error_la * value);
        weights_delta_[i](0, k) = new_moment;
        weights_[i](k, j) -= new_moment;
      }
    }
  }
}

void MatrixNeuralNet::FeedForward() {
  for (int i = 1; i < (int)values_.size(); i++) {
    values_[i] = values_[i - 1] * weights_[i - 1];
    Matrix new_matrix = Sigmoid(values_[i]);
    values_[i] = new_matrix;
  }
}

Matrix<double> MatrixNeuralNet::Sigmoid(Matrix<double> &matrix) {
  int rows = matrix.GetRows();
  int cols = matrix.GetCols();
  Matrix<double> result(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      result(i, j) = 1.0 / (1.0 + (exp((-1) * matrix(i, j))));
    }
  }
  return result;
}

double MatrixNeuralNet::GetError(int expected) {
  return pow(values_[topology_.size() - 1](0, expected) - 1, 2);
}

int MatrixNeuralNet::GetResult() {
  Matrix output = values_[topology_.size() - 1];
  double max = output(0, 0);
  int prediction = 0;
  double tmp;
  for (int i = 1; i < output.GetCols(); i++) {
    tmp = output(0, i);
    if (tmp > max) {
      prediction = i;
      max = tmp;
    }
  }
  return prediction;
}

bool MatrixNeuralNet::SaveWeights(ParserWeights &parser, const string &path) {
  vector<vector<vector<double>>> weights;
  for (int i = 0; i < (int)topology_.size() - 1; i++) {
    weights.emplace_back();
    for (int j = 0; j < weights_[i].GetRows(); j++) {
      weights[i].emplace_back();
      for (int k = 0; k < weights_[i].GetCols(); k++)
        weights[i][j].push_back(weights_[i](j, k));
    }
  }
  return parser.WriteWeightsToFile(path, topology_, weights);
}

}  // namespace s21
