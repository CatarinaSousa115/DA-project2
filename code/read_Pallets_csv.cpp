#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "functions.h"

/**
 * @brief Reads pallet data from a CSV file.
 *
 * This function opens a CSV file, skips the header, and reads each line
 * to extract pallet ID, weight, and profit. It returns a vector of Pallet objects.
 *
 * @param fileName The name of the CSV file to read.
 * @return std::vector<Pallet> List of pallets read from the file.
 */
std::vector<Pallet> readPallets(const std::string &fileName)
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

    // Initialize an empty vector to store pallets
    std::vector<Pallet> pallets;

    // Read each line of the CSV and extract pallet data
    while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string value;
        Pallet pallet{};

        // Extract pallet ID
        getline(ss, value, ',');
        pallet.pallet = std::stoi(value);

        // Extract pallet weight
        getline(ss, value, ',');
        pallet.weight = std::stoi(value);

        // Extract pallet profit
        getline(ss, value, ',');
        pallet.profit = std::stoi(value);

        // Add the extracted pallet to the list
        pallets.push_back(pallet);
    }

    file.close();

    // Return the vector of pallets read from the file
    return pallets;
}