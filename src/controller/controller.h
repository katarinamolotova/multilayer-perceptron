#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>

#include "../model/model.h"

namespace s21 {

class Controller {
 public:
  Controller() { model_ = new Model(); }
  ~Controller() { delete model_; }

  bool LoadWeights(const std::string& path);
  bool LoadDataSet(const std::string& path);
  bool SaveWeight(const std::string& path);
  bool DataSetIsLoaded();
  bool WeightsIsLoaded();

  vector<Trainer::TrainingInfo> Training(bool use_random_weights,
                                         int count_of_hidden_layers,
                                         NeuralNetType type, int count_of_epoch,
                                         int k_group);

  Tester::TestingInfo AutomationTest(double part);
  char ManualTest(vector<double>&);

  void MakeNeuralNet(bool use_random_weights, int count_of_hidden_layers,
                     NeuralNetType type);

  bool GetErrorTrain();
  bool GetErrorTest();

 private:
  Model* model_;
};

}  // namespace s21

#endif  // CONTROLLER_H
