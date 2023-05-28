#ifndef RACE_H
#define RACE_H

#include <ctime>
#include <string>
#include <iostream>

struct Coordinate {
  double latitude;
  double longitude;

  // CTOR
  Coordinate(double lat, double lon) : latitude(lat), longitude(lon) {}
};

struct Race {
  std::string name;
  std::string circuit;
  Coordinate coordinate;
  std::tm date;

  // CTOR
  Race(const std::string& name, const std::string& circuit, 
       const Coordinate& coordinate, const std::tm& date)
    : name(name), circuit(circuit), coordinate(coordinate), date(date) {}

  void PrintDate() {
    std::cout << date.tm_mon + 1 << "-"
              << date.tm_mday << "-"
              << date.tm_year + 1900;
  }
};

#endif  // RACE_H