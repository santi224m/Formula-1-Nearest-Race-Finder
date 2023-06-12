#include "../include/data_import.h"
#include "../include/input_validation.h"
#include "../include/quadtree.h"
#include "../include/race.h"

#include <iostream>

int main() {
  const float MIN_LAT = -90.0;
  const float MAX_LAT = 90.0;
  const float MIN_LON = -180.0;
  const float MAX_LON = 180.0;

  // Initialize quadtreee and add data from csv file
  QuadTree qt;
  importDataFromCSV("./data/formula1_grand_prix_2023.csv", qt);

  std::cout << "Welcome to Formula 1 Nearest Race Finder!\n"
              "This program helps you find the nearest Formula 1 "
              "race to your current location.\n" << std::endl;

  while (true) {
    // Prompt user for latitude
    float userLat;
    inputValidation("Please enter your current latitude: ", userLat, MIN_LAT, MAX_LAT);

    // Prompt user for longitude
    float userLong;
    inputValidation("Please enter your current longitude: ", userLong, MIN_LON, MAX_LON);

    std::cout << "\nFinding the nearest race...\n" << std::endl;

    Race* nearestRace = qt.nearestNeighbor(userLong, userLat);

    std::cout << "The nearest race to your location is:\n" << std::endl;
    std::cout << "Race: " << nearestRace->name << std::endl;
    std::cout << "Circuit: " << nearestRace->circuit << std::endl;
    std::cout << "Date: ";
    nearestRace->PrintDate();
    std::cout << std::endl;
    std::cout << "Coordinates: [" << nearestRace->coordinate.latitude
          << ", " << nearestRace->coordinate.longitude << "]" << std::endl;

    std::cout << "Would you like to find another race? (yes/NO): ";
    std::string continueProgram;
    std::cin >> continueProgram;
    if (continueProgram != "yes") {
      break;
    }
  }

  std::cout << "Thank you for using the F1 Nearest Race Finder. Goodbye!"
        << std::endl;

  return 0;
}