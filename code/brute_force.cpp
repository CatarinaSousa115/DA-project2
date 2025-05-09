#include <iostream>
#include <cmath>
#include <vector>
#include "functions.h"

/**
 * @complexity O(n × 2^n)
 */

void bruteForce(const Truck &truck, const std::vector<Pallet> &pallets)
{
    std::cout << "\n=== Brute-force Algorithm ===\n";
    if (truck.numPallets >= 20)
    {
        std::cout << "The number of pallets is too high for the brute-force algorithm.\n";
        std::cout << "You really want to use this algorithm? (y/n): ";
        char choice;
        std::cin >> choice;

        while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
        {
            std::cout << "\nInvalid option. Please choose between y and n: ";
            std::cin >> choice;
        }
        if (choice == 'n' || choice == 'N')
        {
            std::cout << "\nPlease choose another algorithm.\n";
            chooseAlgorithm(truck, pallets);
        }
        else if (choice == 'y' || choice == 'Y')
        {
            std::cout << "\nThis algorithm may take a considerable amount of time to run.\n";
            std::cout << "Please wait!\n";
        }
    }

    int max = 0;
    int numSubSet = pow(2, truck.numPallets);
    std::vector<int> bestPallets;

    for (int i = 0; i < numSubSet; i++)
    {
        int totalWeight = 0;
        int totalProfit = 0;
        std::vector<int> selectedPallets;

        for (int j = 0; j < truck.numPallets; j++)
        {
            if (i & (1 << j))
            {
                totalWeight += pallets[j].weight;
                totalProfit += pallets[j].profit;
                selectedPallets.push_back(pallets[j].pallet);
            }
        }

        if (totalWeight <= truck.capacity && totalProfit >= max && bestPallets.size() > selectedPallets.size())
        {
            max = totalProfit;
            bestPallets = selectedPallets;
        }
        else if (totalWeight <= truck.capacity && totalProfit > max)
        {
            max = totalProfit;
            bestPallets = selectedPallets;
        }
    }

    for (int i : bestPallets)
    {
        for (Pallet pallet : pallets)
        {
            if (pallet.pallet == i)
            {
                std::cout << pallet.pallet << ", " << pallet.weight << ", " << pallet.profit << "\n";
            }
        }
    }
    std::cout << "\n";

    std::cout << "Do you want test another algorithm? (y/n): ";
    char choice;
    std::cin >> choice;
    while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
    {
        std::cout << "\nInvalid option. Please choose between y and n: ";
        std::cin >> choice;
    }
    if (choice == 'y' || choice == 'Y')
    {
        main();
    }
    else if (choice == 'n' || choice == 'N')
    {
        std::cout << "\nThank you for using the program!\n";
        exit(0);
    }
}