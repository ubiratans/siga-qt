#include "view/gui/statusbar_widget.h"

#include "view/gui/statusbar_widget_ui.h"

StatusBarWidget::StatusBarWidget(QWidget *parent) :  QWidget(parent), m_ui(new Ui::StatusBarWidget) {
  m_ui->setupUi(this);
}

StatusBarWidget::~StatusBarWidget() {
  delete m_ui;
}

void StatusBarWidget::setHeaderText(QString text) {
  m_ui->m_header_label->setText(text);
}

void StatusBarWidget::setContentText(QString text) {
  m_ui->m_content_label->setText(text);
}
