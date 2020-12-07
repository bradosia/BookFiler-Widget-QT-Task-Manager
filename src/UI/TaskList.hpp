/*
 * @name BookFiler Widget w/ QT - Task Manager
 * @version 1.00
 * @license MIT
 * @brief Task Manager Widget tracks task progress
 */

#ifndef BOOKFILER_WIDGET_QT_TASK_MANAGER_TASK_MANAGER_H
#define BOOKFILER_WIDGET_QT_TASK_MANAGER_TASK_MANAGER_H

// config
#include "../core/config.hpp"

// C++17
#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>

/* QT 5.13.2
 * License: LGPLv3
 */
#include <QTreeView>
#include <QWidget>

// Local Project
#include "TaskItem.hpp"

#include <SqliteQueryEngine.hpp>

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

#if DEPENDENCY_SQLITE
using bookfiler::core::TableContent;
#endif

class TaskList : public QTreeView {
  Q_OBJECT
protected:
  std::vector<std::shared_ptr<TaskItem>> taskItemList{};
  std::string tableName, viewRootId;
  std::map<std::string, std::string> columnMap{
      {"id", "id"},
      {"parentId", "parentId"},
      {"partsDone", "partsDone"},
      {"partsTotal", "partsTotal"},
      {"timeElapsed", "timeElapsed"},
      {"timeRemaining", "timeRemaining"},
      {"timeTotal", "timeTotal"},
      {"CanCancel", "CanCancel"},
      {"IsCancel", "IsCancel"},
      {"CanPause", "CanPause"},
      {"IsPause", "IsPause"},
      {"status", "status"},
      {"IsSelected", "IsSelected"},
      {"title", "title"},
      {"description", "description"}};

#if DEPENDENCY_SQLITE
  std::shared_ptr<sqlite3> database;
  bookfiler::core::SQliteQueryEngine queryEngine;

  std::shared_ptr<TaskItem> createTaskItemFromContent(TableContent &content,
                                                      std::size_t index);
#endif

  /* Should only be used internally to add UI elements
   */
  int addItem(std::shared_ptr<TaskItem> taskItem_);

public:
  TaskList();
  ~TaskList();

  /* Called when the sqlite3 database is updated by another widget, thread, or
   * process. Need to rebuild the entire internal representation of the tree
   * because no hint at which rows were added, updated, or deleted is provided.
   * @return 0 on success, else error code
   */
  int update();

  /* Called when the sqlite3 database is updated by another widget, thread, or
   * process. Internally, this method will need to ask the model for the list of
   * QModelIndex that need to be updated.
   * @param addedIdList a list of id that were added. Only the
   * row id provided was added, not the children, unless the child id is
   * also listed
   * @param updatedIdList a list of id that were updated. Only the
   * row id provided was updated, not the children, unless the child id is
   * also listed
   * @param deletedIdList a list of id that were deleted. Only the
   * row id provided was deleted, not the children, unless the child id is
   * also listed
   * @return 0 on success, else error code
   */
  int updateIdHint(std::vector<std::string> addedIdList,
                   std::vector<std::string> updatedIdList,
                   std::vector<std::string> deletedIdList);

  /*
   * @param columnNum The column number that the editor widget will be used for
   * starting from 0
   * @param editorWidgetCreator A function to call that will create a new
   * std::shared_ptr for the item editor widget
   */
  int setItemEditorWidget(
      int columnNum,
      std::function<std::shared_ptr<QWidget>()> editorWidgetCreator);

  /* Select the task items that will be displayed by the widget. This method
   * does not imply the view will be updated. update() must be also called to
   * update the view.
   * @param statusCode the code to filter items by. 0 and 1 = In Progress, 2 =
   * Success, 3 = Cancelled, 4 = Failed
   * @return 0 on success, else error code
   */
  int selectWhereStatus(int statusCode);

  /* Selects all task items to be be displayed by the widget. This method
   * does not imply the view will be updated. update() must be also called to
   * update the view.
   * @return 0 on success, else error code
   */
  int selectWhereAll();

  /* Sets the duration between data polls of the task items. Polling will update
   * progress on the task. Only items currently being view are polled. Items
   * that go from not visible to visible because of a select will be polled
   * immedietely.
   * @param duration the duration in milliseconds between polls
   * @return 0 on success, else error code
   */
  int setPollDuration(std::chrono::milliseconds duration);

#if DEPENDENCY_SQLITE
  // DO NOT USE, DO THIS ON THE MODEL INSTEAD
  int setData(std::shared_ptr<sqlite3> database, std::string tableName,
              std::map<std::string, std::string> columnMap =
                  std::map<std::string, std::string>());
#endif

  friend class WidgetTaskListTest;
};

} // namespace widget
} // namespace bookfiler

#endif
// end BOOKFILER_WIDGET_QT_TASK_MANAGER_TASK_MANAGER_H
