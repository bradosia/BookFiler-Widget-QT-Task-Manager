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
#include <functional>
#include <iostream>
#include <memory>
#include <string>

// Local Project
// #include "LocalFile"

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

public:
  TaskItem();
  ~TaskItem();
};

} // namespace widget
} // namespace bookfiler

#endif
// end BOOKFILER_WIDGET_QT_TASK_MANAGER_TASK_ITEM_H
