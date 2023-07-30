//
// Created by Rebbecca Gormond aka Mikhail Kukhtachev on 10/4/22.
//

#include "parser_datasets.h"

namespace s21 {

void Parser::Parsing(const std::string &file_name) {
  std::string line;
  std::ifstream file(file_name);
  error_ = false;
  if (file.is_open()) {
    while (getline(file, line)) {
      data_set_.push_back(StringParsing(line));
    }
    data_set_.shrink_to_fit();
    file.close();
  } else {
    error_ = true;
  }
}

std::vector<double> Parser::StringParsing(std::string line) {
  bool is_first = true;
  std::vector<double> result_vector;
  result_vector.reserve(string_size_);
  std::string tmp_sub_string;
  for (auto it = line.begin(); it <= line.end(); it++) {
    if (isdigit(*it)) {
      tmp_sub_string += *it;
    }
    if ((*it == ',' || it == line.end()) && !tmp_sub_string.empty()) {
      double temp_number = std::stod(tmp_sub_string);
      if (is_first) {
        temp_number -= 1.0;
        is_first = false;
      }
      result_vector.push_back(temp_number);
      tmp_sub_string.clear();
    }
  }
  result_vector.shrink_to_fit();
  string_size_ = result_vector.size();
  return result_vector;
}

const std::vector<std::vector<double>> &Parser::getDataSet() const {
  return data_set_;
}

unsigned int Parser::getStringSize() const { return string_size_; }

}  // namespace s21
