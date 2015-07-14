#include "view/gui/graphic_element/command/command.h"

Command::Command() : m_executed(false), m_can_undo(false) {

}

bool Command::doCommand() {
  bool ret = false;

  if (!m_can_undo) {
    if (doCommandImpl()) {
      m_executed = m_can_undo = ret = true;
    }
  }

  return ret;
}

void Command::undoCommand() {
  if (m_can_undo) {
    undoCommandImpl();
  }
}

bool Command::redoCommand() {
  bool ret = false;

  if (!m_can_undo && m_executed) {
    if (redoCommandImpl()) {
      m_can_undo = ret = true;
    }
  }

  return ret;
}

bool Command::canUndo() {
  return m_can_undo;
}
