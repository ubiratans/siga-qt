#include "view/gui/graphic_element/command/command_add.h"

CommandAdd::CommandAdd(GraphicElementManager &manager, GraphicNodeStruct graphic_node_st) : m_manager(&manager) {
  m_graphic_node_struct = new GraphicNodeStruct(graphic_node_st);
}

CommandAdd::~CommandAdd() {
  if (m_graphic_node_struct) {
    delete m_graphic_node_struct;
  }
}

bool CommandAdd::doCommandImpl() {
/*  ElementManager &element_manager = m_manager->elementManager();
  Node &node = element_manager.addNode(m_graphic_node_struct->);

  m_added_node_struct->m_id = node.id();
  m_added_node_struct->m_node = &node;

  GraphicNode *graphic_node = new GraphicNode(node.id(), m_graphic_node_struct);*/



  return false;
}

bool CommandAdd::redoCommandImpl() {
  return false;
}

void CommandAdd::undoCommandImpl() {

}
