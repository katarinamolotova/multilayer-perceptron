//
// Created by k.molotova on 7/11/23.
//

#ifndef CPP7_MLP_3_FACTORY_H
#define CPP7_MLP_3_FACTORY_H

#include "graph/graph_neural_net.h"
#include "matrix/matrix_neural_net.h"
#include "neural_net.h"

namespace s21 {

class Factory {
 public:
  static NeuralNet* GetNeuralNet(NeuralNetType type, int count_of_hidden_layers,
                                 bool use_random_weights) {
    NeuralNet* net;
    if (type == NeuralNetType::MATRIX)
      net = new MatrixNeuralNet();
    else
      net = new GraphNeuralNet();

    if (use_random_weights)
      SetParametersOfNeuralNet(net, count_of_hidden_layers);
    return net;
  }

 private:
  static void SetParametersOfNeuralNet(NeuralNet* net,
                                       int count_of_hidden_layers) {
    if (count_of_hidden_layers == 3)
      net->SetTopology({784, 128, 128, 128, 26});
    else if (count_of_hidden_layers == 4)
      net->SetTopology({784, 128, 128, 128, 128, 26});
    else if (count_of_hidden_layers == 5)
      net->SetTopology({784, 256, 256, 128, 64, 32, 26});
    else
      net->SetTopology({784, 256, 256, 26});
    net->SetRandomWeights();
  }
};

}  // namespace s21

#endif  // CPP7_MLP_3_FACTORY_H
