/*
 * @name BookFiler Widget w/ QT - Task Manager
 * @version 1.00
 * @license MIT
 * @brief Task Manager Widget tracks task progress
 */

// Local Project
#include "WidgetTaskItem.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

TaskItem::TaskItem(){};
TaskItem::~TaskItem(){};

int TaskItem::setTitle(std::string title) { return 0; }

std::string TaskItem::getTitle() { return std::string(); }

int TaskItem::setDescription(std::string title) { return 0; }

std::string TaskItem::getDescription() { return std::string(); }

} // namespace widget
} // namespace bookfiler
