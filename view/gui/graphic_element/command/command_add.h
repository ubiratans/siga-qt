#ifndef VIEW_GUI_GRAPHIC_ELEMENT_COMMAND_COMMAND_ADD_H
#define VIEW_GUI_GRAPHIC_ELEMENT_COMMAND_COMMAND_ADD_H

#include "view/gui/graphic_element/command/command.h"

class CommandAdd : public Command {
public:
  CommandAdd(NodeType type, ElementID id, double x, double y);
  virtual ~CommandAdd();

  bool doCommand();
  bool redoCommand();
  void undoCommand();

private:

};

#endif
