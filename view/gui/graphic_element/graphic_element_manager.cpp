#include "view/gui/graphic_element/graphic_element_manager.h"

#include "view/gui/graphic_element/graphic_node.h"

GraphicElementManager::GraphicElementManager(ElementManager &element_manager) : m_element_manager(&element_manager) {
}

GraphicElementManager::~GraphicElementManager() {

}

GraphicNode &GraphicElementManager::addNode(GraphicNodeStruct &st) {

}

ElementManager& GraphicElementManager::elementManager() {
  return *m_element_manager;
}

std::map<ElementID, GraphicNode *>& GraphicElementManager::graphicNodesMap() {
  return m_graphic_nodes_map;
}

std::map<ElementID, GraphicElement *>& GraphicElementManager::graphicElementsMap() {
  return m_graphic_elements_map;
}

/*GraphicNode &GraphicElementManager::addGraphicNode(NodeType type, double world_x, double world_y) {

}*/
