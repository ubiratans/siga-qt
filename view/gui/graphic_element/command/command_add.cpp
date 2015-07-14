#include "view/gui/graphic_element/command/command_add.h"

CommandAdd::CommandAdd(GraphicElementManager &manager, GraphicNodeStruct graphic_node_st) : m_manager(&manager) {
  m_node_struct = new CommandAddNodeStruct(graphic_node_st);
}

CommandAdd::~CommandAdd() {
  if (m_node_struct) {
    if (canUndo()) {
      m_node_struct->m_graphic_node = nullptr;
      m_node_struct->m_node = nullptr;
    }

    delete m_node_struct;
  }
}

bool CommandAdd::doCommandImpl() {
  ElementManager &element_manager = m_manager->elementManager();
  Node &node = element_manager.addNode(m_node_struct->m_graphic_node_struct->m_type,
                                       m_node_struct->m_graphic_node_struct->m_y,
                                       m_node_struct->m_graphic_node_struct->m_y);

  m_node_struct->m_node = &node;

  GraphicNode *graphic_node = new GraphicNode(node.id(), *m_node_struct->m_graphic_node_struct);

  m_node_struct->m_node = &node;
  m_node_struct->m_graphic_node = graphic_node;

  m_manager->graphicNodesMap()[node.id()] = graphic_node;
  m_manager->graphicElementsMap()[node.id()] = graphic_node;

  return true;
}

bool CommandAdd::redoCommandImpl() {
  ElementManager &element_manager = m_manager->elementManager();

  if (m_node_struct) {
    element_manager.attachNode(*m_node_struct->m_node);

    m_manager->graphicNodesMap()[m_node_struct->m_node->id()] = m_node_struct->m_graphic_node;
    m_manager->graphicElementsMap()[m_node_struct->m_node->id()] = m_node_struct->m_graphic_node;
  }

  return true;
}

void CommandAdd::undoCommandImpl() {
  ElementManager &element_manager = m_manager->elementManager();

  if (m_node_struct) {
    Node *node = m_node_struct->m_node;

    element_manager.detachNode(node->id());
    m_manager->graphicElementsMap().erase(node->id());
    m_manager->graphicNodesMap().erase(node->id());
  }
}
