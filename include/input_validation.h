#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

#include <iostream>
#include <limits>
#include <string>

// Function for data validation of a single value within a specified range
template <typename T>
void inputValidation(const std::string& prompt, T& value, T minValue, T maxValue) {
  while (true) {
    std::cout << prompt;
    if (std::cin >> value && value >= minValue && value <= maxValue) {
      break;  // Valid input, exit loop
    } else {
      std::cout << "Invalid input. Please enter a value between " << minValue
                << " and " << maxValue << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}

#endif // INPUT_VALIDATION_H