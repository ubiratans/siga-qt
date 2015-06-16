#include "core/element/node/reservoir.h"

Reservoir::Reservoir(ElementID id, std::string name, double latitude, double longitude) : Node(id, name, latitude, longitude) {
  initializeNodeType();
}

Reservoir::Reservoir(Node &node) : Node(node) {
  initializeNodeType();
}

Reservoir::~Reservoir() {
}

void Reservoir::initializeNodeType() {
    m_type = NodeType::Reservoir;
}
