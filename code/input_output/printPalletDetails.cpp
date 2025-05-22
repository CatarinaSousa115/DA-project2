#include <iostream>
#include "../functions.h"

void printPalletDetails(const std::vector<Pallet> &bestPallets, const std::vector<Pallet> &pallets, const Truck &truck)
{
    for (Pallet pallet : bestPallets)
    {
        std::cout << pallet.palletID << ", " << pallet.weight << ", " << pallet.profit << "\n";
    }

    promptRestartOrExit(truck, pallets);
}
