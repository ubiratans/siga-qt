#ifndef VIEW_GUI_GRAPHIC_ELEMENT_COMMAND_COMMAND_ADD_H
#define VIEW_GUI_GRAPHIC_ELEMENT_COMMAND_COMMAND_ADD_H

#include "view/gui/graphic_element/command/command.h"
#include "view/gui/graphic_element/graphic_element_manager.h"

class CommandAdd : public Command {
public:
  CommandAdd(GraphicElementManager &manager, GraphicNodeStruct graphic_node_struct);
  virtual ~CommandAdd();

protected:
  bool doCommandImpl();
  bool redoCommandImpl();
  void undoCommandImpl();

private:
  GraphicElementManager *m_manager{nullptr};
  GraphicNodeStruct *m_graphic_node_struct{nullptr};
};

#endif
