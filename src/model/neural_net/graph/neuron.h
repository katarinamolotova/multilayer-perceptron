//
// Created by Rebbecca Gormond aka Mikhail Kukhtachev on 10/14/22.
//

#ifndef NEURON_H_
#define NEURON_H_

#include <cmath>
#include <vector>

#include "../neural_net.h"

namespace s21 {

class Neuron {
 public:
  [[nodiscard]] double GetWeightsError() const;
  [[nodiscard]] double GetValue() const;
  [[nodiscard]] double GetNewValueForNextLayer(int index);
  [[nodiscard]] double GetDeltaWeight() const;
  [[nodiscard]] const std::vector<double> &GetWeights() const;

  void SetRandomWeight(int out);
  void SetValue(double value);
  void SetWeights(const std::vector<double> &weights);
  void SetWeightsError(double error_weight);
  void SetWeightsErrorWithDerivative(double sum);
  void SetDeltaWeight(double delta_weight);
  void UpdateWeight(double moment, int index);

 private:
  double value_{};
  double error_weight_{};
  double delta_weight_{};
  std::vector<double> weights_;
};

}  // namespace s21

#endif  // NEURON_H_
