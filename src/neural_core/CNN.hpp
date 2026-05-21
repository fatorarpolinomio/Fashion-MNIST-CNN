#pragma once
#include "torch/nn/module.h"
#include "torch/nn/modules/conv.h"
#include "torch/nn/modules/pooling.h"
#include <torch/torch.h>

class NeuralNet : torch::nn::Module {
private:
  torch::nn::Conv2d conv1{nullptr}, conv2{nullptr};
  torch::nn::MaxPool2d pool{nullptr};
  torch::nn::Linear fc1{nullptr}, fc2{nullptr}, fc3{nullptr}, out{nullptr};

public:
  NeuralNet(int fc1_dims, int fc2_dims, int fc3_dims);
  torch::Tensor forward(torch::Tensor x);

  // Getters
  torch::nn::Conv2d &get_conv1() { return conv1; }
  torch::nn::Conv2d &get_conv2() { return conv2; }
  torch::nn::MaxPool2d &get_pool() { return pool; }
  torch::nn::Linear &get_fc1() { return fc1; }
  torch::nn::Linear &get_fc2() { return fc2; }
  torch::nn::Linear &get_out() { return out; }

  // Setters
  void set_fc1(torch::nn::Linear &fc1) { this->fc1 = fc1; }
  void set_fc2(torch::nn::Linear &fc2) { this->fc2 = fc2; }
  void set_out(torch::nn::Linear &out) { this->out = out; }
};
