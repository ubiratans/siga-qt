#ifndef VIEW_GUI_GRAPHIC_ELEMENT_COMMAND_COMMAND_MANAGER_H
#define VIEW_GUI_GRAPHIC_ELEMENT_COMMAND_COMMAND_MANAGER_H

#include <cstdint>
#include <vector>

#include "view/gui/graphic_element/command/command.h"

class CommandManager {
public:
  CommandManager(uint32_t stack_size);
  ~CommandManager();

  bool execute(Command *cmd);
  void undo();
  void redo();

  bool canUndo();
  bool canRedo();

private:
  void clear();
  void deleteAndClearStack(std::vector<Command *> &stack);

  std::vector< Command* > m_undo_stack;
  std::vector< Command* > m_redo_stack;

  uint32_t m_stack_size;
};

#endif
