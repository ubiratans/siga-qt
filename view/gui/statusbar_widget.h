#ifndef VIEW_GUI_STATUS_BAR_WIDGET_H
#define VIEW_GUI_STATUS_BAR_WIDGET_H

#include <QWidget>

namespace Ui {
class StatusBarWidget;
}

class StatusBarWidget : public QWidget {
  Q_OBJECT

public:
  explicit StatusBarWidget(QWidget *parent = 0);
  ~StatusBarWidget();

  void setHeaderText(QString text);
  void setContentText(QString text);

  Ui::StatusBarWidget *m_ui;
};

#endif
