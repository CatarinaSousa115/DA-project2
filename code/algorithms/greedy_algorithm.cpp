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

/**
 * @brief Solves the 0/1 knapsack problem using a greedy heuristic.
 *
 * Sorts pallets by profit-to-weight ratio and selects as many as fit within
 * the truck's capacity. This does not guarantee an optimal solution but is efficient.
 *
 * @param truck The truck object with a defined capacity.
 * @param pallets The list of available pallets with weight and profit.
 *
 * @note Time complexity: O(n log n), where n is the number of pallets (due to sorting).
 * @note Space complexity: O(n), for storing sorted and selected pallets.
 */
void greedyAlgorithm(const Truck &truck, const std::vector<Pallet> &pallets)
{
    std::cout << "\n=== Greedy Algorithm ===\n";
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

    std::cout << "Maximum profit: " << maxProfit << "\n";

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Execution time: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms\n";
    printPalletDetails(usedPallets, pallets, truck);
}

/**
 * @brief Sorts pallets in descending order of profit-to-weight ratio.
 *
 * This function is used to prioritize pallets that provide the highest profit per unit of weight,
 * which is essential for the greedy approach to the 0/1 knapsack problem.
 * In case of ties, pallets are sorted by descending weight, and then ascending pallet ID.
 *
 * @param pallets Vector of pallets to be sorted.
 */
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

/**
 * @brief Sorts pallets by their palletID in ascending order.
 *
 * This is used to maintain consistent order when displaying pallets.
 *
 * @param pallets Vector of pallets to be sorted.
 */
void sortPallets(std::vector<Pallet> &pallets)
{
    std::sort(pallets.begin(), pallets.end(), [](const Pallet &pallet1, const Pallet &pallet2)
              { return pallet1.palletID < pallet2.palletID; });
}