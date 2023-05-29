#include "../include/quadtree.h"

int main() {
  Coordinate c(30.1333, -97.6411);
  std::tm date = {};
  date.tm_year = 2023;
  date.tm_mon = 10;
  date.tm_mday = 22;
  Race USGP("United States Grand Prix", "Circuit of The Americas", c, date);
  QuadTree myTree;
  myTree.insert(USGP);

  return 0;
}