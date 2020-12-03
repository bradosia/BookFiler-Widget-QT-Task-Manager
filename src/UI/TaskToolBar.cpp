/*
 * @name BookFiler Widget w/ QT - Task Manager
 * @version 1.00
 * @license MIT
 * @brief Task Manager Widget tracks task progress
 */

// Local Project
#include "TaskToolBar.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

TaskToolbar::TaskToolbar(QWidget *parent) : QWidget(parent) {
  this->setObjectName("BookFiler Tree Widget");
  clear_toolbar = new QWidget(this);
  clear_toolbar->setFixedHeight(40);
  clear_suceeded = new QPushButton(QIcon("resources/icons/CompletedTask@2x.png"), "", this);
  clear_failed = new QPushButton(QIcon("resources/icons/Warning@2x.png"), "", this);
  clear_canceled = new QPushButton(QIcon("resources/icons/Error@2x.png"), "", this);
  lbl_clear_inactive = new QLabel("Clear inactive");
  clear_toolbar->setLayout(new QHBoxLayout);
  clear_toolbar->layout()->addWidget(lbl_clear_inactive);
  dynamic_cast<QHBoxLayout *>(clear_toolbar->layout())->addStretch();
  clear_toolbar->layout()->addWidget(clear_suceeded);
  clear_toolbar->layout()->addWidget(clear_failed);
  clear_toolbar->layout()->addWidget(clear_canceled);
  this->setLayout(new QVBoxLayout);
  this->layout()->addWidget(clear_toolbar);
}
TaskToolbar::~TaskToolbar() {}

} // namespace widget
} // namespace bookfiler
