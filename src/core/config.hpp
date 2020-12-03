/*
 * @name BookFiler Widget w/ QT - Task Manager
 * @version 1.00
 * @license MIT
 * @brief Task Manager Widget tracks task progress
 */

#ifndef BOOKFILER_WIDGET_QT_TASK_MANAGER_CONFIG_H
#define BOOKFILER_WIDGET_QT_TASK_MANAGER_CONFIG_H

#define BOOKFILER_WIDGET_QT_TASK_LIST_DEBUG 1
#define BOOKFILER_WIDGET_QT_TASK_ITEM_DEBUG 1
#define BOOKFILER_WIDGET_QT_TASK_TOOL_BAR_DEBUG 1

// C++
#include <string>

#ifdef DEPENDENCY_BOOST
/* boost 1.72.0
 * License: Boost Software License (similar to BSD and MIT)
 */
#define BOOST_ALLOW_DEPRECATED_HEADERS
#endif

namespace bookfiler {
namespace widget {

static std::string moduleName = "BookFiler Widget";
static std::string moduleCode = "bookfiler::widget";

} // namespace widget
} // namespace bookfiler

#endif // BOOKFILER_WIDGET_QT_TASK_MANAGER_CONFIG_H
