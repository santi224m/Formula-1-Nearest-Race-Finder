#ifndef RACE_H
#define RACE_H

#include <ctime>
#include <string>

struct Coordinate;

struct Race {
  std::string name;
  std::string circuit;
  Coordinate coordinate;
  std::tm date;
};

struct Coordinate {
  double latitude;
  double longitude;
};

#endif  // RACE_H