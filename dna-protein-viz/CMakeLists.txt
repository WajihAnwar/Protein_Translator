cmake_minimum_required(VERSION 3.10)
project(dna-protein-viz LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/model/codon_table.cpp
    src/model/sequence.cpp
    src/model/translator.cpp
    src/model/fasta_parser.cpp
    src/controller/app_controller.cpp
    src/view/visualizer.cpp
)

add_executable(dna-protein-viz ${SOURCES})

target_include_directories(dna-protein-viz PRIVATE include)
