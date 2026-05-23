#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

// Arquivos gerados:
//   1. hiperparametros.csv  - arquitetura e hiperparâmetros de treinamento
//   2. pesos_iniciais.csv   - pesos antes do treinamento
//   3. pesos_finais.csv     - pesos após o treinamento
//   4. loss_por_epoca.csv   - loss registrado a cada época
//   5. saidas_teste.csv     - predições vs rótulos reais no conjunto de teste

struct Hiperparametros {
    // Arquitetura
    
    int    canais_entrada   = 1;
    int    num_classes      = 10;
    int    conv1_filtros    = 32;
    int    conv1_kernel     = 3;
    int    conv2_filtros    = 64;
    int    conv2_kernel     = 3;
    int    pool_kernel      = 2;
    int    pool_stride      = 2;
    int    fc1_neuronios    = 128;
    int    fc2_neuronios    = 64;

    std::string ativacao_conv  = "ReLU";
    std::string ativacao_dense = "ReLU";
    std::string ativacao_saida = "LogSoftmax";

    // Treinamento

    float  taxa_aprendizado = 0.001f;
    int    epocas           = 10;
    int    batch_size       = 64;
    float  dropout_rate     = 0.5f;
    std::string otimizador  = "Adam";
    std::string funcao_loss = "NLLLoss";

    // Divisão dos dados

    float  fracao_treino    = 0.8f;
    float  fracao_val       = 0.1f;
    float  fracao_teste     = 0.1f;
};

// Pesos de uma camada. Pesos em ordem row-major; um bias por neurônio/filtro de saída.

struct CamadaPesos {
    std::string        nome;
    int                linhas;
    int                colunas;
    std::vector<float> pesos;
    std::vector<float> biases;
};

// Resultado de uma amostra no conjunto de teste.

struct ResultadoTeste {
    int                indice_amostra;
    int                rotulo_real;
    int                rotulo_predito;
    float              confianca;
    std::vector<float> probabilidades;
};

class IOManager {
public:
    explicit IOManager(const std::string& diretorio_saida = "resultados/")
        : dir_(diretorio_saida)
    {
        fs::create_directories(dir_);
        std::cout << "[IOManager] Diretório de saída: "
                  << fs::absolute(dir_) << "\n";
    }

    // Salva hiperparâmetros em CSV de duas colunas (parametro, valor).

    void salvar_hiperparametros(const Hiperparametros& hp) const {
        const auto caminho = dir_ / "hiperparametros.csv";
        std::ofstream f(caminho);
        if (!f.is_open()) {
            std::cerr << "[IOManager] ERRO: não foi possível abrir " << caminho << "\n";
            return;
        }

        f << "parametro,valor\n";
        f << "canais_entrada,"   << hp.canais_entrada   << "\n";
        f << "num_classes,"      << hp.num_classes       << "\n";
        f << "conv1_filtros,"    << hp.conv1_filtros     << "\n";
        f << "conv1_kernel,"     << hp.conv1_kernel      << "\n";
        f << "conv2_filtros,"    << hp.conv2_filtros     << "\n";
        f << "conv2_kernel,"     << hp.conv2_kernel      << "\n";
        f << "pool_kernel,"      << hp.pool_kernel       << "\n";
        f << "pool_stride,"      << hp.pool_stride       << "\n";
        f << "fc1_neuronios,"    << hp.fc1_neuronios     << "\n";
        f << "fc2_neuronios,"    << hp.fc2_neuronios     << "\n";
        f << "ativacao_conv,"    << hp.ativacao_conv     << "\n";
        f << "ativacao_dense,"   << hp.ativacao_dense    << "\n";
        f << "ativacao_saida,"   << hp.ativacao_saida    << "\n";
        f << "taxa_aprendizado," << hp.taxa_aprendizado  << "\n";
        f << "epocas,"           << hp.epocas            << "\n";
        f << "batch_size,"       << hp.batch_size        << "\n";
        f << "dropout_rate,"     << hp.dropout_rate      << "\n";
        f << "otimizador,"       << hp.otimizador        << "\n";
        f << "funcao_loss,"      << hp.funcao_loss       << "\n";
        f << "fracao_treino,"    << hp.fracao_treino     << "\n";
        f << "fracao_val,"       << hp.fracao_val        << "\n";
        f << "fracao_teste,"     << hp.fracao_teste      << "\n";

        std::cout << "[IOManager] Hiperparâmetros salvos em: " << caminho << "\n";
    }

    // Salva pesos e biases de cada camada em CSV.
    // Formato por linha: nome_camada, tipo (pesos|biases), linhas, colunas, v0, v1, ...

