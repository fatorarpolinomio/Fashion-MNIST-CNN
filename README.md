# Fashion-MNIST-CNN

Projeto de faculdade, que diz respeito à implementação de uma Convolutional Neural Network (CNN) a qual utilizará como conjunto de dados para treino/teste o Fashion MNIST.

## Liguagem e Tecnologia de compilação

- **C++**: Linguagem de programação utilizada para implementar a CNN.
- **CMake**: Sistema de construção utilizado para gerenciar o build do projeto.

### **Instalação do CMake:**

- **Windows**: [Download](https://cmake.org/download/).
- **MacOS**: `brew install cmake`.
- **Linux**: `sudo apt-get install cmake`.
- **Arch Linux**: `sudo pacman -S cmake`

### **Compilando/Rodando**

Para compilar o projeto, siga os passos abaixo:

Abra o terminal na pasta do projeto e rode estes comandos em sequência:

```sh
# 1. Cria a pasta de compilação e entra nela
mkdir build && cd build

# 2. Pede pro CMake ler o CMakeLists.txt e preparar o ambiente
cmake ..

# 3. Compila o seu código (o equivalente ao 'make', mas mais moderno)
cmake --build .
```

Se tudo der certo, o CMake chegará em [100%] Built target trabalho_cnn.

Agora, basta executar o programa:

```sh
# 4. Executa o seu programa
./trabalho_cnn
```

## LibTorch

Biblioteca para trabalhar com CNN e aprendizado profundo.

**Instalação para Windows:**

Acesse o site oficial do [PyTorch](https://pytorch.org/).

Selecione: PyTorch Build (Stable) -> Sua OS (Windows) -> Package (LibTorch) -> C++ / Java -> Compute Platform (CPU ou CUDA).

Baixe o arquivo .zip (Release ou Debug - Aviso: No Windows, você não pode misturar bibliotecas Release com seu projeto em Debug).

Extraia na raiz do seu disco, por exemplo: C:\libtorch.

**Instalação para MacOS:**

O pacote do PyTorch no Homebrew já inclui os cabeçalhos C++ nativamente.

Comando:

```sh
brew install pytorch
```

**Linux (Ubuntu/Debian):**

Caso você instale dessa maneira (que é a principal), não deixe de alterar as flags em `compile_flags.txt` e no script em **CMake** para conectar a biblioteca. Em ambos, é necessário colocar o caminho até o local onde está a sua pasta `LibTorch`. No arquivo `CMakeLists.txt`, você pode alterar o caminho que está por volta da linha 12.

Comando:

```sh
wget https://download.pytorch.org/libtorch/cpu/libtorch-cxx11-abi-shared-with-deps-2.2.0%2Bcpu.zip
sudo unzip libtorch-cxx11-abi-shared-with-deps-2.2.0+cpu.zip -d /opt/
```

**Arch Linux:**

Rode o comando:

```sh
yay -S libtorch-cpu
```

## MatLib++

Biblioteca para produção de gráficos para visualização de dados.

**Instalação para Windows:**

Instale o Gnuplot (o motor de renderização do Matplot++):

```sh
winget install Gnuplot
```

Usando o vcpkg no terminal, instale o Matplot++:

```sh
vcpkg install matplotplusplus:x64-windows
```

**Instalação para MacOS:**

Instale o Gnuplot (o motor de renderização do Matplot++):

```sh
brew install gnuplot
```

**Linux (Ubuntu/Debian):**

Rode os comandos:

```sh
sudo apt update
sudo apt install gnuplot
```

**Arch Linux:**

Rode o comando:

```sh
sudo pacman -S gnuplot
```
