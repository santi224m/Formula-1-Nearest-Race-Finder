#include "../include/data_import.h"

void importDataFromCSV(const std::string& file_path, QuadTree& qt) {
  std::ifstream csv_file(file_path);
  std::string line;
  std::vector<Race> races;

  while(std::getline(csv_file, line)) {
    std::istringstream ss(line);
    std::string race_name, circuit_name, lat_str, lon_str, date;
    std::getline(ss, race_name, ',');
    std::getline(ss, circuit_name, ',');
    std::getline(ss, lat_str, ',');
    std::getline(ss, lon_str, ',');
    std::getline(ss, date, ',');
    float latitude = std::stod(lat_str);
    float longitude = std::stod(lon_str);

    // Parse time  into tm stuct
    std::tm parsedTime = {};
    std::istringstream tmss(date);
    tmss >> std::get_time(&parsedTime, "%Y-%m-%d");

    Race r(race_name, circuit_name, {latitude, longitude}, parsedTime);
    qt.insert(r);
  }
}