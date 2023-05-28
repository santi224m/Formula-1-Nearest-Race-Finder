#include "../include/race.h"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

int main() {
  std::ifstream csv_file("../data/formula1_grand_prix_2023.csv");
  std::string line;
  std::vector<Race> races;

  while(std::getline(csv_file,line)) {
    std::istringstream ss(line);
    std::string race_name, circuit_name, lat_str, lon_str, date;
    std::getline(ss, race_name, ',');
    std::getline(ss, circuit_name, ',');
    std::getline(ss, lat_str, ',');
    std::getline(ss, lon_str, ',');
    std::getline(ss, date, ',');
    double latitude = std::stod(lat_str);
    double longitude = std::stod(lon_str);

    // Pase time  into tm stuct
    std::tm parsedTime = {};
    std::istringstream tmss(date);
    tmss >> std::get_time(&parsedTime, "%Y-%m-%d");

    races.push_back(Race(race_name, circuit_name, {latitude, longitude}, parsedTime));
  }

  std::cout << "Races count: " << races.size() << std::endl;

  // Print out all races
  for (Race r : races) {
    std::cout << "====================\n";
    std::cout << "Name: " << r.name << std::endl;
    std::cout << "Circuit: " << r.circuit <<  std::endl;
    std::cout << "Coordinates: (" << r.coordinate.latitude << ", "
              << r.coordinate.longitude << ")" << std::endl;
    std::cout << "Date: ";
    r.PrintDate();
    std::cout << std::endl;
  }

  return 0;
}