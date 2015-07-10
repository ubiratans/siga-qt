#include "view/gui/graphic_element/graphic_element_manager.h"

#include "view/gui/graphic_element/graphic_node.h"

GraphicElementManager::GraphicElementManager(ElementManager &element_manager) : m_element_manager(&element_manager) {
}

GraphicElementManager::~GraphicElementManager() {

}

ElementManager& GraphicElementManager::elementManager() {
  return *m_element_manager;
}

/*GraphicNode &GraphicElementManager::addGraphicNode(NodeType type, double world_x, double world_y) {

}*/
