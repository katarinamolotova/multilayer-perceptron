//
// Created by k.molotova on 7/11/23.
//

#include "model.h"

namespace s21 {

bool Model::LoadDataSet(const string& path) {
  parser_datasets_.Parsing(path);
  return parser_datasets_.getError();
}

bool Model::LoadWeights(const string& path) {
  return parser_weights_.ReadWeightsFromFile(path);
}

bool Model::SaveWeights(const string& path) {
  return neural_net_->SaveWeights(parser_weights_, path);
}

bool Model::DataSetIsLoaded() {
  return !parser_datasets_.getError() && !parser_datasets_.getDataSet().empty();
}

bool Model::WeightsIsLoaded() {
  return !parser_weights_.GetError() && !parser_weights_.GetTopology().empty();
}

vector<Trainer::TrainingInfo> Model::Training(int count_of_epoch, int k_group) {
  vector<Trainer::TrainingInfo> info;
  trainer_ = new Trainer(neural_net_);

  if (k_group == 0) {
    info.reserve(count_of_epoch);
    for (int i = 0; i < count_of_epoch; i++)
      info.push_back(trainer_->Training(parser_datasets_.getDataSet()));
  } else {
    info.push_back(trainer_->TrainingWithCrossValidation(
        parser_datasets_.getDataSet(), k_group));
  }

  return info;
}

void Model::MakeNeuralNet(bool use_random_weights, int count_of_hidden_layers,
                          NeuralNetType type) {
  neural_net_ =
      Factory::GetNeuralNet(type, count_of_hidden_layers, use_random_weights);
  if (!use_random_weights) neural_net_->SetWeightsFromFile(parser_weights_);
}

Tester::TestingInfo Model::AutomationTest(double part) {
  tester_ = new Tester(neural_net_);
  return tester_->AutomationTest(parser_datasets_.getDataSet(), part);
}

char Model::ManualTest(vector<double>& data_set) {
  tester_ = new Tester(neural_net_);
  return 'A' + tester_->ManualTest(data_set);
}

bool Model::GetErrorTrain() { return trainer_->GetError(); }

bool Model::GetErrorTest() { return tester_->GetError(); }

}  // namespace s21
