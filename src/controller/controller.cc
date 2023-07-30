#include "controller.h"

namespace s21 {

bool Controller::LoadWeights(const std::string& path) {
  return model_->LoadWeights(path);
}

bool Controller::SaveWeight(const std::string& path) {
  return model_->SaveWeights(path);
}

bool Controller::LoadDataSet(const string& path) {
  return model_->LoadDataSet(path);
}

bool Controller::DataSetIsLoaded() { return model_->DataSetIsLoaded(); }

bool Controller::WeightsIsLoaded() { return model_->WeightsIsLoaded(); }

vector<Trainer::TrainingInfo> Controller::Training(bool use_random_weights,
                                                   int count_of_hidden_layers,
                                                   NeuralNetType type,
                                                   int count_of_epoch,
                                                   int k_group = 0) {
  MakeNeuralNet(use_random_weights, count_of_hidden_layers, type);
  return model_->Training(count_of_epoch, k_group);
}

Tester::TestingInfo Controller::AutomationTest(double part) {
  return model_->AutomationTest(part);
}

char Controller::ManualTest(vector<double>& data_set) {
  return model_->ManualTest(data_set);
}

void Controller::MakeNeuralNet(bool use_random_weights,
                               int count_of_hidden_layers, NeuralNetType type) {
  model_->MakeNeuralNet(use_random_weights, count_of_hidden_layers, type);
}

bool Controller::GetErrorTrain() { return model_->GetErrorTrain(); }

bool Controller::GetErrorTest() { return model_->GetErrorTest(); }

}  // namespace s21
