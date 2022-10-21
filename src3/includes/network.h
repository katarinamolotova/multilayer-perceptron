#ifndef SRC_NETWORK_H_
#define SRC_NETWORK_H_

#include <vector>
#include "layer.h"
#include "../helpers/parser.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace s21 {
class Network {
  private:
    std::vector<Layer*> m_layers_;
    double m_learning_rate_;
//    double testPerfomance; // ???

    public:
      Network(std::vector<int> spec, size_t, size_t, double);

      // 1 в файле топология всех слоев, кроме выходного
      // 2 количество выходных нейронов
      // 3 скорость
      Network(std::string path, size_t, double);
      ~Network();
    
      std::vector<double> ForwardProp(const std::vector<double>& some_data);
      double Activate(const std::vector<double>&, const std::vector<double>&);  // dot product
      double Transfer(double);   // sigmoid
      double TransferDerivative(double);  // used for backprop
      void BackProp(const std::vector<double>& expected_data);
      void UpdateWeights(const std::vector<double>& some_data);
      int Predict(const std::vector<double>& some_data); // returns the index of maximum value int the output array
      double LearnOutput(const std::vector<double>& expected);
      void save();
      // void Train(int);
      // void Test();
      // void Validate();
    
    private:
      double GetOutputError_(const std::vector<double>& expected);
};  
}


#endif  // SRC_NETWORK_H_