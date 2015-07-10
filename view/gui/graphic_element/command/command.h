#ifndef VIEW_GUI_GRAPHIC_ELEMENT_COMMAND_COMMAND_H
#define VIEW_GUI_GRAPHIC_ELEMENT_COMMAND_COMMAND_H

#include "core/element/element_structs.h"
#include "core/element/element_constants.h"

class Command {
public:
  Command();

  bool doCommand();
  void undoCommand();
  bool redoCommand();

protected:
  virtual bool doCommandImpl() = 0;
  virtual void undoCommandImpl() = 0;
  virtual bool redoCommandImpl() = 0;

  bool m_can_undo;
  bool m_executed;
};

#endif
