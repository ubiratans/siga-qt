#ifndef CORE_ELEMENT_NODE_BASIN_H
#define CORE_ELEMENT_NODE_BASIN_H

#include "core/element/node.h"

class Basin : public Node {
  friend class ElementManager;

protected:
  Basin(ElementID id, std::string name, double latitude = 0.0, double longitude = 0.0);
  Basin(Node &node);
  virtual ~Basin();

  void initializeNodeType();
};

#endif
