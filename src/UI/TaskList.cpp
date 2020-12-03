/*
 * @name BookFiler Widget w/ QT - Task Manager
 * @version 1.00
 * @license MIT
 * @brief Task Manager Widget tracks task progress
 */

/* QT 5.13.2
 * License: LGPLv3
 */
#include <QDebug>
#include <QVBoxLayout>
#include <SqliteQueryEngine.hpp>

// Local Project
#include "TaskList.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

TaskList::TaskList() {
  this->setObjectName("BookFiler Tree Widget");
  this->setLayout(new QVBoxLayout());
}
TaskList::~TaskList() {}

#if DEPENDENCY_SQLITE
std::shared_ptr<TaskItem>
TaskList::createTaskItemFromContent(TableContent &content, std::size_t index) {
  std::shared_ptr<TaskItem> task_item_ = std::make_shared<TaskItem>(this);
  task_item_->setTitle(content["title"].at(index));
  task_item_->setDescription(content["description"].at(index));
  task_item_->setProgressBarValues(content["partsDone"].at(index),
                                   content["partsTotal"].at(index));
  task_item_->setRemainingTime(content["timeRemaining"].at(index));
  task_item_->setCancelIcon(content["CanCancel"].at(index));
  task_item_->setStatus(content["status"].at(index));
  return task_item_;
}
#endif

int TaskList::update() {
#if DEPENDENCY_SQLITE
  TableContent content = queryEngine.updateContent(database, &queryEngine);
  taskItemList.clear();
  const std::size_t number_of_task = content["id"].size();
  for (std::size_t idx = 0; idx < number_of_task; ++idx) {
    addItem(createTaskItemFromContent(content, idx));
  }
#endif
  return 0;
}

int updateIdHint(std::vector<std::string> addedIdList,
                 std::vector<std::string> updatedIdList,
                 std::vector<std::string> deletedIdList) {
  // TODO
  return 0;
}

int TaskList::setItemEditorWidget(
    int columnNum,
    std::function<std::shared_ptr<QWidget>()> editorWidgetCreator) {
  // TODO
  return 0;
}

int TaskList::selectWhereStatus(int statusCode_) {
  // TODO
  return 0;
}

int TaskList::selectWhereAll() {
  // TODO
  return 0;
}

int TaskList::addItem(std::shared_ptr<TaskItem> taskItem_) {
  taskItemList.push_back(taskItem_);
  this->layout()->addWidget(taskItem_.get());
  return 0;
}
int TaskList::setPollDuration(std::chrono::milliseconds duration_) { return 0; }

#if DEPENDENCY_SQLITE
// DO NOT USE, DO THIS ON THE MODEL INSTEAD
int setData(std::shared_ptr<sqlite3> database_, std::string tableName_,
            std::map<std::string, std::string> columnMap_) {
  return 0;
}
#endif

} // namespace widget
} // namespace bookfiler
