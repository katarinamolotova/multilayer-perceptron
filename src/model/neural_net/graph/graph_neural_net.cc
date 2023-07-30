//
// Created by k.molotova on 7/11/23.
//

#include "graph_neural_net.h"

namespace s21 {

void GraphNeuralNet::SetTopology(vector<int> topology) {
  topology_ = topology;
  count_layers_ = (int)topology.size();
  layers_.clear();
}

void GraphNeuralNet::SetRandomWeights() {
  for (int i = 0; i < count_layers_; i++) {
    layers_.emplace_back(topology_[i]);
    if (i != count_layers_ - 1) layers_[i].SetRandomWeight(topology_[i + 1]);
  }
}

void GraphNeuralNet::SetWeightsFromFile(ParserWeights &parser) {
  SetTopology(parser.GetTopology());
  prepare_weight net_parameters = parser.GetWeights();
  for (int i = 0; i < count_layers_; i++) {
    layers_.emplace_back(topology_[i]);

    if (i != count_layers_ - 1)
      for (int j = 0; j < (int)net_parameters[i].size(); j++)
        layers_[i].SetWeightVector(net_parameters[i][j], j);
  }
}

bool GraphNeuralNet::SaveWeights(ParserWeights &parser, const string &path) {
  prepare_weight data_for_save;
  for (int i = 0; i < count_layers_ - 1; ++i) data_for_save.emplace_back();

  for (int i = 0; i < count_layers_ - 1; ++i) {
    for (int j = 0; j < topology_[i]; ++j) {
      data_for_save[i].emplace_back(layers_[i].GetWeightForIndex(j));
    }
  }
  return parser.WriteWeightsToFile(path, topology_, data_for_save);
}

bool GraphNeuralNet::SetInput(const std::vector<double> &values) {
  if (layers_[0].GetSize() != (int)values.size()) {
    return false;
  } else {
    layers_[0].SetValues(values);
  }
  return true;
}

void GraphNeuralNet::FeedForward() {
  for (int i = 1; i < count_layers_; ++i) {
    layers_[i - 1].FeedForward(layers_[i], layers_[i].GetSize());
  }
}

int GraphNeuralNet::GetResult() {
  std::vector<Neuron> output = layers_[count_layers_ - 1].GetNeurons();
  double max = output[0].GetValue();
  int prediction = 0;
  double tmp;
  for (int i = 1; i < (int)output.size(); i++) {
    tmp = output[i].GetValue();
    if (tmp > max) {
      prediction = i;
      max = tmp;
    }
  }
  return prediction;
}

void GraphNeuralNet::BackPropagation(int expected) {
  UpdateErrorOutputLayer(expected);
  UpdateErrorHiddenLayers();
  UpdateWeights();
}

void GraphNeuralNet::UpdateErrorOutputLayer(int expected) {
  layers_[count_layers_ - 1].UpdateErrorOutputLayer(expected);
}

void GraphNeuralNet::UpdateErrorHiddenLayers() {
  for (int k = count_layers_ - 2; k > 0; --k) {
    layers_[k].UpdateErrorHiddenLayers(layers_[k + 1]);
  }
}

void GraphNeuralNet::UpdateWeights() {
  for (int i = 0; i < count_layers_ - 1; ++i) {
    layers_[i].UpdateWeights(layers_[i + 1], learning_rate_, moment_);
  }
}

double GraphNeuralNet::GetError(int expected) {
  return pow(layers_[count_layers_ - 1].GetNeurons()[expected].GetValue() - 1,
             2);
}

}  // namespace s21