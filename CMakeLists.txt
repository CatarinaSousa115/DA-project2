cmake_minimum_required(VERSION 3.29)
project(DA_project2)

set(CMAKE_CXX_STANDARD 14)

add_executable(DA_project2
    code/main.cpp
    code/read_Pallets_csv.cpp
    code/read_TruckAndPallets_csv.cpp
    )
