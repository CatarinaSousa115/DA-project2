#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "../functions.h"

Truck readTruckAndPallets(const std::string &fileName)
{
    // Opens the CSV file for reading
    std::ifstream file(fileName);
    // Check if the file opened successfully
    if (!file.is_open())
    {
        std::cerr << "Error opening file" << fileName << std::endl;
        return {};
    }

    std::string line;

    // Skip the header line
    getline(file, line);

    // Initialize an empty Truck struct
    Truck truck{};

    // Read the line containing truck data
    if (getline(file, line))
    {
        std::stringstream ss(line);
        std::string value;

        // Extract truck capacity
        getline(ss, value, ',');
        truck.capacity = std::stoi(value);

        // Extract number of pallets
        getline(ss, value, ',');
        truck.numPallets = std::stoi(value);
    }

    file.close();

    // Return the filled Truck struct
    return truck;
}