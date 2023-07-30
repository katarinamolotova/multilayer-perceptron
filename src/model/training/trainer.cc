//
// Created by k.molotova on 7/11/23.
//

#include "trainer.h"

namespace s21 {

Trainer::Trainer(NeuralNet* net) : net_(net) {}

Trainer::TrainingInfo Trainer::Training(vector<vector<double>> data_set) {
  info_ = TrainingInfo{};
  auto start = high_resolution_clock::now();

  int count_right = 0;
  for (vector<double>& data : data_set) {
    int expected = (int)data.front();
    vector<double> input = data;
    input.erase(input.begin());
    error_ |= !net_->SetInput(input);
    net_->FeedForward();
    if (net_->GetResult() == expected) count_right++;
    info_.error += net_->GetError(expected);
    net_->BackPropagation(expected);
  }

  auto end = high_resolution_clock::now();
  info_.accuracy = count_right * 100. / (double)data_set.size();
  info_.time = ((duration<float>)(end - start)).count();
  info_.error /= (int)data_set.size();
  return info_;
}

Trainer::TrainingInfo Trainer::TrainingWithCrossValidation(
    const vector<vector<double>>& data_set, int k_groups) {
  info_ = TrainingInfo{};
  auto start = high_resolution_clock::now();

  if (data_set.size() < 3) {
    error_ = true;
    return {};
  }

  int lines_in_part = (int)data_set.size() / k_groups;
  int count_right = 0;

  for (int i = 0; i < k_groups; ++i) {
    TrainCrossValidation(i, lines_in_part, data_set);
    TestCrossValidation(i, lines_in_part, count_right, data_set);
  }

  auto end = high_resolution_clock::now();
  info_.time = ((duration<float>)(end - start)).count();
  info_.accuracy = count_right * 100. / (int)data_set.size();
  info_.error /= (int)data_set.size();
  return info_;
}

void Trainer::TrainCrossValidation(int number, int lines_in_part,
                                   const vector<vector<double>>& data_set) {
  int iterator = 0;
  for (int j = 0; j < (int)data_set.size(); ++j) {
    if (j == number * lines_in_part) {
      j = number * lines_in_part + lines_in_part - 1;
      iterator += lines_in_part;
    } else {
      int expected = (int)data_set[iterator].front();
      vector<double> input = data_set[iterator];
      input.erase(input.begin());

      error_ |= !net_->SetInput(input);
      net_->FeedForward();
      net_->BackPropagation(expected);
      iterator++;
    }
  }
}

void Trainer::TestCrossValidation(int number, int lines_in_part,
                                  int& count_right,
                                  const vector<vector<double>>& data_set) {
  int iterator = 0;
  for (int j = 0; j < (int)data_set.size(); ++j) {
    if (j >= number * lines_in_part &&
        j < number * lines_in_part + lines_in_part) {
      int expected = (int)data_set[iterator].front();
      vector<double> input = data_set[iterator];
      input.erase(input.begin());

      error_ |= !net_->SetInput(input);
      net_->FeedForward();
      int prediction = net_->GetResult();

      if (prediction == expected) count_right++;
      info_.error += net_->GetError(expected);
      iterator++;
    } else {
      iterator += lines_in_part;
      j += lines_in_part - 1;
    }
  }
}

}  // namespace s21
