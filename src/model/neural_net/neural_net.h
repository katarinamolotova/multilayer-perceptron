//
// Created by k.molotova on 7/11/23.
//

#ifndef CPP7_MLP_3_NEURAL_NET_H
#define CPP7_MLP_3_NEURAL_NET_H

#define MIN_WEIGHT (-1.0)
#define MAX_WEIGHT 1.0

#include <fstream>
#include <random>
#include <string>
#include <vector>

#include "../parser/parser_weights.h"

namespace s21 {

using std::fstream;
using std::string;
using std::vector;

enum class NeuralNetType { MATRIX, GRAPH };

class NeuralNet {
 public:
  virtual ~NeuralNet() = default;

  virtual bool SetInput(const vector<double> &) = 0;
  virtual void SetTopology(vector<int>) = 0;

  virtual void SetRandomWeights() = 0;
  virtual void SetWeightsFromFile(ParserWeights &parser) = 0;
  virtual bool SaveWeights(ParserWeights &parser, const string &path) = 0;

  virtual void FeedForward() = 0;
  virtual void BackPropagation(int expected) = 0;

  virtual double GetError(int expected) = 0;
  virtual int GetResult() = 0;

  static double GetRandomWeight() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_real_distribution<double> dist(MIN_WEIGHT, MAX_WEIGHT);
    return dist(engine);
  }

 protected:
  const double learning_rate_ = 0.3;
  const double moment_ = 0.1;
};

}  // namespace s21

#endif  // CPP7_MLP_3_NEURAL_NET_H
