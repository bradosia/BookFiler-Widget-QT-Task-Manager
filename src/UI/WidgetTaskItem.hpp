/*
 * @name BookFiler Widget w/ QT - Task Manager
 * @version 1.00
 * @license MIT
 * @brief Task Manager Widget tracks task progress
 */

#ifndef BOOKFILER_WIDGET_QT_TASK_MANAGER_TASK_ITEM_H
#define BOOKFILER_WIDGET_QT_TASK_MANAGER_TASK_ITEM_H

// config
#include "../core/config.hpp"

// C++17
#include <chrono>
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

// Local Project
// #include "Item.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

class TaskItem {
private:
  /* getProgress() is called periodically id task polling is enabled. Most tasks
   * should already signal changes for their progress to their associated
   * TaskItem.
   * @param partsDone parts done of the parts total. This could represent a
   * percent completion or bytes loaded or any other unit.
   * @param partsTotal parts total to complete
   * @param timeRemaining time in milliseconds remaining for the task.
   * @return 0 on success, else error code
   */
  std::function<int(int &partsDone, int &partsTotal,
                    std::chrono::milliseconds &timeRemaining)>
  getProgress();
  std::function<int()> doCancel();
  std::function<int()> doPause();

public:
  TaskItem();
  ~TaskItem();

  /* Sets the task title
   * @param title task title
   * @return 0 on success, else error code
   */
  int setTitle(std::string title);
  /* Gets the task title
   * @return task title
   */
  std::string getTitle();
  /* Sets the task description
   * @param title task description
   * @return 0 on success, else error code
   */
  int setDescription(std::string title);
  /* Gets the task description
   * @return task description
   */
  std::string getDescription();
};

} // namespace widget
} // namespace bookfiler

#endif
// end BOOKFILER_WIDGET_QT_TASK_MANAGER_TASK_ITEM_H
