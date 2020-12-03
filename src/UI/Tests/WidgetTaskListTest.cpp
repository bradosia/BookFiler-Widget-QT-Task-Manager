#include <QtTest/QtTest>
#include <chrono>
#include <exception>
#include <map>
#include <memory>
#include <string>
#include <QMainWindow>

#include <TaskItem.hpp>
#include <TaskList.hpp>
#include <sqlite3.h>
using table_map = std::map<std::string, std::string>;

namespace bookfiler {
namespace widget{


class WidgetTaskListTest : public QMainWindow {
  Q_OBJECT
private:
  //std::shared_ptr<Stub> m_stub;
  std::shared_ptr<sqlite3> m_database{nullptr};
  TaskList* m_unit;

private slots:
  void initTestCase() {
    sqlite3 *dbPtr = nullptr;
    int rc = sqlite3_open("resources/example00.db", &dbPtr);
    if (rc) {
      throw std::runtime_error("Could not open sqlite3 database");
    }
    m_database.reset(dbPtr, sqlite3_close);
  }
  void init() {
      //m_stub = std::make_shared<Stub>();
      m_unit=new TaskList();
  }

  void setDataTestWhateverTest() {
    int ret = m_unit->setData(nullptr, "fuck");
    QVERIFY("fuck" == m_unit->tableName);
    QVERIFY(0 == ret);
  }
  void setDataTestWithCustomTable() {
    int ret = m_unit->setData(nullptr, "fuck", table_map{{"id", "id"}});
    QVERIFY(1 == m_unit->columnMap.size());
    QVERIFY(0 == ret);
  }

  void setDataWithDatabase() {
    int ret = m_unit->setData(m_database, "fuck");
    QVERIFY(15 == m_unit->columnMap.size());
    QVERIFY(0 == ret);
  }

  void setDataWithRealDatabase() {
    int ret = m_unit->setData(m_database, "taskList");
    QVERIFY(15 == m_unit->columnMap.size());
    QVERIFY(0 == ret);
  }

  void addItem() {
    int ret = m_unit->addItem(std::make_shared<TaskItem>(m_unit));
    QVERIFY(0 == ret);
    QVERIFY(1 == m_unit->taskItemList.size());
  }

  void Test_properly_Create_Destroy_Recreate_Redestroy()
  {
      TaskList* l_tasklist=new TaskList;
      l_tasklist->setData(m_database,"taskList");
      delete l_tasklist;
      l_tasklist=nullptr;
      l_tasklist=new TaskList;
      l_tasklist->setData(m_database,"taskList");
      delete l_tasklist;
      l_tasklist=nullptr;
  }
  void clean()
  {
      delete m_unit;
      m_unit=nullptr;
  }
  void cleanupTestCase() {
  }
};

}
}

QTEST_MAIN(bookfiler::widget::WidgetTaskListTest)

#include "WidgetTaskListTest.moc"
