#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <chrono>

#include "../functions.h"

void dynamicProgramming(const Truck &truck, const std::vector<Pallet> &pallets)
{
    int weightMax = truck.capacity;
}


unsigned int knapsackDP(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    unsigned int maxValue[100][101]; // Assumindo n <= 100, maxWeight <= 100

    for(unsigned int k = 0; k <= maxWeight; k++) {
        maxValue[0][k] = (k >= weights[0]) ? values[0] : 0;
    }

    for(unsigned int i = 1; i <= n; i++) {
        maxValue[i][0] = 0;
    }

    for(unsigned int i = 1; i < n; i++) {
        for(unsigned int k = 1; k <= maxWeight; k++) {
            if(k < weights[i]) {
                maxValue[i][k] = maxValue[i - 1][k];
            } else {
                unsigned int withItem = maxValue[i - 1][k - weights[i]] + values[i];
                unsigned int withoutItem = maxValue[i - 1][k];
                maxValue[i][k] = std::max(withItem, withoutItem);
            }
        }
    }

    for(unsigned int i = 0; i < n; i++) {
        usedItems[i] = false;
    }

    unsigned int remainingWeight = maxWeight;
    for(int i = n - 1; i > 0; i--) {
        if(maxValue[i][remainingWeight] != maxValue[i - 1][remainingWeight]) {
            usedItems[i] = true;
            remainingWeight -= weights[i];
        }
    }

    if(remainingWeight >= weights[0] && maxValue[0][remainingWeight] > 0) {
        usedItems[0] = true;
    }

    return maxValue[n - 1][maxWeight];
}

void knapsackDPTruck(const Truck &truck, const std::vector<Pallet> &pallets)
{
    std::cout << "\n=== Algoritmo Programação Dinâmica ===\n";
    auto start = std::chrono::high_resolution_clock::now();

    unsigned int n = static_cast<unsigned int>(pallets.size());
    unsigned int maxWeight = truck.capacity;

    unsigned int values[100], weights[100];
    bool usedItems[100];

    for (unsigned int i = 0; i < n; ++i) {
        values[i] = pallets[i].profit;
        weights[i] = pallets[i].weight;
    }

    unsigned int maxProfit = knapsackDP(values, weights, n, maxWeight, usedItems);

    std::cout << "Lucro máximo possível: " << maxProfit << "\n";
    std::cout << "Paletes selecionadas:\n";

    for (unsigned int i = 0; i < n; ++i) {
        if (usedItems[i]) {
            std::cout << "  Pallet ID: " << pallets[i].pallet
                      << " | Peso: " << pallets[i].weight
                      << " | Lucro: " << pallets[i].profit << "\n";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Tempo de execução: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}