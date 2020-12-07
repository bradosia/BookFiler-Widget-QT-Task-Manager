/*
 * @name BookFiler Widget w/ QT - Task Manager
 * @version 1.00
 * @license MIT
 * @brief Task Manager Widget tracks task progress
 */

#ifndef BOOKFILER_WIDGET_QT_TASK_MANAGER_TOOL_BAR_H
#define BOOKFILER_WIDGET_QT_TASK_MANAGER_TOOL_BAR_H

// config
#include "../core/config.hpp"

// C++17
#include <iostream>
#include <map>
#include <memory>
#include <string>

/* QT 5.13.2
 * License: LGPLv3
 */
#include <QWidget>
#include <QPushButton>
#include <QLabel>

// Local Project
#include "TaskList.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

class TaskToolbar : public QWidget {
  Q_OBJECT
private:
  std::shared_ptr<TaskList> taskListWidget;
  QPushButton* clear_suceeded,*clear_failed,*clear_canceled;
  QLabel* lbl_clear_inactive;
  QWidget* clear_toolbar;

public:
  explicit TaskToolbar(QWidget* parent=nullptr);
  ~TaskToolbar();
};

} // namespace widget
} // namespace bookfiler

#endif
// end BOOKFILER_WIDGET_QT_TASK_MANAGER_TOOL_BAR_H
