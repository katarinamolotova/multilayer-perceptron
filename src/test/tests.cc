#include <gtest/gtest.h>

#include "../controller/controller.h"

std::vector<double> getTestSet() {
  std::vector<double> result{
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   20,  114, 125, 82,
      37,  37,  39,  115, 157, 94,  21,  10,  32,  37,  37,  37,  37,  37,  37,
      37,  82,  125, 114, 20,  0,   0,   0,   3,   109, 245, 249, 233, 217, 217,
      217, 245, 251, 234, 172, 142, 203, 217, 217, 217, 217, 217, 217, 217, 233,
      249, 245, 109, 3,   0,   0,   4,   114, 253, 254, 254, 254, 254, 254, 254,
      254, 254, 252, 251, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254,
      127, 4,   0,   0,   0,   45,  214, 233, 251, 254, 254, 254, 254, 255, 255,
      255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254, 254, 251, 113, 4,
      0,   0,   0,   0,   5,   22,  82,  128, 160, 184, 217, 217, 218, 249, 254,
      255, 255, 255, 255, 255, 254, 254, 247, 216, 170, 83,  7,   0,   0,   0,
      0,   0,   0,   0,   2,   5,   16,  25,  37,  40,  50,  227, 254, 255, 255,
      254, 254, 252, 245, 220, 159, 38,  21,  3,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   9,   77,  140, 247, 254, 254, 254, 254, 244,
      177, 114, 50,  20,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   3,   34,  175, 246, 254, 254, 254, 253, 221, 115, 46,  7,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   34,
      84,  175, 251, 254, 254, 253, 234, 202, 91,  4,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   10,  79,  204, 233, 251,
      254, 255, 255, 239, 116, 35,  7,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   20,  123, 220, 254, 254, 254, 255, 255,
      255, 248, 165, 37,  21,  32,  9,   4,   4,   4,   4,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   100, 238, 254, 255, 255, 255, 255, 255, 255, 254,
      253, 235, 234, 245, 222, 217, 217, 217, 203, 115, 32,  0,   0,   0,   0,
      0,   0,   0,   33,  163, 244, 254, 254, 254, 255, 255, 255, 255, 254, 254,
      254, 254, 254, 254, 254, 254, 254, 240, 111, 3,   0,   0,   0,   0,   0,
      0,   1,   33,  126, 216, 233, 250, 254, 255, 255, 255, 255, 255, 255, 255,
      255, 255, 255, 254, 254, 233, 82,  2,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   5,   22,  82,  251, 255, 255, 255, 255, 255, 255, 254, 254, 250,
      233, 217, 203, 110, 18,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   10,  128, 254, 255, 255, 254, 254, 254, 254, 246, 208, 140, 82,  39,
      32,  4,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   22,  95,
      221, 254, 255, 254, 253, 234, 217, 215, 127, 46,  9,   2,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   154, 232, 253, 254,
      254, 252, 207, 95,  39,  37,  8,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   2,   77,  247, 254, 255, 254, 242, 131,
      9,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   4,   125, 254, 254, 252, 232, 131, 32,  0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   4,   113, 253, 246, 177, 109, 22,  0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   8,   111, 77,  8,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   3,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0};
  return result;
}

std::vector<int> getTestTopology() { return std::vector<int>{2, 1}; }

std::vector<double> getTestWeights() {
  return std::vector<double>{-0.604018, 0.73978};
}

TEST(Test, open_file_weigth) {
  s21::Controller c;
  if (c.LoadWeights("../datasets/weights/88.txt")) {
    SUCCEED();
  } else {
    FAIL();
  }
}

TEST(Test, open_file_data_set) {
  s21::Controller c;
  if (c.LoadWeights("../datasets/emnist/emnist-letters-for-test.csv")) {
    SUCCEED();
  } else {
    FAIL();
  }
}

TEST(Test, graph_manual) {
  s21::Controller c;
  c.LoadWeights("../datasets/weights/88.txt");
  c.MakeNeuralNet(false, 2, s21::NeuralNetType::GRAPH);
  std::vector<double> testSet = getTestSet();
  EXPECT_TRUE('W' == c.ManualTest(testSet));
}

TEST(Test, matrix_manual) {
  s21::Controller c;
  c.LoadWeights("../datasets/weights/88.txt");
  c.MakeNeuralNet(false, 2, s21::NeuralNetType::MATRIX);
  std::vector<double> testSet = getTestSet();
  EXPECT_TRUE('W' == c.ManualTest(testSet));
}

TEST(Test, graph_auto) {
  s21::Controller c;
  c.LoadWeights("../datasets/weights/88.txt");
  c.MakeNeuralNet(false, 2, s21::NeuralNetType::GRAPH);

  c.LoadDataSet("../datasets/emnist/emnist-letters-for-test.csv");
  s21::Tester::TestingInfo result = c.AutomationTest(1);

  EXPECT_TRUE(result.error < 0.3);
  EXPECT_TRUE(result.accuracy >= 50);
  EXPECT_TRUE(result.f_measure >= 0.5);
  EXPECT_TRUE(result.precision > 0.5);
  EXPECT_TRUE(result.recall > 0.5);
}

TEST(Test, matrix_auto) {
  s21::Controller c;
  c.LoadWeights("../datasets/weights/88.txt");
  c.MakeNeuralNet(false, 2, s21::NeuralNetType::MATRIX);

  c.LoadDataSet("../datasets/emnist/emnist-letters-for-test.csv");
  s21::Tester::TestingInfo result = c.AutomationTest(1);

  EXPECT_TRUE(result.error < 0.3);
  EXPECT_TRUE(result.accuracy >= 50);
  EXPECT_TRUE(result.f_measure >= 0.5);
  EXPECT_TRUE(result.precision > 0.5);
  EXPECT_TRUE(result.recall > 0.5);
}

TEST(Test, data_set_parser) {
  s21::Parser parser;
  parser.Parsing("../datasets/emnist/emnist-letters-for-test.csv");
  std::vector<double> benchmark = getTestSet();
  benchmark.insert(benchmark.begin(), 23. - 1);
  std::vector<std::vector<double>> data_set = parser.getDataSet();

  for (int i = 0; i < (int)benchmark.size(); i++) {
    EXPECT_TRUE((int)data_set[0][i] == (int)benchmark[i]);
  }
}

TEST(Test, weight_parser_topology) {
  s21::ParserWeights parser;
  parser.ReadWeightsFromFile("../datasets/weights/weight-for-test.txt");

  std::vector<int> topology = parser.GetTopology();
  std::vector<int> benchmark = getTestTopology();
  for (int i = 0; i < (int)topology.size(); i++) {
    EXPECT_TRUE(benchmark[i] == topology[i]);
  }
}

TEST(Test, weight_parser) {
  s21::ParserWeights parser;
  parser.ReadWeightsFromFile("../datasets/weights/weight-for-test.txt");

  std::vector<std::vector<std::vector<double>>> weight = parser.GetWeights();
  std::vector<double> benchmark = getTestWeights();
  for (int i = 0; i < (int)weight[0][0].size(); i++) {
    EXPECT_TRUE(benchmark[i] == weight[0][0][i]);
  }
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
