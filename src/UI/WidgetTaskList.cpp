/*
 * @name BookFiler Widget w/ QT - Task Manager
 * @version 1.00
 * @license MIT
 * @brief Task Manager Widget tracks task progress
 */

// Local Project
#include "WidgetTaskList.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

TaskList::TaskList() { this->setObjectName("BookFiler Tree Widget"); };
TaskList::~TaskList(){};

int TaskList::setData(std::shared_ptr<sqlite3> database_,
                      std::string tableName_,
                      std::map<std::string, std::string> columnMap_) {
  return 0;
}

int TaskList::update() { return 0; }

int TaskList::updateIdHint(std::vector<std::string> addedIdList_,
                           std::vector<std::string> updatedIdList_,
                           std::vector<std::string> deletedIdList_) {
  return 0;
}

int TaskList::connectUpdateIdHint(
    std::function<void(std::vector<std::string>, std::vector<std::string>,
                       std::vector<std::string>)>
        func_) {
  return 0;
}

int TaskList::setItemEditorWidget(
    int columnNum,
    std::function<std::shared_ptr<QWidget>()> editorWidgetCreator) {
  return 0;
}

int TaskList::selectWhereStatus(int statusCode_) { return 0; }

int TaskList::selectWhereAll() { return 0; }

int TaskList::addItem(std::shared_ptr<TaskItem> taskItem_) { return 0; }
int TaskList::setPollDuration(std::chrono::milliseconds duration_) { return 0; }

} // namespace widget
} // namespace bookfiler
