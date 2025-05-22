#include <iostream>
#include "../functions.h"

void printPalletDetails(const std::vector<Pallet> &bestPallets, const std::vector<Pallet> &pallets, const Truck &truck)
{
    std::cout << "-------------------- PALLETS: --------------------\n";

    std::cout << "           ┌────────┬────────┬────────┐\n";
    std::cout << "           │ Pallet │ Weight │ Profit │\n";
    std::cout << "           ├────────┼────────┼────────┤\n";

    for (Pallet pallet : bestPallets)
    {
        std::string palletID = std::to_string(pallet.palletID);
        std::string weight = std::to_string(pallet.weight);
        std::string profit = std::to_string(pallet.profit);
        while (palletID.length() < 6)
        {
            if (palletID.length() == 5)
            {
                palletID = " " + palletID;
            }
            else
            {
                palletID = " " + palletID + " ";
            }
        }
        while (weight.length() < 6)
        {
            if (weight.length() == 5)
            {
                weight = " " + weight;
            }
            else
            {
                weight = " " + weight + " ";
            }
        }
        while (profit.length() < 6)
        {
            if (profit.length() == 5)
            {
                profit = " " + profit;
            }
            else
            {
                profit = " " + profit + " ";
            }
        }

        std::cout << "           │ " << palletID << " │ " << weight << " │ " << profit << " │" << "\n";
    }

        std::cout << "           └────────┴────────┴────────┘\n";

    promptRestartOrExit(truck, pallets);
}
