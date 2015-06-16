#include "core/element/node/lake.h"

Lake::Lake(ElementID id, std::string name, double latitude, double longitude) : Node(id, name, latitude, longitude) {
  initializeNodeType();
}

Lake::Lake(Node &node) : Node(node) {
  initializeNodeType();
}

Lake::~Lake() {

}

void Lake::initializeNodeType() {
    m_type = NodeType::Lake;
}
