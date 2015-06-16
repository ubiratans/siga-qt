#include "core/element/node/junction.h"

Junction::Junction(ElementID id, std::string name, double latitude, double longitude) : Node(id, name, latitude, longitude) {
  initializeNodeType();
}

Junction::Junction(Node &node) : Node(node) {
  initializeNodeType();
}

Junction::~Junction() {
}

void Junction::initializeNodeType() {
  m_type = NodeType::Junction;
}
