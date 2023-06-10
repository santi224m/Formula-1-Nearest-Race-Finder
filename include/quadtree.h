#ifndef  QUADTREE_H
#define  QUADTREE_H

#include "./race.h"

#include <cmath>
#include <limits>
#include <stdexcept>
#include <vector>

class QuadTreeNode {
 public:
  
  // CTOR
  QuadTreeNode() {
    for (size_t i = 0; i < 2; i++) {
      for (size_t  j = 0; j < 2; j++) {
        this->children_[i][j] = nullptr;
      }
    }
  }

  QuadTreeNode(float XMin, float XMax, float YMin, float YMax)
    : x_min_(XMin), x_max_(XMax), y_min_(YMin), y_max_(YMax)
  {
    for (size_t i = 0; i < 2; i++) {
      for (size_t  j = 0; j < 2; j++) {
        this->children_[i][j] = nullptr;
      }
    }
  }

  bool isLeaf() { return this->isLeaf_; }
  void setIsLeaf(bool val) { this->isLeaf_ = val; }
  int numPoints() { return this->numPoints_; }
  void setNumPoints(int num) { this->numPoints_ = num; }
  void incrementNumPoints() { this->numPoints_++; }
  void decrementNumPoints() { this->numPoints_--; }
  float XMin() { return this->x_min_; }
  void setXMin(float val)  { this->x_min_ = val; }
  float XMax() { return this->x_max_; }
  void setXMax(float val) { this->x_max_ = val; }
  float YMin() { return this->y_min_; }
  void setYMin(float val) { this->y_min_ = val; }
  float YMax() { return this->y_max_; }
  void setYMax(float val) { this->y_max_ = val; }
  QuadTreeNode* childrenAt(int i, int j) {
    return this->children_[i][j];
  }
  void setChildrenAt(int i, int j, QuadTreeNode* node) {
    this->children_[i][j] = node;
  }
  void addRace(Race& race) {
    this->races_.push_back(race);
  }
  std::vector<Race> getRaces() const { return races_; }
  void emptyRaces() { this->races_.clear(); }
  size_t getRacesSize() { return this->races_.size(); }
  double getRaceXAt(size_t i) { return this->races_[i].coordinate.longitude; }
  double getRaceYAt(size_t i) { return this->races_[i].coordinate.latitude; }

  // Remove Race at index i from races_ vector
  void removeRaceAt(size_t i) {
    this->races_.erase(this->races_.begin() + i);
  }

 private:
  bool isLeaf_ = true;
  int numPoints_ = 0;
  float x_min_ = -180.0;
  float x_max_ = 180.0;
  float y_min_ = -90.0;
  float y_max_ = 90.0;
  QuadTreeNode* children_[2][2];
  std::vector<Race> races_;
};

class QuadTree {
 public:
  // CTOR
  QuadTree() {
    this->rootNode = new QuadTreeNode();
  }

  void insert(Race& race) {
    double x = race.coordinate.longitude;
    double y = race.coordinate.latitude;
    // Check that race coordinates are within range
    if (x < this->rootNode->XMin() || x > this->rootNode->XMax())
      throw std::runtime_error("insert(): Race coordinated out-of-range");
    if (y < this->rootNode->YMin() || y > this->rootNode->YMax())
      throw std::runtime_error("insert(): Race coordinated out-of-range");
    this->nodeInsert(this->rootNode, race);
  }

  // Wrapper function for deleteNode function
  bool remove(double x, double y) {
    if (x < this->rootNode->XMin() || x > this->rootNode->XMax())
      return false;
    if (y < this->rootNode->YMin() || y > this->rootNode->YMax())
      return false;
    return this->deleteNode(this->rootNode,x,y);
  }

  bool deleteNode(QuadTreeNode* node, double x, double y) {
    if (node->isLeaf()) {
      for (size_t i = 0; i < node->getRacesSize(); i++) {
        if (node->getRaceXAt(i) == x && node->getRaceYAt(i) == y) {
          node->removeRaceAt(i);
          node->decrementNumPoints();
          return true;
        }
      }
      return false;
    }

    // Determine the bin where the race should be located
    float XBinSize = (node->XMax() - node->XMin()) / 2.0;
    float YBinSize = (node->YMax() - node->YMin()) / 2.0;
    int XBin = (x - node->XMin()) / XBinSize;
    int YBin = (y - node->YMin()) / YBinSize;

    if (node->childrenAt(XBin, YBin) == nullptr)
      return false;

    if (this->deleteNode(node->childrenAt(XBin, YBin), x, y)) {
      node->decrementNumPoints();
      if (node->childrenAt(XBin, YBin)->numPoints() == 0) {
        node->setChildrenAt(XBin, YBin, nullptr);
      }
      if (node->numPoints() <= 4) {
        std::vector<Race> tmp_races = this->collapseNode(node);
        for (Race r : tmp_races) {
          node->addRace(r);
        }
      }

      return true;
    }

    return false;
  }

  // Wrapper that passes along root node and initial infinite best distance
  Race* nearestNeighbor(float x, float y) {
    return this->nearestNeighborNode(this->rootNode, x, y, std::numeric_limits<float>::infinity());
  }

