#include "../include/data_import.h"
#include "../include/quadtree.h"

#include <iostream>

int main() {
  QuadTree qt;
  float userLat;
  float userLong;
  importDataFromCSV("./data/formula1_grand_prix_2023.csv", qt);

  std::cout << "Welcome to Formula 1 Nearest Race Finder!\n"
              "This program helps you find the nearest Formula 1 "
              "race to your current location.\n" << std::endl;

  std::cout << "Please enter your current latitude: ";
  std::cin >> userLat;

  std::cout << "Please enter your current longitude: ";
  std::cin >> userLong;

  // TODO: Data validation - Check that user enters valid inputs
  //  that are within the correct range

  return 0;
}