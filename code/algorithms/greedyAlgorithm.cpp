/**
 * @file greedy_algorithm.cpp
 * @brief Implements the greedy algorithm for the 0/1 knapsack problem.
 *
 * Selects pallets based on the highest profit-to-weight ratio, adding them greedily
 * to the truck until the capacity is reached or no more pallets can be added.
 */
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <chrono>
#include <algorithm>

#include "../functions.h"

void greedyAlgorithm(const Truck &truck, const std::vector<Pallet> &pallets)
{
    std::cout << "\n╔════════════════════════════════════════════════╗\n";
    std::cout << "║                GREEDY ALGORITHM                ║\n";
    std::cout << "╚════════════════════════════════════════════════╝\n";
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<Pallet> usedPallets;

    if (pallets.empty() || truck.capacity <= 0)
    {
        std::cout << "No pallets available or 0 capacity" << std::endl;
        return;
    }

    std::vector<Pallet> sortedPallets = pallets;
    sortPallets_ratio(sortedPallets);

    int maxWeight = truck.capacity;
    int maxProfit = 0;
    int weight = 0;

    for (const Pallet &pallet : sortedPallets)
    {
        if (weight + pallet.weight <= maxWeight)
        {
            usedPallets.push_back(pallet);
            weight += pallet.weight;
            maxProfit += pallet.profit;
        }
    }

    sortPallets(usedPallets);
    
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Maximum profit: " << maxProfit << "\n";

    std::cout << "Number of pallets: " << usedPallets.size() << "\n";
    
    std::cout << "Execution time: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms\n";
              
              std::cout << "-------------------- PALLETS: --------------------\n";

    printPalletDetails(usedPallets, pallets, truck);
}

void sortPallets_ratio(std::vector<Pallet> &pallets)
{
    std::sort(pallets.begin(), pallets.end(), [](const Pallet &pallet1, const Pallet &pallet2)
              {
        double ratio1 = static_cast<double>(pallet1.profit) / pallet1.weight;
        double ratio2 = static_cast<double>(pallet2.profit) / pallet2.weight;
        if (ratio1 != ratio2) return ratio1 > ratio2;
        if (pallet1.weight != pallet2.weight) return pallet1.weight > pallet2.weight;
        return pallet1.palletID < pallet2.palletID; });
}

void sortPallets(std::vector<Pallet> &pallets)
{
    std::sort(pallets.begin(), pallets.end(), [](const Pallet &pallet1, const Pallet &pallet2)
              { return pallet1.palletID < pallet2.palletID; });
}