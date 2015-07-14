#ifndef VIEW_GUI_GRAPHIC_ELEMENT_COMMAND_COMMAND_H
#define VIEW_GUI_GRAPHIC_ELEMENT_COMMAND_COMMAND_H

#include "core/element/element_structs.h"
#include "core/element/element_constants.h"

class Command {
  friend class CommandManager;

public:
  Command();

  bool canUndo();

protected:
  bool doCommand();
  void undoCommand();
  bool redoCommand();

  virtual bool doCommandImpl() = 0;
  virtual void undoCommandImpl() = 0;
  virtual bool redoCommandImpl() = 0;

private:
  bool m_can_undo;
  bool m_executed;
};

#endif
