#ifndef CORE_ELEMENT_RESERVOIR_H
#define CORE_ELEMENT_RESERVOIR_H

#include "core/element/node.h"

class Reservoir : public Node {
  friend class ElementManager;

protected:
  Reservoir(ElementID id, std::string name, double latitude = 0.0, double longitude = 0.0);
  Reservoir(Node &node);
  virtual ~Reservoir();

  void initializeNodeType();
};

#endif
