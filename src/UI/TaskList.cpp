/*
 * @name BookFiler Widget w/ QT - Task Manager
 * @version 1.00
 * @license MIT
 * @brief Task Manager Widget tracks task progress
 */

// Local Project
#include "TaskList.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

TaskList::TaskList() { this->setObjectName("BookFiler Widget - Task List"); };
TaskList::~TaskList(){};

int TaskList::update() { return 0; }

int TaskList::setItemEditorWidget(
    int columnNum,
    std::function<std::shared_ptr<QWidget>()> editorWidgetCreator) {
  return 0;
}

int TaskList::selectWhereStatus(int statusCode_) { return 0; }

int TaskList::selectWhereAll() { return 0; }

int TaskList::setPollDuration(std::chrono::milliseconds duration_) { return 0; }

} // namespace widget
} // namespace bookfiler
