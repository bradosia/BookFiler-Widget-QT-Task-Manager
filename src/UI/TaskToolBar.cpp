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

TaskToolbar::TaskToolbar() { this->setObjectName("BookFiler Tree Widget"); };
TaskToolbar::~TaskToolbar(){};

int TaskToolbar::setTaskList(std::shared_ptr<TaskList> widget_) { return 0; }

} // namespace widget
} // namespace bookfiler
