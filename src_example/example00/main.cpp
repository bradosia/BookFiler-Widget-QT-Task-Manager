/*
 * @name BookFiler Library - Sort Filter Tree Widget
 * @author Branden Lee
 * @version 1.00
 * @license MIT
 * @brief Super fast tree sorting and filtering tree widget.
 */

// C++
#include <ctime>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>

/* sqlite3 3.33.0
 * License: PublicDomain
 */
#include <sqlite3.h>

/* QT 5.13.2
 * License: LGPLv3
 */
#include <QApplication>
#include <QMainWindow>
#include <QWidget>

// Bookfiler Libraries
#include <BookFiler-Widget-QT-Task-Manager/Interface.hpp>

std::string testName = "Task Manager Widget Example";

int main(int argc, char *argv[]) {
  std::cout << testName << " BEGIN" << std::endl;

  // Create a QT application
  QApplication qtApp(argc, argv);
  QMainWindow qtMainWindow;

  // create widget
  std::shared_ptr<bookfiler::widget::TaskList> taskListWidget =
      std::make_shared<bookfiler::widget::TaskList>();
  qtMainWindow.setCentralWidget(taskListWidget.get());
  qtMainWindow.show();

  // create a test database
  sqlite3 *dbPtr = nullptr;
  int rc = sqlite3_open("resources/example00.db", &dbPtr);
  if (rc) {
    std::cout << "sqlite3_open ERROR:\n" << sqlite3_errmsg(dbPtr) << std::endl;
    return -1;
  }

  std::shared_ptr<sqlite3> database(nullptr);
  database.reset(dbPtr, sqlite3_close);

  taskListWidget->setData(database, "taskList");
  taskListWidget->update();

  // Start the application loop
  qtApp.exec();

  std::cout << testName << " END" << std::endl;
  return 0;
}
