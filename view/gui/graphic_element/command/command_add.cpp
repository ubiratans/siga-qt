#include "view/gui/graphic_element/command/command_add.h"

struct CommandAddNodeStruct {
  CommandAddNodeStruct(NodeType type, double x, double y)
    : m_x(x), m_y(y), m_type(type)
  {
  }

  NodeType m_node_type;
  ElementID m_id;

  double m_x;
  double m_y;

  Node *m_node;
  GraphicNode *m_graphic_node;
};

CommandAdd::CommandAdd(GraphicElementManager &manager, GraphicNodeStruct graphic_node_st) : m_manager(&manager) {
  m_added_node_struct = new CommandAddNodeStruct(type, id, x, y);
}

CommandAdd::~CommandAdd() {
}

bool CommandAdd::doCommand() {
  ElementManager &element_manager = m_manager->elementManager();
  Node &node = element_manager.addNode(m_added_node_struct->m_node_type, m_added_node_struct->m_y, m_added_node_struct->m_x);

  m_added_node_struct->m_id = node.id();
  m_added_node_struct->m_node = &node;

  // GraphicNodeStruct graphic_node_st(node.type(), node.longitude(), node.
  //GraphicNode *graphic_node = new GraphicNode(node.id(), )

  return false;
}

bool CommandAdd::redoCommand() {
  return false;
}

void CommandAdd::undoCommand() {

}
