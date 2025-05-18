cmake_minimum_required(VERSION 3.29)
project(DA_project2)

set(CMAKE_CXX_STANDARD 14)

add_executable(DA_project2
    code/algorithms/brute_force.cpp
    code/algorithms/dynamic_programming.cpp
    code/menu/main.cpp
    code/menu/menu.cpp
    code/input_output/printPalletDetails.cpp
    code/input_output/read_Pallets_csv.cpp
    code/input_output/read_TruckAndPallets_csv.cpp
    code/menu/restartOrExit.cpp
    )
