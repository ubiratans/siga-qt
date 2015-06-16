#ifndef CORE_ELEMENT_NODE_JUNCTION_H
#define CORE_ELEMENT_NODE_JUNCTION_H

#include "core/element/node.h"

class Junction : public Node {
  friend class ElementManager;

protected:
  Junction(ElementID id, std::string name, double latitude = 0.0, double longitude = 0.0);
  Junction(Node &node);
  virtual ~Junction();

  void initializeNodeType();
};

#endif
