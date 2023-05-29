#ifndef  QUADTREE_H
#define  QUADTREE_H

#include "./race.h"

#include <vector>
#include <stdexcept>

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

  private:
    QuadTreeNode* rootNode;
};

#endif  // QUADTREE_H