# Development Summary

I need a QT5 widget written in C++. Only the widget implementation needs to be written, not an app. The widget is a task manager that consists of three components: The task list, the task items, and the task toolbar. The implementation requires a sqlite3 database backend. The header files are already written so the implementation should be filled in. See the photos for how the task manager should look.

Header: [/src/UI/WidgetTaskList.hpp](/src/UI/WidgetTaskList.hpp)

![/reference/widget-overview.png](/reference/widget-overview.png?raw=true)

![/reference/widget-tasklist-subtasks.png](/reference/widget-tasklist-subtasks.png?raw=true)

Header: [/src/UI/WidgetTaskItem.hpp](/src/UI/WidgetTaskItem.hpp)

[/reference/widget-laskitem.png](/reference/widget-laskitem.png)

Header: [/src/UI/WidgetTaskToolBar.hpp](/src/UI/WidgetTaskToolBar.hpp)

[/reference/widget-toolbar.png](/reference/widget-toolbar.png)

## Libraries, Compiler, and compatability

The Libraries used are QT, Boost, and sqlite3. Other libraries need to be approved before use.

Program must compile on Windows and Linux. For Windows, use MinGW for compiling. For Linux use GCC. Use cmake as the build scipt. Personally, the IDE I use is QT Creator, but any should work as long as you can build with cmake.

# Usage Instructions

Connect to your database:
```cpp
sqlite3 *dbPtr = nullptr;
sqlite3_open("myDatabase.db", &dbPtr);
// Using shared pointers when possible
std::shared_ptr<sqlite3> database(nullptr);
database.reset(dbPtr, sqlite3_close);
```

Create the tree widget and set the database data
```cpp
std::shared_ptr<bookfiler::widget::TreeImpl> treeWidget =
      std::make_shared<bookfiler::widget::TreeImpl>();
treeWidget->setData(database, "taskList");
treeWidget->update();
```

## Sqlite3 Table format
The default table create statement is shown below. The Table name and column names may be different, but the user must explicitly map the names.
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

## Coding Standards
Always use the standard library when possible. Use `std::shared_ptr` and `std::unique_ptr` instead of raw pointers whenever possible. use `boost` if some method does not exist in standard library. Finally use `QT5` as the last option.

Separate all graphical GUI code into the `/src/UI/` directory. Anything with `QT` should be in the `/src/UI/` directory. All logic and non-GUI code goes into the `/src/core/` directory.

* Use camel case
* Use C++17 best coding practices
* Use the standard library when possible

## Deliverables

* Clean and commented code that follows the general design already provided and discussed here
* A working example [/src_example/example00/main.cpp](/src_example/example00/main.cpp).
* tasks are selectable and copyable as tab separated values.

