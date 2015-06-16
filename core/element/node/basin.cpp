#include "core/element/node/basin.h"

Basin::Basin(ElementID id, std::string name, double latitude, double longitude) : Node(id, name, latitude, longitude) {
  initializeNodeType();
}

Basin::Basin(Node &node) : Node(node) {
  initializeNodeType();
}

Basin::~Basin() {
}

void Basin::initializeNodeType() {
  m_type = NodeType::Basin;
}
