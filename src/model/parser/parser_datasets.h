//
// Created by Rebbecca Gormond aka Mikhail Kukhtachev on 10/4/22.
//

#ifndef MODEL_PARSER_H
#define MODEL_PARSER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace s21 {

class Parser {
 public:
  Parser() : error_(false) {}
  ~Parser() = default;

  void Parsing(const std::string &file_name);

  [[nodiscard]] bool getError() const { return error_; };
  [[nodiscard]] const std::vector<std::vector<double>> &getDataSet() const;
  [[nodiscard]] unsigned int getStringSize() const;

 private:
  std::vector<std::vector<double>> data_set_;
  bool error_;
  unsigned int string_size_ = 0;
  std::vector<double> StringParsing(std::string line);
};
}  // namespace s21

#endif  // MODEL_PARSER_H
