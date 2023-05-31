#include "../include/quadtree.h"

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
  QuadTree qt;

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

    // Parse time  into tm stuct
    std::tm parsedTime = {};
    std::istringstream tmss(date);
    tmss >> std::get_time(&parsedTime, "%Y-%m-%d");
    
    Race r(race_name, circuit_name, {latitude, longitude}, parsedTime);
    qt.insert(r);
  }

  // Remove Italian GP
  qt.remove(11.7159,44.3449);
  // Remove British GP
  qt.remove(-1.0169,52.0786);

  std::tm t = {};
  t.tm_year = 2023;
  t.tm_mon = 10;
  t.tm_mday = 22;
  Race las_vegas_gp("Las Vegas Grand Prix", "Las Vegas", {36.1175, -115.1614}, t);

  qt.remove(las_vegas_gp);

  return 0;
}