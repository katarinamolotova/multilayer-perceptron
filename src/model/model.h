//
// Created by k.molotova on 7/11/23.
//

#ifndef CPP7_MLP_3_MODEL_H
#define CPP7_MLP_3_MODEL_H

#include <string>

#include "neural_net/factory.h"
#include "neural_net/neural_net.h"
#include "parser/parser_datasets.h"
#include "parser/parser_weights.h"
#include "testing/tester.h"
#include "training/trainer.h"

namespace s21 {

using std::string;

class Model {
 public:
  Model() = default;
  ~Model() {
    delete tester_;
    delete trainer_;
    delete neural_net_;
  }

  bool LoadDataSet(const string& path);
  bool LoadWeights(const string& path);
  bool SaveWeights(const string& path);
  bool DataSetIsLoaded();
  bool WeightsIsLoaded();
  vector<Trainer::TrainingInfo> Training(int count_of_epoch, int k_group);
  void MakeNeuralNet(bool use_random_weights, int count_of_hidden_layers,
                     NeuralNetType type);
  Tester::TestingInfo AutomationTest(double part);
  char ManualTest(vector<double>&);
  bool GetErrorTrain();
  bool GetErrorTest();

 private:
  Parser parser_datasets_;
  ParserWeights parser_weights_;
  NeuralNet* neural_net_ = nullptr;
  Trainer* trainer_ = nullptr;
  Tester* tester_ = nullptr;
};

}  // namespace s21

#endif  // CPP7_MLP_3_MODEL_H
