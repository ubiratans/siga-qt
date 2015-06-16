#include "core/element/node/demand.h"

DemandType Demand::demandType() {
  return m_demand_type;
}

Demand::Demand(ElementID id, std::string name, double latitude, double longitude, DemandType demand_type) :
  Node(id, name, latitude, longitude), m_demand_type(demand_type)
{
  initializeNodeType();
}

Demand::Demand(Node &node) : Node(node) {
  initializeNodeType();
}

Demand::~Demand() {

}

void Demand::setDemandType(DemandType type) {
  m_demand_type = type;
}

void Demand::initializeNodeType() {
  m_type = NodeType::Demand;
}
