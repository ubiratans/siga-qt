#ifndef VIEW_GUI_GRAPHIC_ELEMENT_COMMAND_COMMAND_H
#define VIEW_GUI_GRAPHIC_ELEMENT_COMMAND_COMMAND_H

#include "core/element/element_structs.h"
#include "core/element/element_constants.h"

class Command {
public:
  virtual bool doCommand() = 0;
  virtual void undoCommand() = 0;
  virtual bool redoCommand() = 0;
};

#endif
