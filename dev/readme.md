# Development Summary

I need a QT5 widget written in C++. Only the widget implementation needs to be written, not an app. This project is a task manager that consists of three components: 
* The task list, which is an view that observes data from a sqlite3 `QAbstractItemModel`
* the task items. Right now this component is unused because the task list component should generate a task tree.
* the task toolbar. Provides controls for the task list and the sqlite3 `QAbstractItemModel`
The implementation requires a sqlite3 database backend. The header files are already written so the implementation should be filled in. See the photos for how the task manager should look.

Header: [/src/UI/TaskList.hpp](/src/UI/TaskList.hpp)

![/reference/widget-overview.png](/reference/widget-overview.png?raw=true)

![/reference/widget-tasklist-subtasks.png](/reference/widget-tasklist-subtasks.png?raw=true)

Header: [/src/UI/TaskItem.hpp](/src/UI/TaskItem.hpp)

![/reference/widget-laskitem.png](/reference/widget-laskitem.png?raw=true)

# sqlite3 `QAbstractItemModel`

This is the data model used with the TaskList. The sqlite3 `QAbstractItemModel` is similar to `QSqlTableModel`, except it is specialized to use `sqlite3`.

## Why is `sqlite3` used and not `QSqlDatabase`?

The reason `sqlite3` is used and not `QSqlDatabase` is because other modules this widget is used with won't be linked against QT, so a `sqlite3` database is passed between modules instead.

## SQL Table format
The default table create statement is shown below. The Table name and column names may be different, but the user must explicitly map the names with the columnMap argument in `dataModel->setData(std::shared_ptr<sqlite3> database, std::string tableName, std::map<std::string, std::string> columnMap)`

```sql
CREATE TABLE "taskList" (
	"id"	INTEGER NOT NULL,
	"parentId"	INTEGER NOT NULL,
	"partsDone"	INTEGER,
	"partsTotal"	INTEGER,
	"timeElapsed"	INTEGER,
	"timeRemaining"	INTEGER,
	"timeTotal"	INTEGER,
	"CanCancel"	INTEGER NOT NULL,
	"IsCancel"	INTEGER NOT NULL,
	"CanPause"	INTEGER NOT NULL,
	"IsPause"	INTEGER NOT NULL,
	"status"	INTEGER,
	"IsSelected"	INTEGER,
	"title"	TEXT,
	"description"	TEXT,
	PRIMARY KEY("id" AUTOINCREMENT)
)
```

# How does the toolbar work?

The toolbar filters tasks by the status code. The code 0 and 1 = In Progress, 2 = Success, 3 = Cancelled, 4 = Failed. There should also be a button to clear the filters.

Header: [/src/UI/TaskToolBar.hpp](/src/UI/TaskToolBar.hpp)

![/reference/widget-toolbar.png](/reference/widget-toolbar.png?raw=true)

# How tasks are updated?

The widget only reads from the database to get data to display the tasks. There are two ways to update task progress in the widget view:
1. The actual tasks will update the data model and signal when they need the widget view to update by calling `taskManagerWidget->update()` or `taskManagerWidget->updateIdHint(...);`
2. The widget can be set to poll in intervals for the progress with `taskManagerWidget->setPollDuration()`

# Usage Instructions

See the two examples. Example00 shows how the sqlite3 `QAbstractItemModel` is created and used. The sqlite3 `QAbstractItemModel` has not been implemented. Example01 was created to test the widget without the sqlite3 `QAbstractItemModel`. The sqlite3 `QAbstractItemModel` is similar to `QSqlTableModel`.
* [/src_example/example00/main.cpp](/src_example/example00/main.cpp)
* [/src_example/example01/main.cpp](/src_example/example01/main.cpp)

# Libraries, Compiler, and compatability

The Libraries used are QT, Boost, and sqlite3. Other libraries need to be approved before use.

Program must compile on Windows and Linux. For Windows, use MinGW for compiling. For Linux use GCC. Use cmake as the build scipt. Personally, the IDE I use is QT Creator, but any should work as long as you can build with cmake.

# Collaboration

To begin development, you should fork this repository and begin implementing the source files at [/src/](/src). Make a pull request or zip up your forked repository and send it to me when delivering work.

## Coding Standards
Always use the standard library when possible. Use `std::shared_ptr` and `std::unique_ptr` instead of raw pointers whenever possible, except when creating widgets since the the QT UI will Immediately take control of the widget. use `boost` if some method does not exist in standard library. Finally use `QT5` as the last option. For example use `std::string` instead of `QString` so the code is more portable. Use `QString` only when necessary to pass to a QT function.

Separate all graphical GUI code into the `/src/UI/` directory. Anything with `QT` should be in the `/src/UI/` directory. All logic and non-GUI code goes into the `/src/core/` directory.

* Use camel case
* Use C++17 best coding practices
* Use the standard library when possible
* Use .hpp files for C++ headers and .cpp files for C++ source
* Use namespace bookfiler::widget for all `QWidget` and derivatives.

## Deliverables

* Clean and commented code that follows the general design already provided and discussed in the readme.
* Widget is implemented with the interface the header files outlined.
* A working example [/src_example/example01/main.cpp](/src_example/example01/main.cpp).
* tasks are selectable and copyable as tab separated values in the clipboard.
* Widget works and looks as the photos show.

