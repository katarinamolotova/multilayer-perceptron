//
// Created by Chastity Eryn on 7/12/23.
//

#ifndef CPP7_MLP_3_PARSER_WEIGHTS_H
#define CPP7_MLP_3_PARSER_WEIGHTS_H

#include <fstream>
#include <vector>

#include "../neural_net/matrix/helpers/matrix.h"

namespace s21 {

using std::fstream;
using std::ofstream;
using std::vector;

class ParserWeights {
 public:
  ParserWeights() = default;
  ~ParserWeights() = default;

  bool ReadWeightsFromFile(const std::string &);
  bool WriteWeightsToFile(const std::string &, vector<int> &,
                          vector<vector<vector<double>>> &);

  vector<int> GetTopology();
  vector<vector<vector<double>>> GetWeights();
  bool GetError() { return error_; }

 private:
  vector<vector<vector<double>>> weights_;
  vector<int> topology_;
  bool error_ = false;

  void WriteTopologyToFile(ofstream &, vector<int> &);
  void ClearAll();
};

}  // namespace s21

#endif  // CPP7_MLP_3_PARSER_WEIGHTS_H
