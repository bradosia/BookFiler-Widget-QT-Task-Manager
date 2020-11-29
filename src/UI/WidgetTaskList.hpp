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

/* boost 1.72.0
 * License: Boost Software License (similar to BSD and MIT)
 */
#include <boost/signals2.hpp>

/* sqlite3 3.33.0
 * License: PublicDomain
 */
#include <sqlite3.h>

/* QT 5.13.2
 * License: LGPLv3
 */
#include <QWidget>

// Local Project
#include "WidgetTaskItem.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

class TaskList : public QWidget {
  Q_OBJECT
private:
  std::shared_ptr<sqlite3> database;
  std::string tableName, viewRootId;
  boost::signals2::signal<void(std::vector<std::string>,
                               std::vector<std::string>,
                               std::vector<std::string>)>
      updateSignal;
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

public:
  TaskList();
  ~TaskList();

  /* Sets the database to use for the task manager widget.
   * @param database mysqlite3 database that this widget will be synced
   * with
   * @param tableName the table name
   * @param columnMap maps internal comuns names to user column names
   * @return 0 on success, else error code
   */
  int setData(std::shared_ptr<sqlite3> database, std::string tableName,
              std::map<std::string, std::string> columnMap =
                  std::map<std::string, std::string>());
  /* Called when the sqlite3 database is updated by another widget, thread, or
   * process. Need to rebuild the entire internal representation of the tree
   * because no hint at which rows were added, updated, or deleted is provided.
   * @return 0 on success, else error code
   */
  int update();
  /* Called when the sqlite3 database is updated by another widget, thread, or
   * process.
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
  /* Connect a function that will be signaled when the database is updated by
   * this widget
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
  int connectUpdateIdHint(
      std::function<void(std::vector<std::string>, std::vector<std::string>,
                         std::vector<std::string>)>);
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
  /* adds a task item to the list. Adds the associated data to the sqlite3
   * database table. This method does not imply the view will be updated.
   * update() must be also called to update the view.
   * @param taskItem shared_ptr to the task item
   * @return 0 on success, else error code
   */
  int addItem(std::shared_ptr<TaskItem> taskItem);
  /* Sets the duration between data polls of the task items. Polling will update
   * progress on the task. Only items currently being view are polled. Items
   * that go from not visible to visible because of a select will be polled
   * immedietely.
   * @param duration the duration in milliseconds between polls
   * @return 0 on success, else error code
   */
  int setPollDuration(std::chrono::milliseconds duration);
};

} // namespace widget
} // namespace bookfiler

#endif
// end BOOKFILER_WIDGET_QT_TASK_MANAGER_TASK_MANAGER_H
