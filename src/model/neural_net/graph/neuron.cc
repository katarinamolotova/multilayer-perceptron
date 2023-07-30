//
// Created by Rebbecca Gormond aka Mikhail Kukhtachev on 10/14/22.
//

#include "neuron.h"

namespace s21 {
void Neuron::SetRandomWeight(int out) {
  for (int i = 0; i < out; i++) {
    weights_.emplace_back(NeuralNet::GetRandomWeight());
  }
}

void Neuron::SetValue(double value) { value_ = value; }

double Neuron::GetValue() const { return value_; }

double Neuron::GetNewValueForNextLayer(int index) {
  return value_ * weights_[index];
}

double Neuron::GetWeightsError() const { return error_weight_; }

void Neuron::SetWeightsError(double error_weights) {
  error_weight_ = error_weights;
}

const std::vector<double> &Neuron::GetWeights() const { return weights_; }

void Neuron::SetWeights(const std::vector<double> &weights) {
  weights_ = weights;
}

void Neuron::SetWeightsErrorWithDerivative(double sum) {
  error_weight_ = sum * value_ * (1 - value_);
}

double Neuron::GetDeltaWeight() const { return delta_weight_; }

void Neuron::SetDeltaWeight(double delta_weight) {
  delta_weight_ = delta_weight;
}

void Neuron::UpdateWeight(double moment, int index) {
  weights_[index] -= moment;
}

}  // namespace s21
