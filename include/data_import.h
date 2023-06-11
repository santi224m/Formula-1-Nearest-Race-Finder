#ifndef DATA_IMPORT_H
#define DATA_IMPORT_H

#include "./quadtree.h"
#include "./race.h"

#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

void importDataFromCSV(const std::string& file_path, QuadTree& qt);

#endif // DATA_IMPORT_H