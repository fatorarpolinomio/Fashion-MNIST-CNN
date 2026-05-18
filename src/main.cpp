#include <iostream>
#include <matplot/matplot.h>
#include <torch/torch.h>
#include <vector>

int main() {
  std::cout << "Iniciando teste do ambiente..." << std::endl;

  // ---------------------------------------------------------
  // Usando LibTorch para gerar dados matemáticos
  // Simulando uma curva de "loss" caindo ao longo de 100 épocas
  // ---------------------------------------------------------
  torch::Tensor epocas = torch::linspace(1, 100, 100);
  // Cria uma curva exponencial decrescente (ex: e^(-0.05 * x))
  torch::Tensor loss = torch::exp(-0.05 * epocas);

  std::cout << "Tensores gerados com sucesso pelo LibTorch!" << std::endl;

  // ---------------------------------------------------------
  // Ponte de conversão: LibTorch -> Matplot++
  // O Matplot++ não entende 'torch::Tensor'. Ele precisa de 'std::vector'.
  // Usamos data_ptr<float>() para extrair os números brutos da memória.
  // ---------------------------------------------------------
  std::vector<float> x_dados(epocas.data_ptr<float>(),
                             epocas.data_ptr<float>() + epocas.numel());

  std::vector<float> y_dados(loss.data_ptr<float>(),
                             loss.data_ptr<float>() + loss.numel());

  // ---------------------------------------------------------
  // Usando Matplot++ para desenhar o gráfico
  // ---------------------------------------------------------
  std::cout << "Abrindo a janela do gráfico com Matplot++..." << std::endl;

  matplot::plot(x_dados, y_dados)->line_width(2).color("blue");

  matplot::title("Simulacao de Loss da CNN");
  matplot::xlabel("Epocas");
  matplot::ylabel("Erro (Loss)");

  // Mostra o gráfico em uma janela interativa
  matplot::show();

  return 0;
}
