#include "view/gui/canvas/main_canvas_tool_dialog.h"
#include "view/gui/canvas/main_canvas_tool_dialog_ui.h"

MainCanvasToolDialog::MainCanvasToolDialog(QWidget *parent) : QDialog(parent), m_ui(new Ui::MainCanvasToolDialog) {
  m_ui->setupUi(this);
}

MainCanvasToolDialog::~MainCanvasToolDialog() {
  delete m_ui;
}
