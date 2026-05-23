#include "ATen/ops/flatten.h"
#include "CNN.hpp"
#include "torch/nn/modules/linear.h"
#include "torch/nn/modules/pooling.h"
#include "torch/nn/options/conv.h"
#include "torch/nn/options/pooling.h"
#include "torch/nn/pimpl.h"
#include <torch/torch.h>

// Construtor padrão
NeuralNet::NeuralNet() {}

// Construtor completo da rede neural
NeuralNet::NeuralNet(int fc1_dims, int fc2_dims, int fc3_dims)
    : conv1(torch::nn::Conv2dOptions(3, 12, 5)),
      conv2(torch::nn::Conv2dOptions(12, 24, 5)),
      pool(torch::nn::MaxPool2d(
          torch::nn::MaxPool2dOptions({2, 2}).stride({2, 2}))),
      fc1(fc1_dims, fc1_dims), fc2(fc1_dims, fc2_dims), fc3(fc1_dims, fc3_dims),
      out(fc2_dims, 1) {
  register_module("conv1", conv1);
  register_module("conv2", conv2);
  register_module("fc1", fc1);
  register_module("fc2", fc2);
  register_module("fc3", fc3);
  register_module("out", out);
}

// Implementação do método forward
torch::Tensor NeuralNet::forward(torch::Tensor &x) {
  x = this->pool(torch::relu(this->conv1(x)));
  x = this->pool(torch::relu(this->conv2(x)));
  x = torch::flatten(x, 1);
  x = torch::relu(this->fc1(x));
  x = torch::relu(this->fc2(x));
  x = this->fc3(x);
  return x;
}
