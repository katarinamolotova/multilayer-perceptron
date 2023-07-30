//
// Created by Rebbecca Gormond on 7/12/23.
//

#ifndef CPP7_MLP_3_LAYER_H
#define CPP7_MLP_3_LAYER_H

#include "neuron.h"

namespace s21 {
class Layer {
 public:
  explicit Layer(int size);

  [[nodiscard]] const std::vector<Neuron>& GetNeurons() const;
  [[nodiscard]] int GetSize() const;

  std::vector<double> GetWeightForIndex(int index);
  void SetWeightVector(const std::vector<double>& weight_vector, int index);
  void SetRandomWeight(int out);
  void SetValues(const std::vector<double>& values);
  void FeedForward(Layer& layer, int size);
  void UpdateErrorOutputLayer(int expected);
  void UpdateErrorHiddenLayers(const Layer& next_layer);
  void UpdateWeights(const Layer& next_layer, double learning_rate,
                     double scale);
  static double Sigmoid(double x);

 private:
  int size_;
  std::vector<Neuron> neurons_;
};

}  // namespace s21

#endif  // CPP7_MLP_3_LAYER_H
