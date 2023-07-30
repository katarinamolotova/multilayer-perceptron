//
// Created by Rebbecca Gormond on 7/12/23.
//

#include "layer.h"

namespace s21 {
Layer::Layer(int size) {
  size_ = size;
  for (int i = 0; i < size_; i++) {
    neurons_.emplace_back();
  }
}

void Layer::SetRandomWeight(int out) {
  for (auto &it : neurons_) {
    it.SetRandomWeight(out);
  }
}

int Layer::GetSize() const { return size_; }

void Layer::SetValues(const std::vector<double> &values) {
  for (int i = 0; i < size_; ++i) {
    neurons_[i].SetValue(values[i]);
  }
}

void Layer::FeedForward(Layer &layer, int size) {
  for (int i = 0; i < size; ++i) {
    double sum = 0;
    for (int j = 0; j < size_; ++j) {
      sum += neurons_[j].GetNewValueForNextLayer(i);
    }
    double value = Sigmoid(sum);
    layer.neurons_[i].SetValue(value);
  }
}

double Layer::Sigmoid(double x) { return 1 / (1 + (exp(-x))); }

void Layer::UpdateErrorOutputLayer(int expected) {
  for (int i = 0; i < size_; ++i) {
    int elem = 0;
    double O_cur = neurons_[i].GetValue();
    if (i == expected) {
      elem = 1;
    }
    neurons_[i].SetWeightsError(-O_cur * (1 - O_cur) * (elem - O_cur));
  }
}

const std::vector<Neuron> &Layer::GetNeurons() const { return neurons_; }

void Layer::SetWeightVector(const std::vector<double> &weight_vector,
                            int index) {
  neurons_[index].SetWeights(weight_vector);
}

void Layer::UpdateErrorHiddenLayers(const Layer &next_layer) {
  for (int i = 0; i < size_; ++i) {
    double sum = 0;
    std::vector<double> weights = neurons_[i].GetWeights();
    for (int j = 0; j < next_layer.size_; ++j) {
      sum += weights[j] * next_layer.neurons_[j].GetWeightsError();
    }
    neurons_[i].SetWeightsErrorWithDerivative(sum);
  }
}

void Layer::UpdateWeights(const Layer &next_layer, double learning_rate,
                          double scale) {
  for (int j = 0; j < next_layer.size_; ++j) {
    double delta_la = next_layer.neurons_[j].GetWeightsError() * learning_rate;
    for (int k = 0; k < size_; ++k) {
      double O_cur = neurons_[k].GetValue();
      double new_delta_weight = (scale * neurons_[k].GetDeltaWeight()) +
                                (1 - scale) * (delta_la * O_cur);
      neurons_[k].SetDeltaWeight(new_delta_weight);
      neurons_[k].UpdateWeight(new_delta_weight, j);
    }
  }
}

std::vector<double> Layer::GetWeightForIndex(int index) {
  return neurons_[index].GetWeights();
}

}  // namespace s21