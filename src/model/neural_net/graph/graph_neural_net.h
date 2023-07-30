//
// Created by k.molotova on 7/11/23.
//

#ifndef CPP7_MLP_3_GRAPH_NEURAL_NET_H
#define CPP7_MLP_3_GRAPH_NEURAL_NET_H

#include <fstream>

#include "../neural_net.h"
#include "layer.h"

typedef std::vector<std::vector<std::vector<double>>> prepare_weight;

namespace s21 {

class GraphNeuralNet : public NeuralNet {
 public:
  GraphNeuralNet() = default;

  void FeedForward() override;
  void BackPropagation(int expected) override;

  bool SetInput(const vector<double> &values) override;
  void SetTopology(vector<int>) override;

  void SetRandomWeights() override;
  void SetWeightsFromFile(ParserWeights &parser) override;
  bool SaveWeights(ParserWeights &parser, const string &path) override;

  double GetError(int expected) override;
  int GetResult() override;

 private:
  void UpdateErrorOutputLayer(int expected);
  void UpdateErrorHiddenLayers();
  void UpdateWeights();

  int count_layers_{};
  std::vector<int> topology_;
  std::vector<Layer> layers_;
};

}  // namespace s21

#endif  // CPP7_MLP_3_GRAPH_NEURAL_NET_H
