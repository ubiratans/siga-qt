#ifndef VIEW_GUI_GRAPHIC_ELEMENT_COMMAND_COMMAND_ADD_H
#define VIEW_GUI_GRAPHIC_ELEMENT_COMMAND_COMMAND_ADD_H

#include "view/gui/graphic_element/command/command.h"
#include "view/gui/graphic_element/graphic_element_manager.h"

struct CommandAddNodeStruct;

class CommandAdd : public Command {
public:
  CommandAdd(GraphicElementManager &manager, NodeType type, double x, double y);
  virtual ~CommandAdd();

  bool doCommand();
  bool redoCommand();
  void undoCommand();

private:
  GraphicElementManager *m_manager;
  CommandAddNodeStruct *m_added_node_struct;
};

#endif