 private:
  void nodeInsert(QuadTreeNode* node, Race& race) {
    double x = race.coordinate.longitude;
    double y = race.coordinate.latitude;
    node->incrementNumPoints();

    // Determine into which bin to insert race
    float XBinSize = (node->XMax() - node->XMin()) / 2.0;
    float YBinSize = (node->YMax() - node->YMin()) / 2.0;
    int XBin = (x - node->XMin()) / XBinSize;
    int YBin = (y - node->YMin()) / YBinSize;

    // Add point to correct child
    if (!node->isLeaf()) {
      if (node->childrenAt(XBin, YBin) == nullptr) {
        QuadTreeNode* tmpNode = new QuadTreeNode(
          node->XMin() + XBin * XBinSize,
          node->XMin() + (XBin + 1) * XBinSize,
          node->YMin() + YBin * YBinSize,
          node->YMin() + (YBin + 1) * YBinSize
        );
        node->setChildrenAt(XBin, YBin, tmpNode);
      }
      this->nodeInsert(node->childrenAt(XBin, YBin), race);
      return;
    }

    // Add point to leaf node and split it if needed
    node->addRace(race);
    if (node->numPoints() > 4) {
      node->setIsLeaf(false);
      std::vector<Race> races_list = node->getRaces();
      for (Race r : races_list) {
        this->nodeInsert(node, r);
      }
      node->setNumPoints(node->numPoints() - races_list.size());
      node->emptyRaces();
    }
  }


  // Helper function for deleteNode method
  // Collapses a node that no longer meets criterial for a node
  std::vector<Race> collapseNode(QuadTreeNode* node) {
    if (node->isLeaf())
      return node->getRaces();

    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        if (node->childrenAt(i,j) == nullptr) {
          std::vector<Race> sub_pts = this->collapseNode(node->childrenAt(i,j));
          for (Race r : sub_pts) {
            node->addRace(r);
          }
          node->setChildrenAt(i,j,nullptr);
        }
      }
    }

    node->setIsLeaf(true);
    return node->getRaces();
  }

    // Helper function that computes distance from a point to a node
  float minDistance(QuadTreeNode* node,  double x, double y) {
    float x_dist = 0.0;
    if (x < node->XMin())
      x_dist = node->XMin() - x;
    if (x > node->XMax())
      x_dist = x - node->XMax();

    float y_dist = 0.0;
    if (y < node->YMin())
      y_dist = node->YMin() - y;
    if (y > node->YMax())
      y_dist = y - node->YMax();

    return std::sqrt(x_dist * x_dist + y_dist * y_dist);
  }

  // Convert degrees to radians
  float toRadians(float degrees) {
    return degrees * M_PI / 180.0;
  }

  // Calculate distance between two coordinates using Haversine formula
  float haversineDist(float lat1, float lon1, float lat2, float  lon2) {
    // Convert latitude and longitude to radians
    float phi1 = this->toRadians(lat1);
    float phi2 = this->toRadians(lat2);
    float deltaPhi = this->toRadians(lat2 - lat1);
    float deltaLambda = this->toRadians(lon2 - lon1);

    // Apply Haversine formula
    float a = std::sin(deltaPhi / 2.0) * std::sin(deltaPhi / 2.0) +
              std::cos(phi1) * std::cos(phi2) *
              std::sin(deltaLambda / 2.0) * std::sin(deltaLambda / 2.0);
    float c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));
    float distance = 6371.0 * c;  // Earth's mean radius in kilometers

    return distance;
  }

  Race* nearestNeighborNode(QuadTreeNode* node, float x, float y, float best_dist) {
    // Prune if node is farther than best distance
    if (this->minDistance(node, x, y) >= best_dist)
      return nullptr;
    
    Race* best_candidate = nullptr;

    // If we are in a leaf, search race coordinates
    if (node->isLeaf()) {
      for (Race race : node->getRaces()) {
        float dist = this->haversineDist(y, x, race.coordinate.latitude,
            race.coordinate.longitude);

        if (dist < best_dist) {
          best_dist = dist;
          best_candidate = &race;
          return best_candidate;
        }
      }
    }

    // Recursively check all 4 children starting with the closest.
    float x_bin_size = (node->XMax() - node->XMin()) / 2.0;
    float y_bin_size = (node->YMax() - node->YMin()) / 2.0;
    int x_bin = (x - node->XMin()) / x_bin_size;
    if (x_bin < 0)
      x_bin = 0;
    if (x_bin > 1)
      x_bin = 1;
    
    int y_bin = (y - node->YMin()) / y_bin_size;
    if (y_bin < 0)
      y_bin = 0;
    if (y_bin > 1)
      y_bin = 1;
    
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        if (node->childrenAt(i, j) != nullptr) {
          Race* quad_best = this->nearestNeighborNode(
                      node->childrenAt(i,j), x, y, best_dist);
          if (quad_best != nullptr) {
            best_candidate = quad_best;
            best_dist = haversineDist(x, y, 
              quad_best->coordinate.latitude, quad_best->coordinate.longitude);
          }
        }
      }
    }

    return best_candidate;
  }

  QuadTreeNode* rootNode;
};


#endif  // QUADTREE_H