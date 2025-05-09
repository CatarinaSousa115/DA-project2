#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#include <string>
#include <vector>
#include "Truck.h"
#include "Pallet.h"

Truck readTruckAndPallets(const std::string &fileName);

std::vector<Pallet> readPallets(const std::string &fileName);

int main();

void displayMenu();

void chooseAlgorithm(const Truck &truck, const std::vector<Pallet> &pallets);

void bruteForce(const Truck &truck, const std::vector<Pallet> &pallets);

#endif