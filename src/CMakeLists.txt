cmake_minimum_required(VERSION 3.15)
project(TrabalhoCNN CXX)

# Exigir C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------------------------------------
# 1. Configurando o LibTorch (Caminho do AUR)
# ---------------------------------------------------------
# Avisa o CMake onde procurar a configuração do PyTorch
list(APPEND CMAKE_PREFIX_PATH "/opt/libtorch")

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# ---------------------------------------------------------
# 2. Configurando o Matplot++ (Via FetchContent)
# ---------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
    matplotplusplus
    GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
    GIT_TAG        origin/master
)
FetchContent_MakeAvailable(matplotplusplus)

# ---------------------------------------------------------
# 3. Criando o executável e linkando tudo
# ---------------------------------------------------------
add_executable(trabalho_cnn main.cpp)

target_link_libraries(trabalho_cnn
    PRIVATE
    ${TORCH_LIBRARIES}
    matplot
)
