#include "../include/quadtree.h"

#include <cassert>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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

  Race* coordinate1 = qt.nearestNeighbor(-117.8827, 33.8823); // Fullerton, CA
  assert(coordinate1->name == "Las Vegas Grand Prix");

  Race* coordinate2 = qt.nearestNeighbor(-0.1276, 51.5072); // London, UK
  assert(coordinate2->name == "British Grand Prix");

  Race* coordinate3 = qt.nearestNeighbor(2.3522, 48.8566); // Paris, France
  assert(coordinate3->name == "Belgian Grand Prix");

  Race* coordinate4 = qt.nearestNeighbor(13.4050, 52.5200); // Berlin, Germany
  assert(coordinate4->name == "Belgian Grand Prix");

  Race* coordinate5 = qt.nearestNeighbor(18.4241, -33.9249); // Cape Town, South Africa
  assert(coordinate5->name == "Brazilian Grand Prix");

  Race* coordinate6 = qt.nearestNeighbor(151.2093, -33.8688); // Sydney, Australia
  assert(coordinate6->name == "Australian Grand Prix");

  Race* coordinate7 = qt.nearestNeighbor(121.4737, 31.2304); // Shanghai, China
  assert(coordinate7->name == "Japanese Grand Prix");

  Race* coordinate8 = qt.nearestNeighbor(139.6917, 35.6895); // Tokyo, Japan
  assert(coordinate8->name == "Japanese Grand Prix");

  Race* coordinate9 = qt.nearestNeighbor(-58.3816, -34.6037); // Buenos Aires, Argentina
  assert(coordinate9->name == "Brazilian Grand Prix");

  Race* coordinate10 = qt.nearestNeighbor(-99.1332, 19.4326); // Mexico City, Mexico
  assert(coordinate10->name == "Mexican Grand Prix");

  Race* coordinate11 = qt.nearestNeighbor(-74.0059, 40.7128); // New York City, USA
  assert(coordinate11->name == "Canadian Grand Prix");

  Race* coordinate12 = qt.nearestNeighbor(-0.0917, 51.5155); // London City Centre, UK
  assert(coordinate12->name == "British Grand Prix");

  Race* coordinate13 = qt.nearestNeighbor(2.2945, 48.8584); // Paris City Centre, France
  assert(coordinate13->name == "Belgian Grand Prix");

  Race* coordinate14 = qt.nearestNeighbor(18.0575, 59.3293); // Stockholm, Sweden
  assert(coordinate14->name == "Dutch Grand Prix");

  Race* coordinate15 = qt.nearestNeighbor(10.7461, 59.9127); // Oslo, Norway
  assert(coordinate15->name == "Dutch Grand Prix");

  Race* coordinate16 = qt.nearestNeighbor(28.0339, 1.6596); // Bucharest, Romania
  assert(coordinate16->name == "Saudi Arabian Grand Prix");

  Race* coordinate17 = qt.nearestNeighbor(12.4964, 41.9028); // Rome, Italy
  assert(coordinate17->name == "Italian Grand Prix Ferrari");

  Race* coordinate18 = qt.nearestNeighbor(-9.1393, 38.7223); // Lisbon, Portugal
  assert(coordinate18->name == "Spanish Grand Prix");

  Race* coordinate19 = qt.nearestNeighbor(-3.7038, 40.4168); // Madrid, Spain
  assert(coordinate19->name == "Spanish Grand Prix");

  Race* coordinate20 = qt.nearestNeighbor(-79.3832, 43.6532); // Toronto, Canada
  assert(coordinate20->name == "Canadian Grand Prix");

  Race* coordinate21 = qt.nearestNeighbor(72.8777, 19.0760); // Mumbai, India
  assert(coordinate21->name == "Abu Dhabi Grand Prix");

  std::cout << "Passed all tests!\n";

  return 0;
}