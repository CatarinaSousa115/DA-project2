#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "functions.h"

Truck readTruckAndPallets(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Error opening file" << fileName << std::endl;
        return {};
    }

    std::string line;

    getline(file, line);

    Truck truck{};

    if (getline(file, line))
    {
        std::stringstream ss(line);
        std::string       value;

        getline(ss, value, ',');
        truck.capacity = std::stoi(value);
        
        getline(ss, value, ',');
        truck.numPallets = std::stoi(value);
    }

    file.close();

    return truck;
}