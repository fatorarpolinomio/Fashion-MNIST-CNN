# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/lucas/Documentos/Faculdade/Quinto_semestre/IA/Fashion-MNIST-CNN/src/build/_deps/matplotplusplus-src")
  file(MAKE_DIRECTORY "/home/lucas/Documentos/Faculdade/Quinto_semestre/IA/Fashion-MNIST-CNN/src/build/_deps/matplotplusplus-src")
endif()
file(MAKE_DIRECTORY
  "/home/lucas/Documentos/Faculdade/Quinto_semestre/IA/Fashion-MNIST-CNN/src/build/_deps/matplotplusplus-build"
  "/home/lucas/Documentos/Faculdade/Quinto_semestre/IA/Fashion-MNIST-CNN/src/build/_deps/matplotplusplus-subbuild/matplotplusplus-populate-prefix"
  "/home/lucas/Documentos/Faculdade/Quinto_semestre/IA/Fashion-MNIST-CNN/src/build/_deps/matplotplusplus-subbuild/matplotplusplus-populate-prefix/tmp"
  "/home/lucas/Documentos/Faculdade/Quinto_semestre/IA/Fashion-MNIST-CNN/src/build/_deps/matplotplusplus-subbuild/matplotplusplus-populate-prefix/src/matplotplusplus-populate-stamp"
  "/home/lucas/Documentos/Faculdade/Quinto_semestre/IA/Fashion-MNIST-CNN/src/build/_deps/matplotplusplus-subbuild/matplotplusplus-populate-prefix/src"
  "/home/lucas/Documentos/Faculdade/Quinto_semestre/IA/Fashion-MNIST-CNN/src/build/_deps/matplotplusplus-subbuild/matplotplusplus-populate-prefix/src/matplotplusplus-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/lucas/Documentos/Faculdade/Quinto_semestre/IA/Fashion-MNIST-CNN/src/build/_deps/matplotplusplus-subbuild/matplotplusplus-populate-prefix/src/matplotplusplus-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/lucas/Documentos/Faculdade/Quinto_semestre/IA/Fashion-MNIST-CNN/src/build/_deps/matplotplusplus-subbuild/matplotplusplus-populate-prefix/src/matplotplusplus-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
