#ifndef CORE_ELEMENT_NODE_DEMAND_H
#define CORE_ELEMENT_NODE_DEMAND_H

#include "core/element/node.h"

class Demand : public Node {
  friend class ElementManager;

public:
  DemandType demandType();

protected:
  Demand(ElementID id, std::string name, double latitude = 0.0, double longitude = 0.0, DemandType demand_type = DemandType::HumanConsume);
  Demand(Node &node);
  virtual ~Demand();

  void setDemandType(DemandType type);

  void initializeNodeType();

private:
  DemandType m_demand_type;
};

#endif
