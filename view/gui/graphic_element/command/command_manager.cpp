#include "view/gui/graphic_element/command/command_manager.h"

CommandManager::CommandManager(uint32_t stack_size) : m_stack_size(stack_size) {
  m_redo_stack.reserve(stack_size);
  m_undo_stack.reserve(stack_size);
}

CommandManager::~CommandManager() {
  clear();
}

bool CommandManager::execute(Command *cmd) {
  if (cmd == nullptr) {
    return false;
  }

  else if (cmd->doCommand()) {
    m_undo_stack.push_back(cmd);

    if (m_undo_stack.size() + m_redo_stack.size() + 1 > m_stack_size) {
      if (!m_undo_stack.empty()) {
        delete m_undo_stack.front();

        m_undo_stack.erase(m_undo_stack.begin());
      }
    }

    deleteAndClearStack(m_redo_stack);

    return true;
  }

  delete cmd;
  return false;
}

void CommandManager::undo() {
  std::vector< Command* > &pop_stack = m_undo_stack;
  std::vector< Command* > &push_stack = m_redo_stack;

  if (!pop_stack.empty()) {
    Command *cmd = pop_stack.back();

    cmd->undoCommand();

    pop_stack.pop_back();
    push_stack.push_back(cmd);
  }
}

void CommandManager::redo() {
  std::vector< Command* > &pop_stack = m_redo_stack;
  std::vector< Command* > &push_stack = m_undo_stack;

  if (!pop_stack.empty()) {
    Command *cmd = pop_stack.back();

    cmd->redoCommand();

    pop_stack.pop_back();
    push_stack.push_back(cmd);
  }
}

bool CommandManager::canUndo() {
  return !m_undo_stack.empty();
}

bool CommandManager::canRedo() {
  return !m_redo_stack.empty();
}

void CommandManager::clear() {
  deleteAndClearStack(m_redo_stack);
  deleteAndClearStack(m_undo_stack);
}

void CommandManager::deleteAndClearStack(std::vector< Command* > &stack) {
  while (!stack.empty()) {
    delete stack.back();

    stack.pop_back();
  }
}
