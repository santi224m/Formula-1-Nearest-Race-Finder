#ifndef DISTANCE_H
#define DISTANCE_H

#include <cmath>

// Convert degrees to radians
float toRadians(float degrees) {
  return degrees * M_PI / 180.0f;
}

// Calculate distance between two coordinates using Haversine formula
float calculateDistanc(float lat1, float lon1, float lat2, float  lon2) {
  // Convert latitude and longitude to radians
  float phi1 = toRadians(lat1);
  float phi2 = toRadians(lat2);
  float deltaPhi = toRadians(lat2 - lat1);
  float deltaLambda = toRadians(lon2 - lon1);

  // Apply Haversine formula
  float a = std::sin(deltaPhi / 2.0) * std::sin(deltaPhi / 2.0) +
            std::cos(phi1) * std::cos(phi2) *
            std::sin(deltaLambda / 2.0) * std::sin(deltaLambda / 2.0);
  float c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));
  float distance = 6371.0 * c;  // Earth's mean radius in kilometers

  return distance;
}

#endif // DISTANCE_H