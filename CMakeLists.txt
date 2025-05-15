cmake_minimum_required(VERSION 3.29)
project(DA_project2)

set(CMAKE_CXX_STANDARD 14)

add_executable(DA_project2
    code/brute_force.cpp
    code/dynamic_programming.cpp
    code/main.cpp
    code/menu.cpp
    code/printPalletDetails.cpp
    code/read_Pallets_csv.cpp
    code/read_TruckAndPallets_csv.cpp
    code/restartOrExit.cpp
    )
