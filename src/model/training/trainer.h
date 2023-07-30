//
// Created by k.molotova on 7/11/23.
//

#ifndef CPP7_MLP_3_TRAINER_H
#define CPP7_MLP_3_TRAINER_H

#include <chrono>
#include <vector>

#include "../neural_net/neural_net.h"

namespace s21 {

using std::vector;
using std::chrono::duration;
using std::chrono::high_resolution_clock;

class Trainer {
 public:
  struct TrainingInfo {
    double time{};
    double error{};
    double accuracy{};
  };

  explicit Trainer(NeuralNet* net);
  TrainingInfo Training(vector<vector<double>> data_set);
  TrainingInfo TrainingWithCrossValidation(
      const vector<vector<double>>& data_set, int k_groups);
  bool GetError() { return error_; }

 private:
  NeuralNet* net_;
  TrainingInfo info_;
  bool error_ = false;

  void TrainCrossValidation(int number, int lines_in_part,
                            const vector<vector<double>>& data_set);
  void TestCrossValidation(int number, int lines_in_part, int& count_right,
                           const vector<vector<double>>& data_set);
};

}  // namespace s21

#endif  // CPP7_MLP_3_TRAINER_H
