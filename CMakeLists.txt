cmake_minimum_required(VERSION 3.29)
project(DA_project2)

set(CMAKE_CXX_STANDARD 14)

add_executable(DA_project2
    code/algorithms/bruteForce.cpp
    code/algorithms/dynamicProgramming.cpp
    code/algorithms/greedyAlgorithm.cpp
    code/algorithms/hybridAlgorithm.cpp
    code/input_output/printPalletDetails.cpp
    code/input_output/readPallets.cpp
    code/input_output/readTruckAndPallets.cpp
    code/main.cpp
    code/menu/menu.cpp
    code/menu/restartOrExit.cpp
    )
