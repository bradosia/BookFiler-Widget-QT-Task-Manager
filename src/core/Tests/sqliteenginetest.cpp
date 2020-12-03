

#include <QtTest/QtTest>
#include <SqliteQueryEngine.hpp>
#include <sqlite3.h>
#include <string>
#include <vector>
std::string get_complate_table{"SELECT * FROM taskList;"};
using bookfiler::core::SQliteQueryEngine;
using bookfiler::core::TableContent;
class SqliteQueryEngineTest : public QObject {
  Q_OBJECT

private:
  std::shared_ptr<sqlite3> m_database{nullptr};
  SQliteQueryEngine m_unit;

  void checkContent(TableContent content) {
    QVERIFY(15 == content.size());
    QVERIFY(7 == content["title"].size());
    QVERIFY("Doing stuff in update" == content["title"][1]);
  }

private slots:
  void initTestCase() {
    sqlite3 *dbPtr = nullptr;
    int rc = sqlite3_open("resources/example00.db", &dbPtr);
    if (rc) {
      throw std::runtime_error("Could not open sqlite3 database");
    }
    m_database.reset(dbPtr, sqlite3_close);
  }

  void QueryDatabase() {
    TableContent updated_value = m_unit.updateContent(m_database, &m_unit);
    checkContent(updated_value);
  }
  void QueryDatasbaeTwoTimesInARow() {
    TableContent updated_value = m_unit.updateContent(m_database, &m_unit);
    updated_value = m_unit.updateContent(m_database, &m_unit);
    checkContent(updated_value);
  }
  void NoCrashIfNullPtr() {
    TableContent updated_value = m_unit.updateContent(nullptr, &m_unit);
    QVERIFY(0 == updated_value.size());
  }

  void cleanupTestCase() { sqlite3_close(m_database.get()); }
};

QTEST_MAIN(SqliteQueryEngineTest)

#include "sqliteenginetest.moc"