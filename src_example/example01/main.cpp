/*
 * @name BookFiler Widget w/ QT - Task Manager
 * @version 1.00
 * @license MIT
 * @brief Task Manager Widget tracks task progress
 */

// C++
#include <iostream>

/* QT 5.13.2
 * License: LGPLv3
 */
#include <QApplication>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QVBoxLayout>
#include <QWidget>

// Bookfiler Libraries
#include <BookFiler-Widget-QT-Task-Manager/Interface.hpp>

std::string testName = "Task Manager Widget Example";

int main(int argc, char *argv[]) {
  std::cout << testName << " BEGIN" << std::endl;

  // Create a QT application
  QApplication qtApp(argc, argv);
  QMainWindow qtMainWindow;

  // create a test database
  QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
  database.setDatabaseName("resources/example00.db");

  if (!database.open()) {
    std::cout << database.lastError().text().toStdString();
    return -1;
  }

  // columnMap
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

  bookfiler::widget::SqliteModelTest *sqlModelPtr =
      new bookfiler::widget::SqliteModelTest(database, "taskList", columnMap);

  // create task list
  bookfiler::widget::TaskList *taskListPtr = new bookfiler::widget::TaskList();
  taskListPtr->setModel(sqlModelPtr);
  taskListPtr->update();

  // create task toolbar
  bookfiler::widget::TaskToolbar *taskToolbarPtr =
      new bookfiler::widget::TaskToolbar();

  // Set up window
  QWidget *centralWidgetPtr = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(taskToolbarPtr);
  layout->addWidget(taskListPtr);
  centralWidgetPtr->setLayout(layout);

  qtMainWindow.setCentralWidget(centralWidgetPtr);
  qtMainWindow.show();

  // Start the application loop
  qtApp.exec();

  std::cout << testName << " END" << std::endl;
  return 0;
}
