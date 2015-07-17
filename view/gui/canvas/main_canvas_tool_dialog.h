#ifndef VIEW_GUI_CANVAS_MAIN_CANVAS_TOOL_DIALOG_H
#define VIEW_GUI_CANVAS_MAIN_CANVAS_TOOL_DIALOG_H

#include <QDialog>

namespace Ui {
class MainCanvasToolDialog;
}

class MainCanvasToolDialog : public QDialog {
    Q_OBJECT

public:
    explicit MainCanvasToolDialog(QWidget *parent = 0);
    ~MainCanvasToolDialog();

private:
    Ui::MainCanvasToolDialog *m_ui;
};

#endif
