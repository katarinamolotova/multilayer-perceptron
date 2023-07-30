//
// Created by Chastity Eryn on 7/12/23.
//

#include "parser_weights.h"

namespace s21 {

bool ParserWeights::ReadWeightsFromFile(const std::string &path) {
  ClearAll();
  fstream in(path);
  if (!in.is_open()) {
    error_ = true;
    return false;
  }

  int count_of_layers;
  in >> count_of_layers;

  for (int i = 0; i < count_of_layers; i++) {
    int count_of_neurons;
    in >> count_of_neurons;
    topology_.push_back(count_of_neurons);
  }

  for (int i = 0; i < count_of_layers - 1; i++) {
    weights_.emplace_back();
    for (int j = 0; j < topology_[i]; j++) {
      weights_[i].emplace_back();
      vector<double> weights;
      for (int k = 0; k < topology_[i + 1]; k++) {
        if (in.eof()) return false;
        in >> weights_[i][j].emplace_back();
      }
    }
  }

  error_ = false;
  return true;
}

bool ParserWeights::WriteWeightsToFile(
    const std::string &path, vector<int> &topology,
    vector<vector<vector<double>>> &weights) {
  ofstream out(path);
  if (!out.is_open()) {
    error_ = true;
    return false;
  }

  WriteTopologyToFile(out, topology);
  weights_ = weights;

  for (int k = 0; k < (int)topology.size() - 1; ++k) {
    for (int i = 0; i < topology_[k]; ++i) {
      for (int j = 0; j < topology_[k + 1]; ++j) {
        out << weights_[k][i][j] << " ";
      }
    }
  }

  error_ = false;
  return true;
}

void ParserWeights::WriteTopologyToFile(ofstream &out, vector<int> &topology) {
  topology_ = topology;
  out << topology_.size();
  out << " ";
  for (int i = 0; i < (int)topology_.size(); i++) {
    out << topology[i];
    if (i != (int)topology_.size() - 1) out << " ";
  }
  out << "\n";
}

vector<int> ParserWeights::GetTopology() { return topology_; }

vector<vector<vector<double>>> ParserWeights::GetWeights() { return weights_; }

void ParserWeights::ClearAll() {
  topology_.clear();
  weights_.clear();
}

}  // namespace s21
