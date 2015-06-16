#ifndef CORE_ELEMENT_NODE_LAKE_H
#define CORE_ELEMENT_NODE_LAKE_H

#include "core/element/node.h"

class Lake : public Node {
  friend class ElementManager;

protected:
  Lake(ElementID id, std::string name, double latitude = 0.0, double longitude = 0.0);
  Lake(Node &node);
  virtual ~Lake();

  void initializeNodeType();
};

#endif