    void salvar_pesos(const std::vector<CamadaPesos>& camadas,
                      const std::string& nome_arquivo) const
    {
        const auto caminho = dir_ / nome_arquivo;
        std::ofstream f(caminho);
        if (!f.is_open()) {
            std::cerr << "[IOManager] ERRO: não foi possível abrir " << caminho << "\n";
            return;
        }

        f << "camada,tipo,linhas,colunas,valores...\n";

        for (const auto& camada : camadas) {
            f << camada.nome << ",pesos," << camada.linhas << "," << camada.colunas;
            for (float v : camada.pesos)
                f << "," << std::fixed << std::setprecision(8) << v;
            f << "\n";

            if (!camada.biases.empty()) {
                f << camada.nome << ",biases,1," << camada.biases.size();
                for (float b : camada.biases)
                    f << "," << std::fixed << std::setprecision(8) << b;
                f << "\n";
            }
        }

        int total = 0;
        for (const auto& c : camadas)
            total += (int)c.pesos.size() + (int)c.biases.size();

        std::cout << "[IOManager] Pesos salvos em: " << caminho
                  << " (" << camadas.size() << " camadas, " << total << " parâmetros)\n";
    }

    // Registra a loss de uma época. Deve ser chamada ao final de cada época.
    // Usa append - não reescreve o arquivo inteiro a cada chamada.

    void registrar_loss(int   epoca,
                        float loss_treino,
                        float loss_val     = -1.0f,
                        float acuracia_val = -1.0f)
    {
        const auto caminho = dir_ / "loss_por_epoca.csv";

        if (epoca == 1) { // Cabeçalho apenas na primeira época
            std::ofstream f(caminho);
            f << "epoca,loss_treino,loss_val,acuracia_val\n";
        }

        std::ofstream f(caminho, std::ios::app);
        if (!f.is_open()) {
            std::cerr << "[IOManager] ERRO: não foi possível abrir " << caminho << "\n";
            return;
        }

        f << std::fixed << std::setprecision(6) << epoca << "," << loss_treino << ",";
        if (loss_val     >= 0) f << loss_val;
        f << ",";
        if (acuracia_val >= 0) f << acuracia_val;
        f << "\n";

        std::cout << "[IOManager] Época " << std::setw(4) << epoca
                  << " | loss_treino: " << std::setw(10) << std::setprecision(6) << loss_treino;
        if (loss_val     >= 0) std::cout << " | loss_val: " << std::setw(10) << loss_val;
        if (acuracia_val >= 0) std::cout << " | acuracia_val: " << std::setprecision(2) << acuracia_val << "%";
        std::cout << "\n";
    }

    // Salva predições do conjunto de teste em CSV.
    // Colunas: indice, rotulo_real, nome_real, rotulo_predito, nome_predito,
    //          acerto, confianca, prob_classe_0, ..., prob_classe_N

    void salvar_saidas_teste(
        const std::vector<ResultadoTeste>& resultados,
        const std::vector<std::string>&    nomes_classes = {}) const
    {
        const auto caminho = dir_ / "saidas_teste.csv";
        std::ofstream f(caminho);
        if (!f.is_open()) {
            std::cerr << "[IOManager] ERRO: não foi possível abrir " << caminho << "\n";
            return;
        }

        f << "indice,rotulo_real,nome_real,rotulo_predito,nome_predito,acerto,confianca";
        if (!resultados.empty() && !resultados[0].probabilidades.empty()) {
            for (int c = 0; c < (int)resultados[0].probabilidades.size(); ++c) {
                f << ",prob_classe_" << c;
                if (c < (int)nomes_classes.size())
                    f << "(" << nomes_classes[c] << ")";
            }
        }
        f << "\n";

        int acertos = 0;
        for (const auto& r : resultados) {
            const bool acerto = (r.rotulo_real == r.rotulo_predito);
            if (acerto) ++acertos;

            f << std::fixed << std::setprecision(6)
              << r.indice_amostra << ","
              << r.rotulo_real    << "," << nome_classe_(r.rotulo_real,    nomes_classes) << ","
              << r.rotulo_predito << "," << nome_classe_(r.rotulo_predito, nomes_classes) << ","
              << (acerto ? 1 : 0) << "," << r.confianca;

            for (float p : r.probabilidades)
                f << "," << p;
            f << "\n";
        }

        if (!resultados.empty()) {
            float acuracia = 100.0f * acertos / (int)resultados.size();
            std::cout << "[IOManager] Saídas de teste salvas em: " << caminho
                      << "\n           Amostras: " << resultados.size()
                      << " | Acertos: "  << acertos
                      << " | Acurácia: " << std::fixed << std::setprecision(2) << acuracia << "%\n";
        }
    }

    // Constrói um ResultadoTeste a partir de probabilidades softmax.
    // Classe predita = índice de maior probabilidade.

    static ResultadoTeste criar_resultado(
        int                       indice,
        int                       rotulo_real,
        const std::vector<float>& probabilidades)
    {
        ResultadoTeste r;
        r.indice_amostra = indice;
        r.rotulo_real    = rotulo_real;
        r.probabilidades = probabilidades;
        r.rotulo_predito = (int)(std::max_element(
            probabilidades.begin(), probabilidades.end()) - probabilidades.begin());
        r.confianca      = probabilidades[r.rotulo_predito];
        return r;
    }

    fs::path diretorio() const { return dir_; }

private:
    fs::path dir_;

    static std::string nome_classe_(int indice, const std::vector<std::string>& nomes) {
        if (indice >= 0 && indice < (int)nomes.size())
            return nomes[indice];
        return "classe_" + std::to_string(indice);
    }
};