#pragma once
#include "torch/nn/module.h"
#include "torch/nn/modules/conv.h"
#include "torch/nn/modules/linear.h"
#include "torch/nn/modules/pooling.h"
#include <torch/torch.h>

class NeuralNet : public torch::nn::Module {
private:
  /* Uma convolução bidimensional é uma operação matemática
   * que aplica filtros sobrepostos em uma imagem bidimensional,
   * produzindo um "filtered output", que destaca certas características
   * da imagem original.
   * Link:
   * https://www.geeksforgeeks.org/computer-vision/apply-a-2d-convolution-operation-in-pytorch/
   * Complemento:
   * https://medium.com/@ml_dl_explained/understanding-2d-convolutions-in-pytorch-b35841149f5f
   */
  torch::nn::Conv2d conv1{nullptr}, conv2{nullptr};

  /* Pooling é uma técnica usada para reduzir a amostragem da feature
   * que vem de camadas anteriores e produz uma nova feature map resumida
   * Max Pooling seleciona o valor máximo de cada conjunto de filtros
   * sobrepostos e o passa para a próxima camada
   * Link:
   * https://www.geeksforgeeks.org/computer-vision/apply-a-2d-max-pooling-in-pytorch/
   */
  torch::nn::MaxPool2d pool{nullptr};

  /* Modulo que aplica uma transformação linear sobre a entrada utilizando
   * pesos e um viés opcional
   * Link:
   * https://docs.pytorch.org/docs/2.12/generated/torch.nn.Linear.html */
  torch::nn::Linear fc1{nullptr}, fc2{nullptr}, fc3{nullptr}, out{nullptr};

public:
  NeuralNet();
  NeuralNet(int fc1_dims, int fc2_dims, int fc3_dims);

  /* Tensor atua como uma matriz multidimensional que armazena os dados
   * de entrada e saída da rede neural.
   * Este método é responsável por realizar a propagação para frente (forward)
   * da rede neural, aplicando as camadas convolucionais, pooling e camadas
   * totalmente conectadas.
   * Link:
   * https://www.geeksforgeeks.org/deep-learning/understanding-the-forward-function-output-in-pytorch/*/
  torch::Tensor forward(torch::Tensor &x);

  // Getters
  torch::nn::Conv2d &get_conv1() { return conv1; }
  torch::nn::Conv2d &get_conv2() { return conv2; }
  torch::nn::MaxPool2d &get_pool() { return pool; }
  torch::nn::Linear &get_fc1() { return fc1; }
  torch::nn::Linear &get_fc2() { return fc2; }
  torch::nn::Linear &get_fc3() { return fc3; }
  torch::nn::Linear &get_out() { return out; }

  // Setters
  void set_fc1(torch::nn::Linear &fc1) { this->fc1 = fc1; }
  void set_fc2(torch::nn::Linear &fc2) { this->fc2 = fc2; }
  void set_fc3(torch::nn::Linear &fc3) { this->fc3 = fc3; }
  void set_out(torch::nn::Linear &out) { this->out = out; }
};
