#include "ATen/core/interned_strings.h"
#include "dataset_core/FashionMNIST.hpp"
#include "neural_core/CNN.hpp"
#include "torch/data/dataloader.h"
#include "torch/data/samplers/random.h"
#include "torch/optim/sgd.h"
#include <iostream>
#include <matplot/matplot.h>
#include <torch/torch.h>
#include <vector>

int main() {

  // Talvez transformar isso aqui tudo em uma função num arquivo separado
  const size_t batch_size = 64;

  // Instanciando o dataset e aplicando a transformação Stack
  auto dataset = FashionMNIST().map(torch::data::transforms::Stack<>());

  // Criando o train_loader (usando RandomSampler pra embaralhar)
  auto train_loader =
      torch::data::make_data_loader<torch::data::samplers::RandomSampler>(
          std::move(dataset), batch_size);

  auto net = NeuralNet();
  auto loss_function = torch::nn::CrossEntropyLoss();
  auto optimizer = torch::optim::SGDOptions(0.01).momentum(0.9);
  auto optimizer_instance = torch::optim::SGD(net.parameters(), optimizer);

  for (int epoch; epoch < 30; epoch++) {
    std::cout << "Treinando epoch: " << epoch << "..." << std::endl;
    double running_loss = 0.0;
    for (const auto &[i, data] : c10::prim::enumerate(train_loader)) {
      auto inputs = data;
      auto labels = data;
      optimizer_instance.zero_grad();
      auto outputs = net(inputs);
      auto loss = loss_function(outputs, labels);
      loss.backward();
      optimizer_instance.step();
      running_loss += loss.item();
    }
    std::cout << "Loss: " << running_loss / train_loader.size() << std::endl;
  }

  auto model = std::make_shared<NeuralNet>();
  torch::save(model, "model.pt");
  return 0;
}
