#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "functions.h"

std::vector<Pallet> readPallets(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Error opening file" << fileName << std::endl;
        return {};
    }

    std::string line;

    getline(file, line);

    Pallet pallet{};

    std::vector<Pallet> pallets;

    while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string value;

        getline(ss, value, ',');
        pallet.pallet = std::stoi(value);

        getline(ss, value, ',');
        pallet.weight = std::stoi(value);

        getline(ss, value, ',');
        pallet.profit = std::stoi(value);

        pallets.push_back(pallet);
    }
    file.close();

    return pallets;
}